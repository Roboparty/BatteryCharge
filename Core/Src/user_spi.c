

#include "user_spi.h"
#include "stm32f1xx_hal_spi.h"
#include "spi.h"

int spi2_send(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
	if(pData == NULL)
		return 1;
	HAL_SPI_Transmit_DMA(hspi, pData, Size);
	return 0;
}

int spi2_recv(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
	if(pData == NULL)
		return 1;
	HAL_SPI_Receive_DMA(hspi, pData, Size);
	return 0;
}
