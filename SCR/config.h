#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32f10x.h"
#include "def_datastructure.h"
#include "def_globalmacro.h"
#include "Security.h"

void cfg_init(void);
void cfg_readfromflash(union uni_glb_cfg* lite_cfg);
void cfg_writetoflash(union uni_glb_cfg* lite_cfg);

#endif
