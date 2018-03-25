#ifndef __HITLINK_HEARTBEAT_H
#define __HITLINK_HEARTBEAT_H

/* Includes ------------------------------------------------------------------*/
#include "protocol.h"
#include "stdio.h"
#include <stdint.h>

/* Private define ------------------------------------------------------------*/
#ifndef HITLINK_HEARTBEAT_MSG_ID
#define HITLINK_HEARTBEAT_MSG_ID	0
#endif

/* Typedefine line of the basic link----------------------------------------- */
typedef enum __hitlink_typeenum{Quadrotor,GroundControlSystem,Other_type}HITLINK_TYPEENUM;
typedef enum __hitlink_connect_flagenum{AVALIABLE,UNAVALIABLE}HITLINK_FLAGENUM;
typedef enum __hitlink_stateenum{Lock,Auto,Stable,Other_state}HITLINK_STATEENUM;

typedef struct __hitlink_heartbeat_t{
	uint32_t time_stamp;
	HITLINK_TYPEENUM type;
	HITLINK_FLAGENUM connect_flag;
	HITLINK_STATEENUM system_state;
}hitlink_heartbeat_t;
/* Private function prototypes -----------------------------------------------*/
//void hitlink_heartbeat_pack(hitlink_heartbeat_t *hitlink_heartbeat,\
//							hitlink_msg *hitlinkmsg);

void hitlink_heartbeat_pack(hitlink_heartbeat_t *hitlink_heartbeat,\
							hitlink_msg *hitlinkmsg)
{
	put_uint32_t_buf(hitlinkmsg->payload, hitlink_heartbeat->time_stamp);
	put_int_buf(hitlinkmsg->payload, hitlink_heartbeat->type);
	put_int_buf(hitlinkmsg->payload, hitlink_heartbeat->connect_flag);
	put_int_buf(hitlinkmsg->payload, hitlink_heartbeat->system_state);
}
#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
