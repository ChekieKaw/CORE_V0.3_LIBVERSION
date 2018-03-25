#include "System_Init.h"

extern uint8_t USART1_RX_BUF[64];
extern uint8_t USART1_TX_BUF[64];
extern uint8_t USART2_RX_BUF[64];
extern uint8_t USART2_TX_BUF[64];
extern uint8_t USART3_RX_BUF[64];
extern uint16_t AD_BUF[1];

void System_Init(void)
{
	NVIC_Configuration();
	GPIO_Configuration();
	SPI_Configuration();
	TIMER4_Configuration();
	
	PWM_OUTPUT_Set_1();
	
	USART1_Configuration((uint32_t)USART1_RX_BUF,(uint32_t)USART1_TX_BUF);
	USART2_Configuration((uint32_t)USART2_RX_BUF,(uint32_t)USART2_TX_BUF);
	USART3_Configuration((uint32_t)USART3_RX_BUF);
	
	ADC_VS_Configuration((uint32_t)AD_BUF);
}
