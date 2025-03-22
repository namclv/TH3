#ifndef BH1750_H
#define BH1750_H

#include "stm32f10x.h"  

#define BH1750_ADDR   0x23 << 1  
#define BH1750_ONE_H_MODE  0x10  

void BH1750_Init(void);
uint16_t BH1750_ReadLight(void);

#endif
