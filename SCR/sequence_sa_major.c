#include "sequence_sa_major.h"

#ifdef FIR_IS_ON
	float fir_acc_temp[3];
	float fir_acc_pool[3][64];
	float fir_coefficient[64]={
 0.0036876274601339953,             
-0.0039083518272118294,              
-0.0035246615983618246,              
-0.0037804496816476732,               
-0.0043474663084984103,               
-0.0050292074411847892,               
-0.005705436777992021 ,               
-0.0062846465036508724,              
-0.0066869182426247216,               
-0.0068391713956120074,               
-0.0066750541022948572,               
-0.0061334150870683982,               
-0.0051623241028387976,               
-0.0037186895172336958,               
-0.0017741757128695345,               
 0.00068580987639609275,              
 0.0036564851638691848,               
 0.0071165803973998751,               
 0.011023440935828081,                
 0.015317924888012886,                
 0.019920444707427314,                
 0.024738505230870161,               
 0.029663661797993613,                
 0.034581344134232729,                
 0.039367230674983163,                
 0.043898915274410755,                
 0.048051103964413137,                
 0.051710872840346367,                
 0.054771007585481105,                
 0.057150983719312987,                
 0.058784891161800676,                
 0.059603801074131484,                
 0.059603801074131484,                
 0.058784891161800676,                
 0.057150983719312987,                
 0.054771007585481105,                
 0.051710872840346367,                
 0.048051103964413137,                
 0.043898915274410755,               
 0.039367230674983163,                
 0.034581344134232729,                
 0.029663661797993613,                
 0.024738505230870161,                
 0.019920444707427314,                
 0.015317924888012886,                
 0.011023440935828081,                
 0.0071165803973998751,               
 0.0036564851638691848,              
 0.00068580987639609275,              
-0.0017741757128695345,               
-0.0037186895172336958,               
-0.0051623241028387976,               
-0.0061334150870683982,               
-0.0066750541022948572,               
-0.0068391713956120074,               
-0.0066869182426247216,               
-0.0062846465036508724,               
-0.005705436777992021,                
-0.0050292074411847892,               
-0.0043474663084984103,               
-0.0037804496816476732,               
-0.0035246615983618246,               
-0.0039083518272118294,               
 0.0036876274601339953};
#endif
 
 void AHRS_test(struct str_sa_sensor* lite_sensor,struct str_glb_state* lite_state)
 {
	 	float w[3],w1[3],w2[3]; 
		float q0[4],k1[4],k2[4],k3[4],k4[4],qfinal[4],q1[4],q2[4],q3[4],qsum,qfinal2[4],qsum2;
		uint8_t i;	
		float h=2.0*lite_sensor->ahrs_dt;
		float euler2[3];
		float euler[3];
		if(lite_state->flag > 0)
		{
			w[0]=0;w[1]=0;w[2]=0;
			lite_state->flag=0;
//			qfinal2[0]=1;qfinal2[1]=0;qfinal2[2]=0;qfinal2[3]=0;
		}
		else{
			w[0]=lite_state->omega[0];w[1]=lite_state->omega[1];w[2]=lite_state->omega[2];
		}
		w1[0]=lite_sensor->omega[0];w1[1]=lite_sensor->omega[1];w1[2]=lite_sensor->omega[2];
		
		q0[0]=lite_state->q3[0];q0[1]=lite_state->q3[1];q0[2]=lite_state->q3[2];q0[3]=lite_state->q3[3];
		qfinal2[0]=lite_state->q2[0];qfinal2[1]=lite_state->q2[1];qfinal2[2]=lite_state->q2[2];qfinal2[3]=lite_state->q2[3];
//		w2[0]=(w[0]+w1[0])/2.0;		w2[1]=(w[1]+w1[1])/2.0;		w2[2]=(w[2]+w1[2])/2.0;
//		
		k1[0]=(-0.5)*(w[0]*q0[1]+w[1]*q0[2]+w[2]*q0[3]);
		k1[1]=0.5*(w[0]*q0[0]+w[2]*q0[2]-w[1]*q0[3]);
		k1[2]=0.5*(w[1]*q0[0]-w[2]*q0[1]+w[0]*q0[3]);
		k1[3]=0.5*(w[2]*q0[0]+w[1]*q0[1]-w[0]*q0[2]);
		
		q1[0]=q0[0]+0.5*h*k1[0];q1[1]=q0[1]+0.5*h*k1[1];q1[2]=q0[2]+0.5*h*k1[2];q1[3]=q0[3]+0.5*h*k1[3];

		w[0]=(w[0]+w1[0])/2.0;		w[1]=(w[1]+w1[1])/2.0;		w[2]=(w[2]+w1[2])/2.0;
		
		k2[0]=(-0.5)*(w[0]*q1[1]+w[1]*q1[2]+w[2]*q1[3]);
		k2[1]=0.5*(w[0]*q1[0]+w[2]*q1[2]-w[1]*q1[3]);
		k2[2]=0.5*(w[1]*q1[0]-w[2]*q1[1]+w[0]*q1[3]);
		k2[3]=0.5*(w[2]*q1[0]+w[1]*q1[1]-w[0]*q1[2]);
		
		q2[0]=q0[0]+0.5*h*k2[0];q2[1]=q0[1]+0.5*h*k2[1];q2[2]=q0[2]+0.5*h*k2[2];q2[3]=q0[3]+0.5*h*k2[3];
		
		k3[0]=(-0.5)*(w[0]*q2[1]+w[1]*q2[2]+w[2]*q2[3]);
		k3[1]=0.5*(w[0]*q2[0]+w[2]*q2[2]-w[1]*q2[3]);
		k3[2]=0.5*(w[1]*q2[0]-w[2]*q2[1]+w[0]*q2[3]);
		k3[3]=0.5*(w[2]*q2[0]+w[1]*q2[1]-w[0]*q2[2]);
		
		q3[0]=q0[0]+0.5*h*k3[0];q3[1]=q0[1]+0.5*h*k3[1];q3[2]=q0[2]+0.5*h*k3[2];q3[3]=q0[3]+0.5*h*k3[3];

		k4[0]=(-0.5)*(w1[0]*q3[1]+w1[1]*q3[2]+w1[2]*q3[3]);
		k4[1]=0.5*(w1[0]*q3[0]+w1[2]*q3[2]-w1[1]*q3[3]);
		k4[2]=0.5*(w1[1]*q3[0]-w1[2]*q3[1]+w1[0]*q3[3]);
		k4[3]=0.5*(w1[2]*q3[0]+w1[1]*q3[1]-w1[0]*q3[2]);

		for(i=0;i<4;i++)
		{
			qfinal[i]=q0[i]+(h/12.0)*(k1[i]+2*k2[i]+2*k3[i]+k4[i]);
		}	

//		qfinal[0] += 0.5 * (-q0[1]*w1[0] - q0[2]*w1[1] - q0[3]*w1[2])* h/6;
//		qfinal[1] += 0.5 * (q0[0]*w1[0] + q0[2]*w1[2] - q0[3]*w1[1])* h/6;
//		qfinal[2] += 0.5 * (q0[0]*w1[1] - q0[1]*w1[2] + q0[3]*w1[0])* h/6;
//		qfinal[3] += 0.5 * (q0[0]*w1[2] + q0[1]*w1[1] - q0[2]*w1[0])* h/6;	
		

		qfinal2[0] += 0.5 * (-qfinal2[1]*w1[0] - qfinal2[2]*w1[1] - qfinal2[3]*w1[2])* h/2;
		qfinal2[1] += 0.5 * (qfinal2[0]*w1[0] + qfinal2[2]*w1[2] - qfinal2[3]*w1[1])* h/2;
		qfinal2[2] += 0.5 * (qfinal2[0]*w1[1] - qfinal2[1]*w1[2] + qfinal2[3]*w1[0])* h/2;
		qfinal2[3] += 0.5 * (qfinal2[0]*w1[2] + qfinal2[1]*w1[1] - qfinal2[2]*w1[0])* h/2;	
		qsum=sqrt(qfinal[0]*qfinal[0]+qfinal[1]*qfinal[1]+qfinal[2]*qfinal[2]+qfinal[3]*qfinal[3]);
		qsum2=sqrt(qfinal2[0]*qfinal2[0]+qfinal2[1]*qfinal2[1]+qfinal2[2]*qfinal2[2]+qfinal2[3]*qfinal2[3]);
		for(i=0;i<4;i++)
		{
			qfinal[i]=qfinal[i]/qsum;
			qfinal2[i]=qfinal2[i]/qsum2;
			lite_state->q3[i]=qfinal[i];	
			lite_state->q2[i]=qfinal2[i];
		}
			
		lite_state->euler3[2]=(atan2f(2.0f*(qfinal[0]*qfinal[1] + qfinal[2]*qfinal[3]),1 - 2.0f*(qfinal[1]*qfinal[1] + qfinal[2]*qfinal[2]))/M_PI)*180;
		lite_state->euler3[1]=-(asin(2.0f*(qfinal[0]*qfinal[2] - qfinal[1]*qfinal[3]))/M_PI)*180;
		lite_state->euler3[0]=(-90)+(atan2f(2.0f*(qfinal[1]*qfinal[2] + qfinal[0]*qfinal[3]),1- 2.0f*(qfinal[2]*qfinal[2] + qfinal[3]*qfinal[3]) )/M_PI)*180;
		
		lite_state->euler2[2]=(atan2f(2.0f*(qfinal2[0]*qfinal2[1] + qfinal2[2]*qfinal2[3]),1 - 2.0f*(qfinal2[1]*qfinal2[1] + qfinal2[2]*qfinal2[2]))/M_PI)*180;
		lite_state->euler2[1]=-(asin(2.0f*(qfinal2[0]*qfinal2[2] - qfinal2[1]*qfinal2[3]))/M_PI)*180;
		lite_state->euler2[0]=(-90)+(atan2f(2.0f*(qfinal2[1]*qfinal2[2] + qfinal2[0]*qfinal2[3]),1- 2.0f*(qfinal2[2]*qfinal2[2] + qfinal2[3]*qfinal2[3]) )/M_PI)*180;

		euler[0]=lite_state->euler[0];
		euler[1]=lite_state->euler[1];
		euler[2]=lite_state->euler[2];

		lite_state->omega[0]=lite_sensor->omega[0];		lite_state->omega[1]=lite_sensor->omega[1];		lite_state->omega[2]=lite_sensor->omega[2];
 }
 

void sq_lite_major_state_update(
	struct str_glb_identity* glb_identity,
	struct str_sa_sensor* sa_sensor,
	struct str_glb_state* glb_state,
	struct str_glb_toc* glb_toc,
	struct str_glb_input* glb_input,
	struct str_glb_cfg* glb_cfg)
{
	static uint8_t n_iteration=0;
	static uint8_t power_on_iteration=0;
	uint8_t i;
	if(n_iteration>7)
	{
		n_iteration=1;
	}
	else
	{
		n_iteration++;
	}
	if(power_on_iteration<200)
	{
		power_on_iteration++;
		if(power_on_iteration==200){glb_identity->flag_ahrs_ready=1;}
	}
//start of toc update ////////////////////////////////
	if(glb_toc->rx<40)
	{
		glb_toc->rx++;
	}
	else
	{
		glb_identity->flag_rx_online=0;
	}
//end of toc update //////////////////////////////////
	if(!glb_identity->flag_ahrs_ready)
	{
		if(power_on_iteration==0){sa_sensor->IMU_beta=100.0f;}
		if(power_on_iteration==20){sa_sensor->IMU_beta=50.0f;}
		if(power_on_iteration==60){sa_sensor->IMU_beta=10.0f;}
		if(power_on_iteration==199){sa_sensor->IMU_beta=0.05f;}
	}
	//decide operating mode ///////////////////////////////////////////////////////////////////
	glb_identity->operating_mode=1;
	//read from baro meter ms56xx /////////////////////////////////////////////////////////////	
	if(n_iteration==4)
	{
		sa_sensor->ms5611_d2=MS5611_ADC_Read(GPIOA,GPIO_Pin_1);
		MS5611_Prs_Conv(GPIOA,GPIO_Pin_1);
	}
	if(n_iteration==8)
	{
		sa_sensor->ms5611_d1=MS5611_ADC_Read(GPIOA,GPIO_Pin_1);
		MS5611_Tpt_Conv(GPIOA,GPIO_Pin_1);
		glb_identity->flag_ms5611update=1;
	}

	//read from ICM20689 /////////////////////////////////////////////////////////
	ICM20689_Read(sa_sensor->omega_raw[0],sa_sensor->acc_raw[0],GPIOA,GPIO_Pin_15);
	ICM20689_Read(sa_sensor->omega_raw[1],sa_sensor->acc_raw[1],GPIOB,GPIO_Pin_12);
	
//	for(i=0;i<3;i++)sa_sensor->omega[i]=(sa_sensor->omega_raw[0][i]-glb_cfg->bias_omega[0][i])*glb_cfg->scale_omega[0][i]
//																			+(sa_sensor->omega_raw[1][i]-glb_cfg->bias_omega[1][i])*glb_cfg->scale_omega[1][i];
		sa_sensor->omega[0]=(sa_sensor->omega_raw[0][1]-glb_cfg->bias_omega[0][1])*glb_cfg->scale_omega[0][1]
												-(sa_sensor->omega_raw[1][1]-glb_cfg->bias_omega[1][1])*glb_cfg->scale_omega[1][1];
		sa_sensor->omega[1]=(sa_sensor->omega_raw[0][0]-glb_cfg->bias_omega[0][0])*glb_cfg->scale_omega[0][0]
												-(sa_sensor->omega_raw[1][0]-glb_cfg->bias_omega[1][0])*glb_cfg->scale_omega[1][0];
		sa_sensor->omega[2]=-(sa_sensor->omega_raw[0][2]-glb_cfg->bias_omega[0][2])*glb_cfg->scale_omega[0][2]
												-(sa_sensor->omega_raw[1][2]-glb_cfg->bias_omega[1][2])*glb_cfg->scale_omega[1][2];
	
//	for(i=0;i<3;i++)glb_state->omega[i]=sa_sensor->omega[i];

//	for(i=0;i<3;i++)sa_sensor->acc[i]=(sa_sensor->acc_raw[0][i]-glb_cfg->bias_acc[0][i])*glb_cfg->scale_acc[0][i]
//																		+(sa_sensor->acc_raw[1][i]-glb_cfg->bias_acc[1][i])*glb_cfg->scale_acc[1][i];
	sa_sensor->acc[0]=(sa_sensor->acc_raw[0][1]-glb_cfg->bias_acc[0][1])*glb_cfg->scale_acc[0][1]
										-(sa_sensor->acc_raw[1][1]-glb_cfg->bias_acc[1][1])*glb_cfg->scale_acc[1][1];
	sa_sensor->acc[1]=(sa_sensor->acc_raw[0][0]-glb_cfg->bias_acc[0][0])*glb_cfg->scale_acc[0][0]
										-(sa_sensor->acc_raw[1][0]-glb_cfg->bias_acc[1][0])*glb_cfg->scale_acc[1][0];
	sa_sensor->acc[2]=-(sa_sensor->acc_raw[0][2]-glb_cfg->bias_acc[0][2])*glb_cfg->scale_acc[0][2]
										-(sa_sensor->acc_raw[1][2]-glb_cfg->bias_acc[1][2])*glb_cfg->scale_acc[1][2];

	//AHRS information update /////////////////////////////////////////////////////////////////
	AHRS_test(sa_sensor,glb_state);	
	AHRS_AHRSupdate(sa_sensor,glb_state);
	AHRS_updateYPR(glb_state);

}

void sq_sa_major_control_generate(
	struct str_glb_state* glb_state,
	struct str_glb_identity* glb_identity,
	struct str_glb_toc* glb_toc,
	struct str_glb_input* glb_input,
	struct str_glb_output* glb_output,
	struct str_glb_cfg* glb_cfg)
{
	uint8_t i;
	switch (glb_identity->operating_mode)
	{
		case 1://attitude ///////////////////////////////////////////////////////////////////////
			glb_input->r_euler[1]=glb_input->r[1];
			glb_input->r_euler[2]=glb_input->r[0];
			glb_input->r_omega[0]=glb_input->dr[0];
			glb_input->r_omega[1]=glb_input->dr[1];
			glb_input->r_omega[2]=glb_input->r[3];
			conalg_pid_att(glb_input->r_euler,glb_input->r_omega,glb_state->euler,glb_state->omega,glb_cfg,0.0025f,glb_output->u_core);
			conalg_pid_mix(glb_cfg,glb_input,glb_output);
			break;
		default:
			break;
	}
}

void sq_sa_major_control_execuate(
	struct str_glb_input* sinput,
	struct str_glb_output* soutput,
	struct str_glb_cfg* scfg)
{
	static volatile uint16_t* OUTPUT_CHANNEL_CCR[4]={&TIM3->CCR1,&TIM3->CCR2,&TIM3->CCR3,&TIM3->CCR4};
	uint16_t OUTPUT_CHANNEL_SIG[4];
	uint8_t i;
	//motion control //////////////////////////////////////////////////////////////////////////
	OUTPUT_CHANNEL_SIG[0]=(u16)((18240+scfg->sv_dir[0]*(scfg->sv_midtrim[0]+soutput->u[0]))/scfg->sv_type[0]);
	OUTPUT_CHANNEL_SIG[1]=(u16)((18240+scfg->sv_dir[1]*(scfg->sv_midtrim[1]+soutput->u[1]))/scfg->sv_type[1]);
	OUTPUT_CHANNEL_SIG[2]=(u16)((18240+scfg->sv_dir[2]*(scfg->sv_midtrim[2]+soutput->u[2]))/scfg->sv_type[2]);
	OUTPUT_CHANNEL_SIG[3]=(u16)((18240+scfg->sv_dir[3]*(scfg->sv_midtrim[3]+soutput->u[3]))/scfg->sv_type[3]);
	
	for(i=0;i<4;i++)
	{
		if(scfg->output_sig_id[i]<4)*OUTPUT_CHANNEL_CCR[i]=OUTPUT_CHANNEL_SIG[scfg->output_sig_id[i]];
		else *OUTPUT_CHANNEL_CCR[i]=0;
	}
}
