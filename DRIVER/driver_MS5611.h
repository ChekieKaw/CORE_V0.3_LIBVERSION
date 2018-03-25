#ifndef __DRIVER_MS5611_H
#define __DRIVER_MS5611_H

#include "stm32f10x.h"
#include "delay.h"
#include "math.h"

#define AUXENSOR_1_SPIx SPI1

#define MS5611_CMD_Reset  0x1E
#define MS5611_CMD_CONV_Pressure 0x48	//最高分辨率
#define MS5611_CMD_CONV_Temperature 0x58	//最高分辨率
//#define MS5611_CMD_CONV_Pressure 0x46	//次高分辨率
//#define MS5611_CMD_CONV_Temperature 0x56	//次高分辨率
#define MS5611_CMD_ADC_Read 0x00

#define	MS5611_PROM_Reg	0xA0

void MS5611_Reset(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void MS5611_Prom_Read(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void MS5611_Tpt_Conv(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void MS5611_Prs_Conv(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint32_t MS5611_ADC_Read(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void MS5611_Update(uint32_t D1, uint32_t D2,int32_t* pTEMP,int32_t* pPRESSURE);

#endif
