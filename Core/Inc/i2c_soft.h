

#ifndef __I2C_SOFT_H
#define __I2C_SOFT_H

#include "gpio.h"

// ?? I2C ??
#define OLED_I2C_SCL_PORT       GPIOB
#define OLED_I2C_SCL_PIN        GPIO_PIN_1
#define OLED_I2C_SDA_PORT       GPIOB
#define OLED_I2C_SDA_PIN        GPIO_PIN_2

// ?????
#define OLED_I2C_SCL_HIGH()     HAL_GPIO_WritePin(OLED_I2C_SCL_PORT, OLED_I2C_SCL_PIN, GPIO_PIN_SET)//GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN)
#define OLED_I2C_SCL_LOW()      HAL_GPIO_WritePin(OLED_I2C_SCL_PORT, OLED_I2C_SCL_PIN, GPIO_PIN_RESET)//GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN)
#define OLED_I2C_SDA_HIGH()     HAL_GPIO_WritePin(OLED_I2C_SDA_PORT, OLED_I2C_SDA_PIN, GPIO_PIN_SET)//GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN)
#define OLED_I2C_SDA_LOW()      HAL_GPIO_WritePin(OLED_I2C_SDA_PORT, OLED_I2C_SDA_PIN, GPIO_PIN_RESET)//GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN)
#define OLED_I2C_SDA_READ()     HAL_GPIO_ReadPin(OLED_I2C_SDA_PORT, OLED_I2C_SDA_PIN)//GPIO_ReadInputDataBit(I2C_SDA_PORT, I2C_SDA_PIN)


#define I2C_SCL_PORT       GPIOB
#define I2C_SCL_PIN        GPIO_PIN_8
#define I2C_SDA_PORT       GPIOB
#define I2C_SDA_PIN        GPIO_PIN_9

// ?????

#define I2C_SCL_HIGH()     HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_PIN_SET)//GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN)
#define I2C_SCL_LOW()      HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_PIN_RESET)//GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN)
#define I2C_SDA_HIGH()     HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_PIN_SET)//GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN)
#define I2C_SDA_LOW()      HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_PIN_RESET)//GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN)
#define I2C_SDA_READ()     HAL_GPIO_ReadPin(I2C_SDA_PORT, I2C_SDA_PIN)//GPIO_ReadInputDataBit(I2C_SDA_PORT, I2C_SDA_PIN)

void I2C_SOFT_INIT();

void I2C_Delay_us(uint32_t us);

// I2C ????
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(uint8_t data);
uint8_t I2C_ReadByte(void);
uint8_t I2C_WaitAck(void);
void I2C_SendAck(void);
void I2C_SendNoAck(void);

// ????
uint8_t I2C_WriteReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
uint8_t I2C_ReadReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data);
uint8_t I2C_WriteData(uint8_t dev_addr, uint8_t *data, uint16_t len);
uint8_t I2C_ReadData(uint8_t dev_addr, uint8_t *data, uint16_t len);
uint8_t I2C_WriteDataWithReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);
uint8_t I2C_ReadDataWithReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);


void OLED_I2C_SOFT_INIT();

void OLED_I2C_Delay_us(uint32_t us);

// I2C ????
void OLED_I2C_Start(void);
void OLED_I2C_Stop(void);
void OLED_I2C_SendByte(uint8_t data);
uint8_t OLED_I2C_ReadByte(void);
uint8_t OLED_I2C_WaitAck(void);
void OLED_I2C_SendAck(void);
void OLED_I2C_SendNoAck(void);

// ????
uint8_t OLED_I2C_WriteReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
uint8_t OLED_I2C_ReadReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data);
uint8_t OLED_I2C_WriteData(uint8_t dev_addr, uint8_t *data, uint16_t len);
uint8_t OLED_I2C_ReadData(uint8_t dev_addr, uint8_t *data, uint16_t len);
uint8_t OLED_I2C_WriteDataWithReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);
uint8_t OLED_I2C_ReadDataWithReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

#endif

