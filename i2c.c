#include "i2c.h"

void I2C_Config(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); //i2c1 la mot bo dieu khien i2c tren stm32 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_ClockSpeed = 200000;  //200kHz
		I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;   // che do giao tiep chuan
		I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;  //chia tan ti le 1:2
    I2C_InitStructure.I2C_OwnAddress1 = 0x00; // dia chi stm32
    I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;  //ko bat che do ACK mac dinh 
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //dia chi 7 bit
    I2C_Init(I2C1, &I2C_InitStructure);

    I2C_Cmd(I2C1, ENABLE);//bat i2c 
}

void I2C_Write(uint8_t addr, uint8_t *data, uint8_t len) {
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));//tra ve 1 neu neu dang doc/gh

    I2C_GenerateSTART(I2C1, ENABLE);// tao tin hieu start
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));//ktra stm32 da la master hay chua, neu chua thi tiep tuc cho

    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);//gui 7 bit dia chi, 1 bit ghi (0)
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//ktra master dã vào mode ghi du lieu hay chua

    for (uint8_t i = 0; i < len; i++) {
        I2C_SendData(I2C1, data[i]);//gui tung byte thu i trong mang? data 
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//ktra master da gui thanh cong byte chua 
    }

    I2C_GenerateSTOP(I2C1, ENABLE); //gui tin hieu stop 
}

void I2C_Read(uint8_t addr, uint8_t *buffer, uint8_t len) {
		while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //tra ve 1 neu neu dang doc/ghi 
		
		//gui tin hieu start
    I2C_GenerateSTART(I2C1, ENABLE); // tao tin hieu start
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //ktra stm32 da la master hay chua, neu chua thi tiep tuc cho 
		
		//gui dia chi slave
    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Receiver);//gui 7 bit dia chi, them 1 bit doc (1) 

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); //ktra master dã vào mode nhan du lieu hay chua, neu slave gui ack nghia la su kien xay ra con ko tiep tuc cho 
		
		//nhan cac byte tru byte cuoi 
    for (uint8_t i = 0; i < len - 1; i++) {
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));//ktra master da nhan thanh cong byte chua 
        buffer[i] = I2C_ReceiveData(I2C1);//ghi byte vao buffer 
    }
		
		//tat ACK 
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    buffer[len - 1] = I2C_ReceiveData(I2C1);//doc not byte cuoi ghi vao buffer
    
		//gui tin hieu stop 
    I2C_GenerateSTOP(I2C1, ENABLE);
    I2C_AcknowledgeConfig(I2C1, ENABLE);//bat lai ACK cho lan tiep theo 
}
