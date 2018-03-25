#ifndef __AHRS_MADGWICK_H
#define __AHRS_MADGWICK_H

#include <math.h>
#include "def_datastructure.h"
#define M_PI  (float)3.1415926535

//Mini IMU AHRS ½âËãµÄAPI
void AHRS_AHRSupdate(struct str_sa_sensor* lite_sensor,struct str_glb_state* lite_state);
void AHRS_AHRSupdate_NoMag(struct str_sa_sensor* lite_sensor,struct str_glb_state* lite_state);
void AHRS_updateYPR(struct str_glb_state * lite_state);


#endif

//------------------End of File----------------------------
