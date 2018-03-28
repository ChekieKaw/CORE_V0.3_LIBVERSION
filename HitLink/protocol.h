#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include <stdint.h>
#include "stdio.h"
#include "hitlink.h"
#include "string.h"

/* Private define ------------------------------------------------------------*/
#define FLOAT_SIZE	sizeof(float)		//4
#define INT_SIZE		sizeof (int)		//4
#define UINT32_SIZE	sizeof(uint32_t)//4 
#define DOUBLE_SIZE	sizeof(double)	//8
#define	HEARTBEAT	0
#define	ATTITUTE	1

/* Private function prototypes -----------------------------------------------*/
//void put_float_buf(char *buffer, float data);
//void put_uint32_t_buf(char *buffer, uint32_t data);
//void put_int_buf(char *buffer, int data);

void put_float_buf(unsigned char *buffer, float data)
{
	unsigned char float_buf[FLOAT_SIZE];
	unsigned int i=0;
	for(i=0;i<FLOAT_SIZE;i++)
	{
		float_buf[i]=(((uint32_t)data)>>(8*(FLOAT_SIZE-i)))&0x0000000FF;
	}
//	float_buf[0]=(uint32_t)data>>(8*3);
//	float_buf[1]=((uint32_t)data>>(8*2))&0x000000FF;
//	float_buf[2]=((uint32_t)data>>(8*1))&0x000000FF;
//	float_buf[3]=((uint32_t)data&0x000000FF);
	memcpy(buffer,float_buf,(unsigned int)sizeof(float));
}

void put_uint32_t_buf(unsigned char *buffer, uint32_t data)
{
	unsigned char uint32_t_buf[UINT32_SIZE];
	int i=0;
	for(i=0;i<UINT32_SIZE;i++)
	{
		uint32_t_buf[i]=((uint32_t)data>>(8*(UINT32_SIZE-1-i)))&0x000000FF;
	}
	memcpy(buffer,uint32_t_buf,(unsigned int)sizeof(uint32_t));
}

void put_int_buf(unsigned char *buffer, int data)
{
	unsigned char int_buf[INT_SIZE];
	int i=0;
	for(i=0;i<INT_SIZE;i++)
	{
		int_buf[i]=((uint32_t)data>>(8*(INT_SIZE-1-i)))&0x000000FF;
	}
	memcpy(buffer,int_buf,(unsigned int)sizeof(int));
}
#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
