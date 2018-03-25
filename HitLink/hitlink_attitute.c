#include "protocol.h"
#include "string.h"
#include "hitlink_attitute.h"
#include "hitlink.h"

hitlink_attitute_t hitlink_attitute_msg;

void hitlink_attitute_pack(uint32_t systime_ms,\
							float roll,\
							float pitch,\
							float yaw,\
							float roll_speed,\
							float pitch_speed,\
							float yaw_speed,\
							hitlink_msg *hitlinkmsg)
{
	put_uint32_t_buf(hitlinkmsg->payload,systime_ms);
	put_float_buf(hitlinkmsg->payload,roll);
	put_float_buf(hitlinkmsg->payload,pitch);
	put_float_buf(hitlinkmsg->payload,yaw);
	put_float_buf(hitlinkmsg->payload,roll_speed);
	put_float_buf(hitlinkmsg->payload,pitch_speed);
	put_float_buf(hitlinkmsg->payload,yaw_speed);
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
