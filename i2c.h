#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"

void I2C_Config(void);
void I2C_Write(uint8_t addr, uint8_t *data, uint8_t len);
void I2C_Read(uint8_t addr, uint8_t *buffer, uint8_t len);

#endif

//uint8_t addr: dia chi cua thiet bi 
//uint8_t *data: con tro den mang chua du lieu can gui 
//uint8_t len: so byte can gui 

//uint8_t addr: dia chi I2C1 cua thiet bi can doc du lieu 
//uint8_t *buffer: con tro den mang de luu du lieu nhan dc
//uint8_t len: so byte can doc