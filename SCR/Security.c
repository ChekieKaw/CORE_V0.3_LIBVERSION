#include "Security.h"

void Sec_IWDG_Init(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_8);
	IWDG_SetReload(160);
	IWDG_ReloadCounter();
	IWDG_Enable();
}

void Sec_IWDG_Slowdown(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	IWDG_SetReload(0xFFF);
	IWDG_ReloadCounter();
}

void Sec_IWDG_Speedup(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_8);
	IWDG_SetReload(160);
	IWDG_ReloadCounter();
}

void Sec_Get_Key(uint32_t* key)
{
	key[0]=*((uint32_t*)0x1FFFF7E8);
	key[1]=*((uint32_t*)0x1FFFF7EC);
	key[2]=*((uint32_t*)0x1FFFF7F0);
}
uint8_t Sec_Check_Key0(uint32_t* key)
{
	if((*((uint32_t*)0x1FFFF7E8))==key[0])
	{
		return 0;
	}
	else{
		return 1;
	}
}
uint8_t Sec_Check_Key1(uint32_t* key)
{
	if((*((uint32_t*)0x1FFFF7EC))==key[1])
	{
		return 0;
	}
	else{
		return 1;
	}
}
uint8_t Sec_Check_Key2(uint32_t* key)
{
	if((*((uint32_t*)0x1FFFF7F0))==key[2])
	{
		return 0;
	}
	else{
		return 1;
	}
}
