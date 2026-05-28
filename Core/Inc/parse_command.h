

#ifndef _PARSE_COMMAND_H_
#define _PARSE_COMMAND_H_
#include "main.h"
#define CFG_FLASH_ADDR   0x0800FC00   // ????????(STM32F103C8 64KB,?????? 0x0800FC00,??1KB)
#define CFG_MAGIC_NUMBER 0xAA55      // ????,????????
#define CFG_SAVE_BYTES   36
typedef struct {
    uint16_t magic;              // ??,??????????
    uint8_t  ictrl;              // ICTRL ??? (0-100)
    uint8_t  r;                  // R [0-100]
    uint8_t  g;                  // G [0-100]
    uint8_t  b;                  // B [0-100]
    uint8_t  chg_en;             // CHG_EN  (0/1)
    uint8_t  fan;                // FAN Speed
    char  str_sw_date[12];    // yyyy-mm-dd-A(/B/C)
    char  str_chrg_sn[16];    // Charge Brd SN
} ConfigData;

extern ConfigData g_config;   // ????
extern int LoadConfigFromFlash(ConfigData *cfg);
extern void ApplyConfig(void);
extern void parse_command(const uint8_t *cmd, uint16_t len);

extern char strBmsSoc[6];
extern char strBmsSoh[6];
#endif