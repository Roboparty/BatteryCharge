#include "fw_update.h"
#include "usart.h"   // ????????
#include <string.h>
#include <stdlib.h>

#define RX_BUFFER_SIZE  512   // ???? 16+256+2 = 274 ??,512 ??

static FW_Update_Context fw_ctx;
static uint8_t rx_buf[RX_BUFFER_SIZE];

// CRC16 Modbus (??0xFFFF, ???0xA001)
uint16_t CRC16_Modbus(uint8_t *buf, uint16_t len)
{
    uint16_t crc = 0xFFFF;
    for (uint16_t i = 0; i < len; i++) {
        crc ^= buf[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x0001)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc >>= 1;
        }
    }
    return crc;
}

void FW_Update_Init(void)
{
    memset(&fw_ctx, 0, sizeof(fw_ctx));
    fw_ctx.state = FW_IDLE;
    fw_ctx.rx_buffer = rx_buf;
    // ??????Flash?????
}

// ?????(??????)
static void UART_SendString(const char *str)
{
    HAL_UART_Transmit(&huart3, (uint8_t*)str, strlen(str), 100);
    HAL_UART_Transmit(&huart3, (uint8_t*)";", 1, 100);
}

void FW_SendAck(uint16_t index)
{
    char ack[32];
    sprintf(ack, "%d succeed", index);
    UART_SendString(ack);
}

void FW_SendError(const char *err_msg)
{
    UART_SendString(err_msg);
}

// Check data
static bool IsValidDate(const uint8_t *date)
{
    // date format "yyyy-mm-dd-A"
    if (date[4] != '-' || date[7] != '-' || date[10] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }
    if (date[11] < 'A' || date[11] > 'Z') return false;
    return true;
}

// Analysis Packate
static void ProcessPacket(void)
{
    // parse head
    uint8_t *header = fw_ctx.header;
    // date
    if (!IsValidDate(header)) {
        FW_SendError("wrong date");
        fw_ctx.state = FW_IDLE;
        return;
    }
    // payload len
    uint16_t segment_len = (header[12] << 8) | header[13];
    uint16_t payload_len_val = segment_len - 2;   // ??CRC2??
    if (payload_len_val > 256 || segment_len < 2) {
        FW_SendError("length mismatch");
        fw_ctx.state = FW_IDLE;
        return;
    }
    // segment index
    uint16_t index = (header[14] << 8) | header[15];
    // check whether index match
    // last_index++, as this expected index
    static uint16_t last_index = 0;
    if (index != last_index && last_index != 0) {
        FW_SendError("wrong index");
        fw_ctx.state = FW_IDLE;
        last_index = 0; // reset
        return;
    }
    last_index = index + 1;

    //Calculate CRC: head 16byte + Payload
    uint16_t crc_calc = CRC16_Modbus(fw_ctx.rx_buffer, 16 + payload_len_val);
    //Recved CRC(Little Endian, Low byte first)
    uint8_t *crc_bytes = fw_ctx.rx_buffer + 16 + payload_len_val;
    uint16_t crc_rcvd = crc_bytes[0] | (crc_bytes[1] << 8);
    if (crc_calc != crc_rcvd) {
        FW_SendError("CRC Error");
        fw_ctx.state = FW_IDLE;
        return;
    }

    // All Check Passed
    // Save Payload to Flash or RAM
    // payload start address: fw_ctx.rx_buffer + 16
    // Length: payload_len_val
    // Basing index to Calculate Burn address

    // Send ACK
    FW_SendAck(index);

    // Ready to Recv Nxt Packate
    fw_ctx.state = FW_IDLE;  // Wait Next Start
}

// External Call: Every Recving Segment data(trigged by DMA)
void FW_Update_Process(uint8_t *data, uint16_t len)
{
    static uint16_t bytes_processed = 0;
    uint16_t i = 0;
    while (i < len) {
        switch (fw_ctx.state) {
            case FW_IDLE:
                fw_ctx.state = FW_WAIT_HEADER;
                fw_ctx.rx_index = 0;
                // fall through
            case FW_WAIT_HEADER:
                while (i < len && fw_ctx.rx_index < 16) {
                    fw_ctx.header[fw_ctx.rx_index++] = data[i++];
                }
                if (fw_ctx.rx_index == 16) {
                    // Head Recv finished, parse length
                    uint16_t segment_len = (fw_ctx.header[12] << 8) | fw_ctx.header[13];
                    fw_ctx.expected_len = 16 + segment_len;   // 16? + ???(?CRC)
                    fw_ctx.payload_len = segment_len - 2;
                    if (fw_ctx.expected_len > RX_BUFFER_SIZE) {
                        FW_SendError("length mismatch");
                        fw_ctx.state = FW_IDLE;
                        break;
                    }
                    // Copy head to rx_buffer
                    memcpy(fw_ctx.rx_buffer, fw_ctx.header, 16);
                    fw_ctx.rx_index = 16;
                    fw_ctx.state = FW_WAIT_PAYLOAD;
                }
                break;
            case FW_WAIT_PAYLOAD:
                // remain part(payload+CRC)
                while (i < len && fw_ctx.rx_index < fw_ctx.expected_len) {
                    fw_ctx.rx_buffer[fw_ctx.rx_index++] = data[i++];
                }
                if (fw_ctx.rx_index == fw_ctx.expected_len) {
                    // complete packate proc finished
                    ProcessPacket();
                    fw_ctx.state = FW_IDLE;
                }
                break;
            default:
                break;
        }
    }
}