#include "bh1750.h"
#include "i2c.h"  

void BH1750_Init(void) {
    uint8_t cmd = BH1750_ONE_H_MODE;
    I2C_Write(BH1750_ADDR, &cmd, 1);  // gui dia chi, lenh do, 1 byte 
}

uint16_t BH1750_ReadLight(void) {
    uint8_t buffer[2] = {0};
    I2C_Read(BH1750_ADDR, buffer, 2);  
    uint16_t lux = ((buffer[0] << 8) | buffer[1]) / 1.2;  
    return lux;
}
