#ifndef __sequence_sa_major_H
#define __sequence_sa_major_H

#include "stm32f10x.h"
#include "def_datastructure.h"
#include "def_globalmacro.h"
#include "delay.h"
#include "driver_MS5611.h"
#include "driver_ICM20689.h"
#include "AHRS_Madgwick.h"
#include "pid.h"

void sq_lite_major_state_update(
	struct str_glb_identity* glb_identity,
	struct str_sa_sensor* sa_sensor,
	struct str_glb_state* glb_state,
	struct str_glb_toc* glb_toc,
	struct str_glb_input* glb_input,
	struct str_glb_cfg* glb_cfg);
void sq_sa_major_control_generate(
	struct str_glb_state* lite_state,
	struct str_glb_identity* lite_identity,
	struct str_glb_toc* lite_toc,
	struct str_glb_input* lite_input,
	struct str_glb_output* lite_output,
	struct str_glb_cfg* lite_cfg);
void sq_sa_major_control_execuate(
	struct str_glb_input* lite_input,
	struct str_glb_output* lite_output,
	struct str_glb_cfg* lite_cfg);
void AHRS_test(struct str_sa_sensor* lite_sensor,struct str_glb_state* lite_state);

#endif
