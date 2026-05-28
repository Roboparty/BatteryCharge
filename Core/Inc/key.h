#ifndef __KEY_H
#define __KEY_H

#include "stm32f1xx_hal.h"
#include "gpio.h"

// ??????
extern uint8_t KEY1_EVENT;   // ????
extern uint8_t KEY2_EVENT;   // ????
extern uint8_t KEY_LONG_EVENT; // ????

// ???????(??)
extern uint8_t KEY1_VAL;
extern uint8_t KEY2_VAL;

void KEY_Init(void);
void KEY_Scan(void);

#endif