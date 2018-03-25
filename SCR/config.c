#include "config.h"
extern union uni_glb_cfg glb_cfg;

void cfg_init(void)
{
	glb_cfg.str.sv_type[0]=1;		glb_cfg.str.sv_type[1]=1;		glb_cfg.str.sv_type[2]=1;		glb_cfg.str.sv_type[3]=1;
	glb_cfg.str.sv_dir[0]=1;			glb_cfg.str.sv_dir[1]=1;		glb_cfg.str.sv_dir[2]=1;			glb_cfg.str.sv_dir[3]=1;
	glb_cfg.str.sv_midtrim[0]=0;	glb_cfg.str.sv_midtrim[1]=0;	glb_cfg.str.sv_midtrim[2]=0;	glb_cfg.str.sv_midtrim[3]=0;
	glb_cfg.str.sv_install=0x0001;
	glb_cfg.str.rp1=0x0001;
	glb_cfg.str.chn_KTP=28.0f;
	glb_cfg.str.chn_swash_limit=3000.0f;
	glb_cfg.str.chn_tail_limit_upper=3000.0f;
	glb_cfg.str.chn_tail_limit_lower=-3000.0f;
	glb_cfg.str.chn_P_inner[0]=45.0f;		glb_cfg.str.chn_P_inner[1]=40.0f;		glb_cfg.str.chn_P_inner[2]=40.0f;
	glb_cfg.str.chn_I_inner[0]=40.0f;		glb_cfg.str.chn_I_inner[1]=0.0f;		glb_cfg.str.chn_I_inner[2]=0.0f;
	glb_cfg.str.chn_P_outer[0]=0.0f;			glb_cfg.str.chn_P_outer[1]=1.7f;			glb_cfg.str.chn_P_outer[2]=1.7f;
	glb_cfg.str.chn_I_outer[0]=0.0f;			glb_cfg.str.chn_I_outer[1]=1.3f;		glb_cfg.str.chn_I_outer[2]=1.3;

	glb_cfg.str.bias_omega[0][0]=0.0f;		glb_cfg.str.bias_omega[0][1]=0.0f;		glb_cfg.str.bias_omega[0][2]=0.0f;
	glb_cfg.str.bias_omega[1][0]=0.0f;		glb_cfg.str.bias_omega[1][1]=0.0f;		glb_cfg.str.bias_omega[1][2]=0.0f;
	glb_cfg.str.scale_omega[0][0]=2.66e-4f;		glb_cfg.str.scale_omega[0][1]=2.66e-4f;		glb_cfg.str.scale_omega[0][2]=2.66e-4f;
	glb_cfg.str.scale_omega[1][0]=2.66e-4f;		glb_cfg.str.scale_omega[1][1]=2.66e-4f;		glb_cfg.str.scale_omega[1][2]=2.66e-4f;
	glb_cfg.str.output_sig_id[0]=0;			glb_cfg.str.output_sig_id[1]=1;			glb_cfg.str.output_sig_id[2]=2;
	glb_cfg.str.output_sig_id[3]=3;
	glb_cfg.str.bias_acc[0][0]=0;		glb_cfg.str.bias_acc[0][1]=0;		glb_cfg.str.bias_acc[0][2]=0;
	glb_cfg.str.bias_acc[1][0]=0;		glb_cfg.str.bias_acc[1][1]=0;		glb_cfg.str.bias_acc[1][2]=0;
	glb_cfg.str.scale_acc[0][0]=1.196e-3f;	glb_cfg.str.scale_acc[0][1]=1.196e-3f;	glb_cfg.str.scale_acc[0][2]=1.196e-3f;
	glb_cfg.str.scale_acc[1][0]=1.196e-3f;	glb_cfg.str.scale_acc[1][1]=1.196e-3f;	glb_cfg.str.scale_acc[1][2]=1.196e-3f;

}

void cfg_readfromflash(union uni_glb_cfg* glb_cfg)
{
	uint8_t flash_counter;
	for(flash_counter=0;flash_counter<CFG_LENGTH_INWORD;flash_counter++)
	{
		glb_cfg->inword[flash_counter]=*((uint32_t*)(0x0800FC00+flash_counter*4));
	}
}

void cfg_writetoflash(union uni_glb_cfg* glb_cfg)
{
	uint8_t flash_counter;
	Sec_IWDG_Slowdown();
	TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
	TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
	DMA_Cmd(DMA1_Channel5,DISABLE);
	DMA_Cmd(DMA1_Channel6,DISABLE);
	DMA_Cmd(DMA1_Channel3,DISABLE);
	USART_ITConfig(USART1, USART_IT_IDLE , DISABLE);
	USART_ITConfig(USART2, USART_IT_IDLE , DISABLE);
	USART_ITConfig(USART3, USART_IT_IDLE , DISABLE);
	IWDG_ReloadCounter();	
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	 
	FLASH_ErasePage(0x0800FC00);
	IWDG_ReloadCounter();
	for(flash_counter=0;flash_counter<CFG_LENGTH_INWORD;flash_counter++)
	{
		FLASH_ProgramWord((uint32_t)(0x0800FC00+flash_counter*4),glb_cfg->inword[flash_counter]);
		IWDG_ReloadCounter();
	}
	FLASH_Lock();
	
	Sec_IWDG_Speedup();
	IWDG_ReloadCounter();
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	DMA_Cmd(DMA1_Channel5,ENABLE);
	DMA_Cmd(DMA1_Channel6,ENABLE);
	DMA_Cmd(DMA1_Channel3,ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE , ENABLE);
	USART_ITConfig(USART2, USART_IT_IDLE , ENABLE);
	USART_ITConfig(USART3, USART_IT_IDLE , ENABLE);
}

