#ifndef __COMMUNICATE_H
#define __COMMUNICATE_H
#include "stm32f10x.h"
#include "def_datastructure.h"
#include "def_globalmacro.h"
#include <math.h>
#include "delay.h"

void com_decipher_sbus(
	uint8_t USART_RX_STA,
	uint8_t* USART_RX_BUF,
	struct str_glb_input* glb_input,
	struct str_glb_identity* glb_identity,
	struct str_glb_toc* glb_toc);
	
void com_decipher_dsm(
	uint8_t USART_RX_STA,
	uint8_t* USART_RX_BUF,
	struct str_glb_input* glb_input,
	struct str_glb_identity* glb_identity,
	struct str_glb_toc* glb_toc);

#endif
