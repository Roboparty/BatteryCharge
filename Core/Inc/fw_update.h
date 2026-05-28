#ifndef __FW_UPDATE_H
#define __FW_UPDATE_H

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

// ????
#define CMD_CHARGER_UPDATE_START   "CHARGER_UPDATE_START"
#define CMD_BMS_UPDATE_START       "BMS_UPDATE_START"
#define CMD_START_BMS_UPDATE       "START_BMS_UPDATE"   // ????BMS??

// ???
typedef enum {
    FW_IDLE,
    FW_WAIT_HEADER,
    FW_WAIT_PAYLOAD,
    FW_WAIT_CRC,
} FW_STATE;

// ????
typedef struct {
    FW_STATE state;
    uint8_t header[16];
    uint16_t expected_len;    // ??? = payload_len + 2
    uint16_t payload_len;
    uint16_t packet_index;
    uint8_t *rx_buffer;       // ?????????
    uint16_t rx_index;
    bool crc_ok;
} FW_Update_Context;

// ????
void FW_Update_Init(void);
void FW_Update_Process(uint8_t *data, uint16_t len);
void FW_SendAck(uint16_t index);
void FW_SendError(const char *err_msg);
uint16_t CRC16_Modbus(uint8_t *buf, uint16_t len);

#endif

