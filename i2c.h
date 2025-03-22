#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"

void I2C_Config(void);
void I2C_Write(uint8_t addr, uint8_t *data, uint8_t len);
void I2C_Read(uint8_t addr, uint8_t *buffer, uint8_t len);

#endif
