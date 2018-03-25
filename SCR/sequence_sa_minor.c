#include "sequence_sa_minor.h"

static float cali_omega[2][3];

void sq_sa_cali_sampling(
	struct str_glb_identity* sidentity,
	struct str_sa_sensor* ssensor,
	struct str_glb_cali* scali)
{
	static uint16_t i=0;
	if(i==0)
	{
		uint8_t j;
		for(j=0;j<3;j++)
		{
			scali->acc_raw[0][sidentity->flag_cali-1][j]=0.0f;
		}
		for(j=0;j<3;j++)
		{
			scali->acc_raw[1][sidentity->flag_cali-1][j]=0.0f;
		}
	}
	if(i<400)
	{
		uint8_t j;
		for(j=0;j<3;j++)
		{
			scali->acc_raw[0][sidentity->flag_cali-1][j]+=ssensor->acc_raw[0][j];
		}
		for(j=0;j<3;j++)
		{
			scali->acc_raw[1][sidentity->flag_cali-1][j]+=ssensor->acc_raw[1][j];
		}
		i++;
	}
	else
	{
		uint8_t j;
		for(j=0;j<3;j++)scali->acc_raw[0][sidentity->flag_cali-1][j]*=0.0025f;
		for(j=0;j<3;j++)scali->acc_raw[1][sidentity->flag_cali-1][j]*=0.0025f;
		sidentity->flag_cali=0;
		i=0;
	}
}

void sq_sa_cali_update(
	struct str_glb_identity* sidentity,
	struct str_glb_cfg* scfg,
	struct str_glb_cali* scali)
{
//	scfg->acc_scale[0]=fabs(7740.0f/(lite_cali->acc_raw[0][0]-lite_cali->acc_raw[1][0]));
//	scfg->acc_scale[1]=fabs(7740.0f/(lite_cali->acc_raw[2][1]-lite_cali->acc_raw[3][1]));
//	scfg->acc_scale[2]=fabs(7740.0f/(lite_cali->acc_raw[4][2]-lite_cali->acc_raw[5][2]));
//	scfg->acc_bias[0]=(lite_cali->acc_raw[0][0]+lite_cali->acc_raw[1][0])*0.5f;
//	scfg->acc_bias[1]=(lite_cali->acc_raw[2][1]+lite_cali->acc_raw[3][1])*0.5f;
//	scfg->acc_bias[2]=(lite_cali->acc_raw[4][2]+lite_cali->acc_raw[5][2])*0.5f;

//	sidentity->flag_caliupdate=0;
}

void sq_sa_cali_gyro(
	struct str_glb_identity* sidentity,
	struct str_sa_sensor* ssensor,
	struct str_glb_cfg* scfg)
{
	static uint16_t i=0;
	if(i==0)
	{
		uint8_t j;
		for(j=0;j<3;j++)
		{
			cali_omega[0][j]=0.0f;
		}
		for(j=0;j<3;j++)
		{
			cali_omega[1][j]=0.0f;
		}
	}
	if(i<4000)
	{
		uint8_t j;
		for(j=0;j<3;j++)
		{
			cali_omega[0][j]+=ssensor->omega_raw[0][j];
		}
		for(j=0;j<3;j++)
		{
			cali_omega[1][j]+=ssensor->omega_raw[1][j];
		}
		i++;
	}
	else
	{
		uint8_t j;
		for(j=0;j<3;j++)
		{
			scfg->bias_omega[0][j]=cali_omega[0][j]*2.5e-4f;
		}
		for(j=0;j<3;j++)
		{
			scfg->bias_omega[1][j]=cali_omega[1][j]*2.5e-4f;
		}
		sidentity->flag_caligyro=0;
		i=0;
	}
}

void sq_sa_cali_acc_quick(
	struct str_glb_identity* sidentity,
	struct str_sa_sensor* ssensor,
	struct str_glb_cali* scali,
	struct str_glb_cfg* scfg)
{
//	static uint16_t i=0;
//		if(i==0)
//	{
//		uint8_t j;
//		for(j=0;j<3;j++)
//		{
//			lite_cali->acc_raw[4][j]=0.0f;
//		}
//	}
//	if(i<400)
//	{
//		uint8_t j;
//		for(j=0;j<3;j++)
//		{
//			lite_cali->acc_raw[4][j]+=lite_sensor->acc_raw[j];
//		}
//		i++;
//	}
//	else
//	{
//		uint8_t j;
//		for(j=0;j<3;j++)lite_cali->acc_raw[4][j]*=0.0025f;
//		lite_cfg->acc_bias[0]=lite_cali->acc_raw[4][0];
//		lite_cfg->acc_bias[1]=lite_cali->acc_raw[4][1];
//		lite_cfg->acc_bias[2]=lite_cali->acc_raw[4][2]-(3870.0f/lite_cfg->acc_scale[2]);
//		lite_identity->flag_caliaccquick=0;
//		i=0;
//		lite_identity->flag_cancmd_send=1;
//	}
}
