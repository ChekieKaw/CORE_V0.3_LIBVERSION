#include "driver_MS5611.h"

uint8_t MS5611_prom[16];
uint8_t ADC_temp[3];
uint16_t C1=0xA135;
uint16_t C2=0x8BD2;
uint16_t C3=0x5DA6;
uint16_t C4=0x5517;
uint16_t C5=0x83A3;
uint16_t C6=0x6F0E;

double T;
double P;

float p_buf[5];
	float sum=0.0f;


static u8 MS5611_SPI_ReadWriteByte(u8 TxData)
{
	int retry=0;					 
	while((AUXENSOR_1_SPIx->SR&(1<<1))==0)
	{
		retry++;
		if(retry>10000)
		{
			//flag_SPI_fail++;
			//flag_SPI_fail_test_send++;
			return 0;
		}
	}
	//SPI_I2S_SendData(SPI1,TxData);
	AUXENSOR_1_SPIx->DR=TxData;
	retry=0;
	while((AUXENSOR_1_SPIx->SR&(1<<0))==0)
	{
		retry++;
		if(retry>10000)
		{
			//flag_SPI_fail++;
			//flag_SPI_fail_test_receive++;
			return 0;
		}
	}	
	//return SPI_I2S_ReceiveData(SPI1);
	return AUXENSOR_1_SPIx->DR; 
}

void MS5611_Reset(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOx,GPIO_Pin);
	MS5611_SPI_ReadWriteByte(MS5611_CMD_Reset);
	delay5ms();	
	GPIO_SetBits(GPIOx,GPIO_Pin); 
}

void MS5611_Prom_Read(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	uint8_t i=0;
	for(i = 0;i < 8;i ++)
	{
		GPIO_ResetBits(GPIOx,GPIO_Pin);
		MS5611_SPI_ReadWriteByte(MS5611_PROM_Reg+i*2);
		MS5611_prom[2*i]=MS5611_SPI_ReadWriteByte(0x00);
		MS5611_prom[2*i+1]=MS5611_SPI_ReadWriteByte(0x00);
		GPIO_SetBits(GPIOx,GPIO_Pin);
	}
	C1=MS5611_prom[2]<<8|MS5611_prom[3];
	C2=MS5611_prom[4]<<8|MS5611_prom[5];
	C3=MS5611_prom[6]<<8|MS5611_prom[7];
	C4=MS5611_prom[8]<<8|MS5611_prom[9];
	C5=MS5611_prom[10]<<8|MS5611_prom[11];
	C6=MS5611_prom[12]<<8|MS5611_prom[13];
}

void MS5611_Tpt_Conv(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOx,GPIO_Pin);
	MS5611_SPI_ReadWriteByte(MS5611_CMD_CONV_Temperature);
	GPIO_SetBits(GPIOx,GPIO_Pin);
}

void MS5611_Prs_Conv(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOx,GPIO_Pin);
	MS5611_SPI_ReadWriteByte(MS5611_CMD_CONV_Pressure);
	GPIO_SetBits(GPIOx,GPIO_Pin);
}

uint32_t MS5611_ADC_Read(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOx,GPIO_Pin);
	MS5611_SPI_ReadWriteByte(MS5611_CMD_ADC_Read);
	ADC_temp[0]=MS5611_SPI_ReadWriteByte(0x00);
	ADC_temp[1]=MS5611_SPI_ReadWriteByte(0x00);
	ADC_temp[2]=MS5611_SPI_ReadWriteByte(0x00);
	GPIO_SetBits(GPIOx,GPIO_Pin);
	return (ADC_temp[0]<<16 | ADC_temp[1]<<8 | ADC_temp[2]);
}

void MS5611_Update(uint32_t D1, uint32_t D2,int32_t* pTEMP,int32_t* pPRESSURE)
{
	double dT;
	//double T;
	double OFF;
	double SENS;
	//double P;
	uint8_t i;
	
	dT=D2-(double)C5*256;
	OFF=(double)C2*65536+C4*dT/128;
	SENS=(double)C1*32768+C3*dT/256;
	T=2000+dT*C6/8388608;
	P=(D1*SENS/2097152-OFF)/32768;
	
	for(i=0;i<4;i++)p_buf[i]=p_buf[i+1];
	p_buf[4]=P;
	
	*pTEMP=(int32_t)T;
	//*pPRESSURE=(int32_t)P;
	sum=0.0f;
	for(i=0;i<5;i++)sum+=p_buf[i];
	*pPRESSURE=(int32_t)sum*0.2f;
}
