#include "protocol.h"
#include "stdio.h"
#include "string.h"
#include "hitlink_heartbeat.h"
#include "hitlink.h"

hitlink_heartbeat_t hitlink_heartbeat_msg;

void hitlink_heartbeat_pack(hitlink_heartbeat_t *hitlink_heartbeat,\
							hitlink_msg *hitlinkmsg)
{
	put_uint32_t_buf(hitlinkmsg->payload, hitlink_heartbeat->time_stamp);
	put_int_buf(hitlinkmsg->payload, hitlink_heartbeat->type);
	put_int_buf(hitlinkmsg->payload, hitlink_heartbeat->connect_flag);
	put_int_buf(hitlinkmsg->payload, hitlink_heartbeat->system_state);
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
