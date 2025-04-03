#include "bh1750.h"
#include "i2c.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"

void UART_Init(void) {
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

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}


void UART_SendChar(char c) {//gui 1 ki tu qua uart
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);//ktra cong tx co san sang truyen data ko?
																																 //USART_FLAG_TXE co bao thanh ghi data trong va san sang nhan du kieu 
																																 //RESET la chua san sang (SET moi tiep tuc) 
    USART_SendData(USART1, c);
}

void UART_SendString(char *str) {//gui 1 chuoi ki tu 
    while (*str) {
        UART_SendChar(*str++);//lay gia tri ki tu tai dia chi str roi tang dia chi con tro ++, gap null thi dung 
    }
}

void UART_SendNumber(uint16_t number) {//chuyen so nguyen -> chuoi va gui qua uart 
    char buffer[10]; 
    sprintf(buffer, "%d", number); // ham chuyen doi so nuyen thanh chuoi ki tu
    UART_SendString(buffer); 
}


int main(void) {
    uint16_t lux;
    I2C_Config();       
    UART_Init();      
    BH1750_Init();      

    while (1) {
        lux = BH1750_ReadLight();  
        UART_SendString("Cuong do anh sang: ");
				UART_SendNumber(lux);
				UART_SendString(" lux\n");
        for ( int i = 0; i < 2000000; i++);  //delay fake 
    }
}