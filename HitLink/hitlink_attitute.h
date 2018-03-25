#ifndef __HITLINK_ATTITUTE_H
#define __HITLINK_ATTITUTE_H

/* Includes ------------------------------------------------------------------*/
#include "hitlink.h"
#include "protocol.h"
#include "stdio.h"
#include <stdint.h>


/* Private define ------------------------------------------------------------*/
#ifndef HITLINK_ATTITUTE_MSG_ID
#define HITLINK_ATTITUTE_MSG_ID	1
#endif

/* Typedefine line of the basic link----------------------------------------- */
typedef struct __hitlink_attitute_t{
	uint32_t time_stamp;
	float roll;
	float pitch;
	float yaw;
	float roll_speed;
	float pitch_speed;
	float yaw_speed;
}hitlink_attitute_t;



/* Private function prototypes -----------------------------------------------*/
//void hitlink_attitute_pack(uint32_t systime_ms,\
//							float roll,\
//							float pitch,\
//							float yaw,\
//							float roll_speed,\
//							float pitch_speed,\
//							float yaw_speed,\
//							hitlink_msg *hitlinkmsg);
							

hitlink_attitute_t hitlink_attitute_msg;

void hitlink_attitute_pack(hitlink_attitute_t *hitlink_attitute_msg,\
							hitlink_msg *hitlinkmsg)
{
	put_uint32_t_buf(hitlinkmsg->payload,hitlink_attitute_msg->time_stamp);
	put_float_buf(hitlinkmsg->payload,hitlink_attitute_msg->roll);
	put_float_buf(hitlinkmsg->payload,hitlink_attitute_msg->pitch);
	put_float_buf(hitlinkmsg->payload,hitlink_attitute_msg->yaw);
	put_float_buf(hitlinkmsg->payload,hitlink_attitute_msg->roll_speed);
	put_float_buf(hitlinkmsg->payload,hitlink_attitute_msg->pitch_speed);
	put_float_buf(hitlinkmsg->payload,hitlink_attitute_msg->yaw_speed);
}
#endif
							
							