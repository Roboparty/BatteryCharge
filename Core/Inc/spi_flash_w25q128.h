/*--------------------------------------------------------------------------------
 * ??: spi_flash_w25q128.h
 * ??: W25Q128JVSQ SPI Flash ?????? (??CS + ?DMA)
 *--------------------------------------------------------------------------------*/
#ifndef _SPI_FLASH_W25Q128_H_
#define _SPI_FLASH_W25Q128_H_

#include <stdint.h>
#include <stdbool.h>

/* ????? (GPIOB Pin12) */
#define W25Q_CS_LOW()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define W25Q_CS_HIGH()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

/* ???? */
#define W25Q_CMD_WREN      0x06
#define W25Q_CMD_WRDI      0x04
#define W25Q_CMD_RDSR1     0x05
#define W25Q_CMD_RDSR2     0x35
#define W25Q_CMD_WRSR      0x01
#define W25Q_CMD_READ      0x03
#define W25Q_CMD_FAST_READ 0x0B
#define W25Q_CMD_PP        0x02
#define W25Q_CMD_SE        0x20
#define W25Q_CMD_BE32      0x52
#define W25Q_CMD_BE64      0xD8
#define W25Q_CMD_CE        0xC7
#define W25Q_CMD_RDID      0x9F
#define W25Q_CMD_PD        0xB9
#define W25Q_CMD_RDPD      0xAB

/* ?????? */
#define W25Q_SR1_BUSY      (1 << 0)
#define W25Q_SR1_WEL       (1 << 1)

/* ???? */
void W25Q128_Init(void);
void W25Q128_ReadID(uint8_t *id);
void W25Q128_WaitBusy(void);
void W25Q128_WriteEnable(void);
void W25Q128_EraseSector(uint32_t sector_addr);
void W25Q128_EraseBlock32K(uint32_t block_addr);
void W25Q128_EraseBlock64K(uint32_t block_addr);
void W25Q128_EraseChip(void);
void W25Q128_PageProgram(uint32_t page_addr, uint8_t *data, uint16_t len);
void W25Q128_Read(uint32_t addr, uint8_t *rxBuf, uint16_t len);

void spi_flash_simple_test();

#endif

