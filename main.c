#include "bh1750.h"
#include "i2c.h"
#include "stm32f10x.h"
#include "stdio.h"

void UART_Config(void);
void UART_SendString(char *str);

int main(void) {
    uint16_t lux;
    char buffer[32];

    I2C_Config();       
    UART_Config();      
    BH1750_Init();      

    while (1) {
        lux = BH1750_ReadLight();  
        
        sprintf(buffer, "Light: %d lux\r\n", lux); 
        UART_SendString(buffer);  

        for (volatile int i = 0; i < 500000; i++);  
    }
}

void UART_Config(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}


void UART_SendString(char *str) {
    while (*str) {
        while (!(USART1->SR & USART_SR_TXE));  
        USART1->DR = *str++;
    }
}
	