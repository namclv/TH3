#ifndef BH1750_H
#define BH1750_H

#include "stm32f10x.h"  

#define BH1750_ADDR   0x23 << 1  //0010 0011
#define BH1750_ONE_H_MODE  0x10  //do 1 lan voi do phan giai cao 1 lux 0001 0000

void BH1750_Init(void);
uint16_t BH1750_ReadLight(void);

#endif
