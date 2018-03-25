#include "main.h"
#include "hitlink.h"
#include "string.h"
uint32_t KEY[3]={0x066BFF49,0x48528472,0x67194853};

float dt=0.0f;
float tscale=0.0f;

/*FLAGS*/
uint8_t flag_readkey=0;
static uint8_t n_iteration=0;
uint8_t i;
uint8_t dataserial=0;
int flag=1;

/*USART*/
uint16_t USART1_RX_STA;
uint8_t USART1_RX_BUF[64];
uint8_t USART1_TX_BUF[64];
uint16_t USART2_RX_STA;
uint8_t USART2_RX_BUF[64];
uint8_t USART2_TX_BUF[64];
uint16_t USART3_RX_STA;
uint8_t USART3_RX_BUF[64];

uint16_t AD_BUF[1];

struct str_glb_state glb_state;
struct str_sa_sensor sa_sensor;
struct str_glb_identity glb_identity;
struct str_glb_input glb_input;
struct str_glb_output glb_output;
struct str_glb_toc glb_toc;
union uni_glb_cfg glb_cfg;

extern uint16_t DSM_SVPOS[28];

/*Hitlink 协议数据*/
hitlink_msg msg;
hitlink_heartbeat_t heartbeat;
hitlink_attitute_t attitute;



 int main(void)
 {
	GPIO_Configuration();
	RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);
	 delay5ms();
	 
	 //go to system_stm32f10x.c line 1054 to set the PLL with a different HSE
//		if(Sec_Check_Key0(KEY))while(1);
//		if(Sec_Check_Key1(KEY))while(1);
//		if(Sec_Check_Key2(KEY))while(1);
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST))
	{
		System_Init();
		Sec_IWDG_Init();
		RCC_ClearFlag();
	}
	else
	{
 		System_Init();
		Sec_IWDG_Init();
		RCC_ClearFlag();
	}
	
	glb_state.q[0]=1.0f;
	glb_state.q[1]=0.0f;
	glb_state.q[2]=0.0f;
	glb_state.q[3]=0.0f;
	glb_state.q2[0]=1.0f;
	glb_state.q2[1]=0.0f;
	glb_state.q2[2]=0.0f;
	glb_state.q2[3]=0.0f;
	glb_state.q3[0]=1.0f;
	glb_state.q3[1]=0.0f;
	glb_state.q3[2]=0.0f;
	glb_state.q3[3]=0.0f;
	glb_state.flag=1;
	sa_sensor.ahrs_dt=2.5e-3f;
	//for(i=0;i<64;i++)
	//{
		//USART2_TX_BUF[i]=i+48;
	//}
	cfg_readfromflash(&glb_cfg);
	
	MS5611_Reset(GPIOA, GPIO_Pin_1);
	ICM20689_Init(GPIOA,GPIO_Pin_15);
	ICM20689_Init(GPIOB,GPIO_Pin_12);
	MS5611_Prom_Read(GPIOA, GPIO_Pin_1);
	MS5611_Tpt_Conv(GPIOA,GPIO_Pin_1);
	ICM20689_Init(GPIOA,GPIO_Pin_15);
	ICM20689_Init(GPIOB,GPIO_Pin_12);

	SysTick->LOAD=0xFFFFFF;	  		//SysTick预装载寄存器设定装载值 16777215
	SysTick->CTRL=0x05;				//SysTick使能 时钟源 内核时钟 72MHz	
	tscale=1.0/72000000.0;			//真实时间比例尺
	SysTick->VAL=0;
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	DMA_Cmd(DMA1_Channel5,ENABLE);//usart1
	DMA_Cmd(DMA1_Channel6,ENABLE);//usart2
	DMA_Cmd(DMA1_Channel3,ENABLE);//usart3
	
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
 	  
  while(1)
	{
		if(flag_readkey)
		{
			Sec_Get_Key(KEY);
			flag_readkey=0;
		}
		if(glb_identity.flag_ms5611update)
		{
			//SysTick->VAL=0;
			MS5611_Update(sa_sensor.ms5611_d1,sa_sensor.ms5611_d2,&sa_sensor.ms5611_temp,&sa_sensor.ms5611_press);
			//dt=(float)(((SysTick->LOAD)-(SysTick->VAL))*tscale);
			glb_identity.flag_ms5611update=0;
		}
		if(glb_identity.flag_cfg_init)
		{
			cfg_init();
			glb_identity.flag_cfg_init=0;
		}
		if(glb_identity.flag_flash_execute)
		{
			uint8_t i;
			cfg_writetoflash(&glb_cfg);
			glb_identity.flag_flash_execute=0;
		}
	}
 }
 
 void Datainput(void)
 {
	 union char2float temp;
	 union char2uint16 crcdata;
	 uint8_t j;
	 uint8_t count;
	 uint8_t len = 23;  
   uint16_t crc = 0;  
   uint8_t *ptr = USART2_TX_BUF;  
	 
	 
//	 
//	 USART2_TX_BUF[0]=0xFE;	//包头
//	 USART2_TX_BUF[1]=dataserial; //包序列号
//	 USART2_TX_BUF[2]=25+48;	//包长(字符形式的数字)
//	 USART2_TX_BUF[3]=1;			//姿态数据包
//	 
	 //发送心跳包
	 if(flag){
		heartbeat.time_stamp = 0x11111111;//心跳包内容初始化
		heartbeat.type = Quadrotor;
		heartbeat.system_state = Auto;
		heartbeat.connect_flag = UNAVALIABLE;
	 hitlink_init(&msg);
	 hitlink_heartbeat_pack(&heartbeat,&msg);//心跳包内容打包到payload里面
	 }
	 else {
	 //发送姿态数据
	 attitute.time_stamp = 0x00000000;//填入姿态数据
	 attitute.roll = glb_state.euler[0];
	 attitute.pitch = glb_state.euler[1];
	 attitute.yaw = glb_state.euler[2];
	 attitute.roll_speed = glb_state.omega[0];
	 attitute.pitch_speed = glb_state.omega[1];
	 attitute.yaw_speed = glb_state.omega[2];
	 //memset((msg.payload),0,HITLINK_MAX_LEN);
	 hitlink_init(&msg);
	 hitlink_attitute_pack(&attitute,&msg);
	 }
	 msg.sequence = dataserial;//添加序列号		 
	 hit_link_msg2buffer(&msg,(char*)USART2_TX_BUF);//全部消息打包，发送
	 flag = !flag;
	 
	 
///*	 for(j=0;j<4;j++)					//四元数发送
//	 {
//	 temp.in_float=glb_state.q[j];
//	 for(i=0;i<3;i++)
//	 {
//		 USART2_TX_BUF[i+4*j+4]=temp.in_char[i];
//	 }
//	 count=i+4*j+4;
//	}*/
//	 
//		 for(j=0;j<3;j++)					//欧拉角发送
//	 {
//	 temp.in_float=glb_state.euler[j];
//	 for(i=0;i<3;i++)
//	 {
//		 USART2_TX_BUF[i+3*j+4]=temp.in_char[i];
//	 }
//	}
//	 
//			 for(j=0;j<3;j++)					//角速度发送
//	 {
//	 temp.in_float=glb_state.omega[j];
//	 for(i=0;i<3;i++)
//	 {
//		 USART2_TX_BUF[i+3*j+13]=temp.in_char[i];
//	 }
//	}
//	 
//	 while( len-- ) {  
//      for(i = 0x80; i != 0; i = i >> 1) {  
//        if((crc & 0x8000) != 0) {  
//           crc = crc << 1;  
//           crc = crc ^ 0x1021;  
//        }  
//        else {  
//           crc = crc << 1;  
//        }  
//        if((*ptr & i) != 0) {  
//          crc = crc ^ 0x1021;   
//        }  
//     }  
//     ptr++;  
//   } 
//	 crcdata.in_uint16=crc;
//	 USART2_TX_BUF[23]=crcdata.in_char[0];
//	 USART2_TX_BUF[24]=crcdata.in_char[1];
//	 
//	 USART2_TX_BUF[25]=0xFE;	//包头
//	 USART2_TX_BUF[26]=dataserial; //包序列号
//	 USART2_TX_BUF[27]=7+48;	//包长(字符形式的数字)
//	 USART2_TX_BUF[28]=0;			//心跳包
//	 USART2_TX_BUF[29]=1;				//飞行器类型
//	 USART2_TX_BUF[30]=1; 			//连接状态
//	 USART2_TX_BUF[31]=1;	//系统状态
//	 
//	for(i=32;i<64;i++)
//	{
//		USART2_TX_BUF[i]=0x00;
//	}
	
	if(dataserial==255)
	 {dataserial=0;}
	 else{
	 dataserial++;}
	
/*	for(j=0;j<7;j++)
	{
	for(i=0;i<8;i++)
	{
		USART2_TX_BUF[i+8*j]=i+48;
	}
}
	for(j=0;j<64;j++)
{
	USART2_TX_BUF[j]=j+48;
}*/
	 
 }


 
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update))
	{
//		static uint8_t n_iteration=0;
		SysTick->VAL=0;
		
		if(n_iteration==0)
		{
			glb_identity.flag_caligyro=1;
			n_iteration=1;
		}
		if(glb_identity.flag_caligyro)
		{
			sq_sa_cali_gyro(&glb_identity,&sa_sensor,&glb_cfg.str);
		}

		
		sq_lite_major_state_update(&glb_identity,&sa_sensor,&glb_state,&glb_toc,&glb_input,&glb_cfg.str);
		sq_sa_major_control_generate(&glb_state,&glb_identity,&glb_toc,&glb_input,&glb_output,&glb_cfg.str);
		if(glb_identity.flag_rx_ready)
		{
			sq_sa_major_control_execuate(&glb_input,&glb_output,&glb_cfg.str);
		}
		
//		if(n_iteration>7)
//		{
//			n_iteration=1;
//		}
//		else
//		{
//			n_iteration++;
//		}
//		if(n_iteration==4)
//		{
//		sa_sensor.ms5611_d2=MS5611_ADC_Read(GPIOA,GPIO_Pin_1);
//		MS5611_Prs_Conv(GPIOA,GPIO_Pin_1);
//		}
//		if(n_iteration==8)
//		{
//		sa_sensor.ms5611_d1=MS5611_ADC_Read(GPIOA,GPIO_Pin_1);
//		MS5611_Tpt_Conv(GPIOA,GPIO_Pin_1);
//		glb_identity.flag_ms5611update=1;
//		}
//	
//		ICM20689_Read(sa_sensor.omega_raw[0],sa_sensor.acc_raw[0],GPIOA,GPIO_Pin_15);
//		ICM20689_Read(sa_sensor.omega_raw[1],sa_sensor.acc_raw[1],GPIOB,GPIO_Pin_12);

		if(glb_identity.flag_caligyro)
		{
			sq_sa_cali_gyro(&glb_identity,&sa_sensor,&glb_cfg.str);
		}

		dt=(float)(((SysTick->LOAD)-(SysTick->VAL))*tscale);
		
		//Transmit data
		Datainput();
		 DMA_Cmd(DMA1_Channel7, DISABLE);	
		DMA1_Channel7->CNDTR = 64;
			DMA_ClearFlag(DMA1_FLAG_TC7);
	//USART2_RX_STA=64-(DMA1_Channel6->CNDTR);	
	//DMA1_Channel6->CNDTR=64;
	//DMA_ClearFlag(DMA1_FLAG_TC6);
	DMA_Cmd(DMA1_Channel7, ENABLE);

		IWDG_ReloadCounter();		
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update))
	{
		//dt=(float)(((SysTick->LOAD)-(SysTick->VAL))*tscale);
		//SysTick->VAL=0;
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}


 void USART1_IRQHandler(void)
{
	uint8_t res;	

	DMA_Cmd(DMA1_Channel5, DISABLE);
	USART1_RX_STA=64-(DMA1_Channel5->CNDTR);
	
	
	DMA1_Channel5->CNDTR=64;
	DMA_ClearFlag(DMA1_FLAG_TC5);
	DMA_Cmd(DMA1_Channel5, ENABLE);
	res=USART1->SR;
	res=USART1->DR;
	
	
//	DMA1_Channel4->CMAR=(uint32_t)(&msg_o2m_rx);
//	DMA_Cmd(DMA1_Channel4,DISABLE);
//	DMA_ClearFlag(DMA1_FLAG_TC4);
//	DMA_SetCurrDataCounter(DMA1_Channel4,sizeof(msg_o2m_rx));
//	DMA_Cmd(DMA1_Channel4, ENABLE);
//	while(!DMA_GetFlagStatus(DMA1_FLAG_TC4));
}

void USART2_IRQHandler(void)
{
	uint8_t res;  

	DMA_Cmd(DMA1_Channel6, DISABLE);
	USART2_RX_STA=64-(DMA1_Channel6->CNDTR);	
	
	DMA1_Channel6->CNDTR=64;
	DMA_ClearFlag(DMA1_FLAG_TC6);
	DMA_Cmd(DMA1_Channel6, ENABLE);
	res=USART2->SR;
	res=USART2->DR;
}

 void USART3_IRQHandler(void)
{
	uint8_t res;   

	DMA_Cmd(DMA1_Channel3, DISABLE);
	USART3_RX_STA=64-(DMA1_Channel3->CNDTR);
	
	
	DMA1_Channel3->CNDTR=64;
	DMA_ClearFlag(DMA1_FLAG_TC3);
	DMA_Cmd(DMA1_Channel3, ENABLE);
	res=USART3->SR;
	res=USART3->DR;	
	
#ifdef USE_DSM_SATELLITE
	com_decipher_dsm(USART3_RX_STA,USART3_RX_BUF,&glb_input,&glb_identity,&glb_toc);
#else	
	com_decipher_sbus(USART3_RX_STA,USART3_RX_BUF,&glb_input,&glb_identity,&glb_toc);
#endif
	
//	sprintf(USART1_TX_BUF,"%f",(float)DSM_SVPOS[2]);
//	USART1_TX_BUF[8]=0x0D;
//	USART1_TX_BUF[9]=0x0A;
//	DMA1_Channel4->CMAR=(uint32_t)(USART1_TX_BUF);
//	DMA_Cmd(DMA1_Channel4,DISABLE);
//	DMA_ClearFlag(DMA1_FLAG_TC4);
//	DMA_SetCurrDataCounter(DMA1_Channel4,10);
//	DMA_Cmd(DMA1_Channel4, ENABLE);
//	while(!DMA_GetFlagStatus(DMA1_FLAG_TC4));
}
