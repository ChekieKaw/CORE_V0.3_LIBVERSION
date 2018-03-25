#ifndef __INTERFACE_INIT_H
#define __INTERFACE_INIT_H
#include "stm32f10x.h"
#include "def_globalmacro.h"

void GPIO_Configuration(void);
void SPI_Configuration(void);

void PWM_OUTPUT_Set_1(void);
void PWM_OUTPUT_Set_2(void);

void USART1_Configuration(uint32_t USART_RX_BUF,uint32_t USART_TX_BUF);
void USART2_Configuration(uint32_t USART_RX_BUF,uint32_t USART_TX_BUF);
void USART3_Configuration(uint32_t USART_RX_BUF);

void ADC_VS_Configuration(uint32_t ADC_BUF);

#endif
