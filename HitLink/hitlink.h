#ifndef __HITLINK_H
#define __HITLINK_H

#include <stdint.h>
#include "string.h"




/* Private define ------------------------------------------------------------*/
#ifndef HITLINK_STR
#define HITLINK_STR	0xFE
#endif

#ifndef HITLINK_MAX_LEN
#define HITLINK_MAX_LEN 255
#endif

#define HITLINK_MAX_SEQ 255

/* Typedefine line of the basic link----------------------------------------- */
typedef struct __hitlink_msg{
	uint8_t start;
	uint8_t sequence;
	uint8_t payload_len;
	uint8_t message;
	unsigned char payload[HITLINK_MAX_LEN];
	uint8_t CRC_h;
	uint8_t CRC_l;
	}hitlink_msg;

/* Private function prototypes -----------------------------------------------*/

void hitlink_calculatelen(hitlink_msg *hitlinkmsg);
void hitlink_init(hitlink_msg *hitlinkmsg);
void hit_link_msg2buffer(hitlink_msg *hitlinkmsg, uint8_t *pbuffer);
	
/* Includes ------------------------------------------------------------------*/
#include "protocol.h"
#include "hitlink_heartbeat.h"
#include "hitlink_attitute.h"
#include "checksum.h"
	
hitlink_msg hitlink;
char hitlink_buffer[(HITLINK_MAX_LEN+6)];


//void hitlink_calcuatelen(hitlink_msg *hitlinkmsg);
//void hitlink_init(hitlink_msg *hitlinkmsg);

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
	hitlinkmsg->payload_len=strlen((char *)hitlinkmsg->payload);
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
	//hitlink_calculatelen(hitlinkmsg);
	memset(hitlinkmsg->payload,0,HITLINK_MAX_LEN);
}

/**
 * @brief Change structure into char(uint8_t type) buffer message/
 *	add crc checksum
 * 
 * @param hitlink msssage structure.
 * @param buffer pin
 * @return None
 **/
void hit_link_msg2buffer(hitlink_msg *hitlinkmsg,uint8_t *pbuffer)
{
	int p=0;
	uint16_t crcAccum;
	*pbuffer = hitlinkmsg->start;
	*(pbuffer+1) = (uint8_t)hitlinkmsg->sequence;
	*(pbuffer+2) = (uint8_t)hitlinkmsg->payload_len;
	*(pbuffer+3) = (uint8_t)hitlinkmsg->message;
//	for(p=0;p < (hitlinkmsg->payload_len);p++)
//	{
//		*(pbuffer+4+p) = hitlinkmsg->payload[p];
//	}
	memcpy(pbuffer+4,hitlinkmsg->payload,hitlinkmsg->payload_len);
	crcAccum = crc_calculate(pbuffer,hitlinkmsg->payload_len+4);
	*(pbuffer+4+(hitlinkmsg->payload_len))=(uint8_t)(crcAccum>>8);
	*(pbuffer+5+(hitlinkmsg->payload_len))=(uint8_t)(crcAccum&0x00FF);
}

#endif
	
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
	