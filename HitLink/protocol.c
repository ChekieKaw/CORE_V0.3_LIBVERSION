#include "protocol.h"
#include "stdio.h"
#include "string.h"

void put_float_buf(char *buffer, float data)
{
	char float_buf[FLOAT_SIZE];
	int i=0;
	for(i=0;i<FLOAT_SIZE;i++)
	{
		float_buf[i]=((uint32_t)data>>(8*(FLOAT_SIZE-i)))&0x0000000FF;
	}
//	float_buf[0]=(uint32_t)data>>(8*3);
//	float_buf[1]=((uint32_t)data>>(8*2))&0x000000FF;
//	float_buf[2]=((uint32_t)data>>(8*1))&0x000000FF;
//	float_buf[3]=((uint32_t)data&0x000000FF);
	strcat(buffer,float_buf);
}

void put_uint32_t_buf(char *buffer, uint32_t data)
{
	char uint32_t_buf[UINT32_SIZE];
	int i=0;
	for(i=0;i<UINT32_SIZE;i++)
	{
		uint32_t_buf[i]=(data>>(8*(UINT32_SIZE-1-i)))&0x000000FF;
	}
}

void put_int_buf(char *buffer, int data)
{
	char int_buf[INT_SIZE];
	int i=0;
	for(i=0;i<INT_SIZE;i++)
	{
		int_buf[i]=(data>>(8*(INT_SIZE-1-i)))&0x000000FF;
	}
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
