#include "stm32f10x.h"
#include "hitlink.h"
#include "checksum.h"
#include "string.h"
#include <stdint.h>

hitlink_msg hitlink;
char hitlink_buffer[(HITLINK_MAX_LEN+6)];


void hitlink_calcuatelen(hitlink_msg *hitlinkmsg);
void hitlink_init(hitlink_msg *hitlinkmsg);

/**
 * @brief Calculate payload string len.
 *	we use strlen in string.h
 * 
 * @param hitlink msssage structure.
 * @return None
 **/
void hitlink_calculatelen(hitlink_msg *hitlinkmsg)
{
//	int flag=0;
//	int len=0;
//	for (flag=HITLINK_MAX_LEN-1;flag>=0;flag--)
//	{
//		if(hitlinkmsg->payload[flag]!=0x00)
//			break;
//	}
//	len=flag+1;
//	hitlinkmsg->payload_len=len;
	hitlinkmsg->payload_len=strlen(hitlinkmsg->payload);
}

/**
 * @brief Init mssage structure.
 *	
 * 
 * @param hitlink msssage structure.
 * @return None
 **/
void hitlink_init(hitlink_msg *hitlinkmsg)
{
	hitlinkmsg->start = HITLINK_STR;
	hitlinkmsg->CRC_h=0;
	hitlinkmsg->CRC_l=0;
	hitlink_calculatelen(hitlinkmsg);
}

/**
 * @brief Change structure into char(uint8_t type) buffer message/
 *	add crc checksum
 * 
 * @param hitlink msssage structure.
 * @param buffer pin
 * @return None
 **/
void hit_link_msg2buffer(hitlink_msg *hitlinkmsg, char *pbuffer)
{
	int p=0;
	uint16_t crcAccum;
	*pbuffer = hitlinkmsg->start;
	*(pbuffer+1) = (uint8_t)hitlinkmsg->sequence;
	*(pbuffer+2) = (uint8_t)hitlinkmsg->payload_len;
	*(pbuffer+3) = (uint8_t)hitlinkmsg->message;
	for(p=0;p < hitlinkmsg->payload_len;p++)
	{
		*(pbuffer+4+p) = (uint8_t) hitlinkmsg->payload[p];
	}
	crc_accumulate_buffer(&crcAccum,pbuffer,(hitlinkmsg->payload_len+4));
	*(pbuffer+4+hitlinkmsg->payload_len)=(uint8_t)crcAccum>>8;
	*(pbuffer+5+hitlinkmsg->payload_len)=(uint8_t)crcAccum&0x00FF;
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
