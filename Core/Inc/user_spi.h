

#ifndef _USER_SPI_H_
#define _USER_SPI_H_
#include "spi.h"

extern int spi2_send(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
extern int spi2_recv(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);

#endif
