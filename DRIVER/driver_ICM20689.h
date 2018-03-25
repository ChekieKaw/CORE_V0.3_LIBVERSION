#ifndef __DRIVER_ICM20689_H
#define __DRIVER_ICM20689_H

#include "stm32f10x.h"

/* ICM20689 Register Map */
#define CONFIG									0x1a
#define	GYRO_CONFIG							0x1b
#define ACCEL_CONFIG						0x1c
#define ACCEL_CONFIG2						0x1d
#define ACCEL_XOUTH							0x3b
#define ACCEL_XOUTL							0x3c
#define ACCEL_YOUTH							0x3d
#define ACCEL_YOUTL							0x3e
#define ACCEL_ZOUTH							0x3f
#define ACCEL_ZOUTL							0x40
#define	TEMP_OUTH							0x41
#define	TEMP_OUTL							0x42
#define GYRO_XOUTH							0x43
#define GYRO_XOUTL							0x44
#define GYRO_YOUTH							0x45
#define GYRO_YOUTL							0x46
#define GYRO_ZOUTH							0x47
#define GYRO_ZOUTL							0x48
#define USER_CTRL							0x6a
#define PWR_MGMT1							0x6b
#define	PWR_MGMT2							0x6c
#define WHO_AM_I							0x75

void ICM20689_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
u8 ICM20689_ReadRegister(u8 add,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void ICM20689_WriteRegister(u8 add,u8 val,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
u8 ICM20689_SPI1_ReadWriteByte(u8 TxData);
void ICM20689_Read(int16_t* omega_raw,int16_t* acc_raw,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void ICM20689_Read_Gyro(int16_t* omega_raw,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif
