#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include <math.h>
#include <stdio.h>
#include "System_Init.h"
#include "delay.h"

#include "Security.h"
#include "config.h"
#include "Communicate.h"
#include "def_datastructure.h"

#include "driver_ICM20689.h"
#include "driver_MS5611.h"

#include "sequence_sa_major.h"
#include "sequence_sa_minor.h"
/** º¯ÊýÉêÃ÷ ***********************************************/
int main(void);
void Datainput(void);

#endif
