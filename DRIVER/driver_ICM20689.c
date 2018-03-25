#include "driver_ICM20689.h"

u8 pBuf[14];
static int16_t DATA[6];
static u8 flag_SPI_fail=0;
//u8 flag_SPI_fail_test_send=0;
//u8 flag_SPI_fail_test_receive=0;
void ICM20689_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	int i=0;
//	for(i=0;i<5000;i++){}
//	ICM20689_WriteRegister(PWR_MGMT1,0x80,GPIOx,GPIO_Pin);
//	while(ICM20689_ReadRegister(PWR_MGMT1,GPIOx,GPIO_Pin)&0x80){}
	for(i=0;i<5000;i++){}
	ICM20689_WriteRegister(USER_CTRL,0x10,GPIOx,GPIO_Pin);
	for(i=0;i<5000;i++){}
	ICM20689_WriteRegister(CONFIG,0x02,GPIOx,GPIO_Pin);
	for(i=0;i<5000;i++){}
	ICM20689_WriteRegister(GYRO_CONFIG,0x10,GPIOx,GPIO_Pin);
	for(i=0;i<5000;i++){}
	ICM20689_WriteRegister(ACCEL_CONFIG,0x10,GPIOx,GPIO_Pin);
	for(i=0;i<5000;i++){}
	ICM20689_WriteRegister(ACCEL_CONFIG2,0x06,GPIOx,GPIO_Pin);
	for(i=0;i<5000;i++){}
	ICM20689_WriteRegister(PWR_MGMT1,0x01,GPIOx,GPIO_Pin);
	for(i=0;i<5000;i++){}
	ICM20689_WriteRegister(PWR_MGMT2,0x00,GPIOx,GPIO_Pin);
}

u8 ICM20689_ReadRegister(u8 add,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	u8 val=0;
	GPIO_ResetBits(GPIOx,GPIO_Pin);
	ICM20689_SPI1_ReadWriteByte(add|0x80);//发送寄存器地址	
	val = ICM20689_SPI1_ReadWriteByte(0x80);//读取寄存器数据	
	GPIO_SetBits(GPIOx,GPIO_Pin);	
	return val;  
}

void ICM20689_WriteRegister(u8 add,u8 val,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOx,GPIO_Pin); 	
 	ICM20689_SPI1_ReadWriteByte(add);
 	ICM20689_SPI1_ReadWriteByte(val);
	GPIO_SetBits(GPIOx,GPIO_Pin);
}
u8 ICM20689_SPI1_ReadWriteByte(u8 TxData)
{
	int retry=0;					 
	while((SPI1->SR&(1<<1))==0)
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
	SPI1->DR=TxData;
	retry=0;
	while((SPI1->SR&(1<<0))==0)
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
	return SPI1->DR; 
}

void ICM20689_Read(int16_t* omega_raw,int16_t* acc_raw,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	uint8_t i = 0;
	GPIO_ResetBits(GPIOx,GPIO_Pin);  //片选使能
 	ICM20689_SPI1_ReadWriteByte(ACCEL_XOUTH|0x80);//发送寄存器地址	
 	for(i=0;i<14;i++)
 	{
 		pBuf[i] = ICM20689_SPI1_ReadWriteByte(0x80);//读取寄存器数据;				
 	}
	
	GPIO_SetBits(GPIOx,GPIO_Pin); //关闭通讯
	if(!flag_SPI_fail)
	{
		DATA[0]=(((int16_t)pBuf[0]) << 8) | pBuf[1];
    	DATA[1]=(((int16_t)pBuf[2]) << 8) | pBuf[3];
    	DATA[2]=(((int16_t)pBuf[4]) << 8) | pBuf[5];
    	DATA[3]=(((int16_t)pBuf[8]) << 8) | pBuf[9];
    	DATA[4]=(((int16_t)pBuf[10]) << 8) | pBuf[11];
    	DATA[5]=(((int16_t)pBuf[12]) << 8) | pBuf[13];
	}
	flag_SPI_fail=0;
	acc_raw[0] = DATA[0];
	acc_raw[1] = DATA[1];
	acc_raw[2] = DATA[2];
	omega_raw[0] = DATA[3];
	omega_raw[1] = DATA[4];
	omega_raw[2] = DATA[5];	
}

void ICM20689_Read_Gyro(int16_t* omega_raw,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	u8 i = 0;
	GPIO_ResetBits(GPIOx,GPIO_Pin);  //片选使能
 	ICM20689_SPI1_ReadWriteByte(GYRO_XOUTH|0x80);//发送寄存器地址	
 	for(i=0;i<6;i++)
 	{
 		pBuf[i] = ICM20689_SPI1_ReadWriteByte(0x80);//读取寄存器数据;				
 	}
	
	GPIO_SetBits(GPIOx,GPIO_Pin); //关闭通讯
	if(!flag_SPI_fail)
	{
		DATA[3]=(((int16_t)pBuf[8]) << 8) | pBuf[9];
    	DATA[4]=(((int16_t)pBuf[10]) << 8) | pBuf[11];
    	DATA[5]=(((int16_t)pBuf[12]) << 8) | pBuf[13];
    	
	}
	flag_SPI_fail=0;
	omega_raw[0] = DATA[3];
	omega_raw[1] = DATA[4];
	omega_raw[2] = DATA[5];	
}
