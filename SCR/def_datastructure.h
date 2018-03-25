#ifndef __DEF_DATASTRUCTURE_H
#define __DEF_DATASTRUCTURE_H

#include "stm32f10x.h"
#include "def_globalmacro.h"

union char2float
{
	uint8_t in_char[4];
	float in_float;
};

union char2short_4x
{
	uint8_t in_char[8];
	int16_t in_short[4];
};

union char2uint16
{
	uint8_t in_char[2];
	uint16_t in_uint16;
};

struct str_glb_input{
	float r[20];
	float dr[2];
	float r_omega[3];
	float r_nav[4];
	float r_nav_temp[4];
	float r_euler[3];
	uint8_t cmd_nav[8];
	//float r_alg[10];
	//uint8_t r_dig[10];
	int16_t rx_hd[8];
	int8_t rx_ld[16];
	uint8_t rx_dig[8];
	uint8_t rx_sw_mode[4];
	uint8_t movement;
};

struct str_glb_output{
	float u_core[6];//ox,oy,oz,fx,fy,fz
	float u[4];
};

struct str_glb_toc{
	uint8_t rx;
};

struct str_glb_identity{
	uint8_t operating_mode;
	uint8_t flag_rx_online;
	uint8_t flag_rx_ready;
	uint8_t flag_ms5611update;
	uint8_t flag_ahrs_ready;
	uint8_t flag_cali;
	uint8_t flag_caligyro;
	uint8_t flag_cfg_init;
	uint8_t flag_flash_execute;
};

struct str_sa_sensor{
	int16_t omega_raw[2][3];
	int16_t acc_raw[2][3];
	float acc[3];
	float omega[3];
	float mag[3];
	uint32_t ms5611_d1;
	uint32_t ms5611_d2;
	int32_t ms5611_temp;
	int32_t ms5611_press;
	float IMU_beta;
	float ahrs_dt;
};

struct str_glb_cali{
	float acc_raw[2][6][3];
};

struct str_glb_state{
	float q[4];
	float euler[3];
	float omega[3];
	float q2[4];
	float euler2[3];
	float q3[4];
	float euler3[3];
	uint8_t flag;
};

struct str_glb_cfg{
uint8_t sv_type[4];							//servo PWM signal width type (1,2)//////////////////////////
int8_t sv_dir[4];								//servo direction (1,-1)/////////////////////////////////////
int16_t sv_midtrim[4];					//servo midpoint trim (-3000~+3000)//////////////////////////
uint16_t sv_install;						//servo install type (0~0xFFFF)//////////////////////////////
uint16_t rp1;
float chn_KTP;									//total pitch gain (0~100)///////////////////////////////////
float chn_swash_limit;					//swash plate limit (0~9000)/////////////////////////////////
float chn_tail_limit_upper;			//tail upper limit (0~9000///////////////////////////////////
float chn_tail_limit_lower;			//tail lower limit (0~-9000)/////////////////////////////////

float chn_P_inner[3];						//inner loop P in yaw,pitch,roll (0~200)/////////////////////
float chn_I_inner[3];						//inner loop I (0~200)///////////////////////////////////////
float chn_P_outer[3];						//outer loop P (0~10)////////////////////////////////////////
float chn_I_outer[3];						//outer loop I (0~10)////////////////////////////////////////

float bias_omega[2][3];					//gyro calibration data /////////////////////////////////////
float scale_omega[2][3];
float bias_acc[2][3];							//																														IMU
float scale_acc[2][3];
uint8_t output_sig_id[4];				//output signal channel id ////////////////////////////////// CORE
/////////////////////////////////////////////////////////////////////////////////////////////////////////


};

union uni_glb_cfg{
uint8_t inbyte[CFG_LENGTH_INBYTE];
uint32_t inword[CFG_LENGTH_INWORD];
struct str_glb_cfg str;
};
#endif
