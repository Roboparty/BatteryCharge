


#include "flash_cache.h"
#include "bootloader.h"
#include <string.h>

static uint8_t cache_buffer[32];
static uint32_t cache_base_addr = 0xFFFFFFFF;
static uint32_t cache_len = 0;

static HAL_StatusTypeDef Flash_Cache_Commit(void)
{
    if (cache_len == 0) return HAL_OK;

    // ?? 0xFF
    for (uint32_t i = cache_len; i < 32; i++) {
        cache_buffer[i] = 0xFF;
    }

    HAL_FLASH_Unlock();
    SCB_DisableICache();
    SCB_DisableDCache();

    HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD,
                                                 cache_base_addr,
                                                 (uint32_t)cache_buffer);

    SCB_EnableDCache();
    SCB_EnableICache();
    HAL_FLASH_Lock();

    if (status != HAL_OK) return status;

    // ??
    for (uint32_t i = 0; i < 32; i++) {
        if (*(uint8_t*)(cache_base_addr + i) != cache_buffer[i]) {
            return HAL_ERROR;
        }
    }

    cache_len = 0;
    cache_base_addr = 0xFFFFFFFF;
    return HAL_OK;
}

void Flash_Cache_Init(void)
{
    cache_len = 0;
    cache_base_addr = 0xFFFFFFFF;
}

HAL_StatusTypeDef Flash_Cache_Write(uint32_t addr, uint8_t *data, uint32_t len)
{
    if (len == 0) return HAL_OK;

    while (len > 0) {
        uint32_t block_base = addr & ~0x1F;
        if (cache_len == 0) {
            cache_base_addr = block_base;
        } else if (block_base != cache_base_addr) {
            HAL_StatusTypeDef res = Flash_Cache_Commit();
            if (res != HAL_OK) return res;
            cache_base_addr = block_base;
        }

        uint32_t offset = addr - cache_base_addr;
        uint32_t chunk = 32 - offset;
        if (chunk > len) chunk = len;

        memcpy(cache_buffer + offset, data, chunk);
        if (offset + chunk > cache_len) cache_len = offset + chunk;

        if (cache_len == 32) {
            HAL_StatusTypeDef res = Flash_Cache_Commit();
            if (res != HAL_OK) return res;
        }

        addr += chunk;
        data += chunk;
        len -= chunk;
    }
    return HAL_OK;
}

HAL_StatusTypeDef Flash_Cache_Flush(void)
{
    if (cache_len > 0) {
        return Flash_Cache_Commit();
    }
    return HAL_OK;
}

