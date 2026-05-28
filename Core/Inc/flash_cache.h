


#ifndef __FLASH_CACHE_H
#define __FLASH_CACHE_H

#include "stm32h7xx_hal.h"

void Flash_Cache_Init(void);
HAL_StatusTypeDef Flash_Cache_Write(uint32_t addr, uint8_t *data, uint32_t len);
HAL_StatusTypeDef Flash_Cache_Flush(void);

#endif