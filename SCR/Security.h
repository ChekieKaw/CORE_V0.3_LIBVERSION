#ifndef __SECURITY_H
#define __SECURITY_H

#include "stm32f10x.h"

void Sec_IWDG_Init(void);
void Sec_IWDG_Slowdown(void);
void Sec_IWDG_Speedup(void);
void Sec_Get_Key(uint32_t* key);
uint8_t Sec_Check_Key0(uint32_t* key);
uint8_t Sec_Check_Key1(uint32_t* key);
uint8_t Sec_Check_Key2(uint32_t* key);

#endif
