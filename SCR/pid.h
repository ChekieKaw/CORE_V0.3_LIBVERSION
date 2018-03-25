#ifndef __PID_H
#define __PID_H
#include <math.h>
#include "def_datastructure.h"

struct PID
{
float P_inner;
float I_inner;
float D_inner;
float P_outer;
float I_outer;
float D_outer;
};

void conalg_pid_att(float* r_euler,float* r_omega_input,float* euler,float* omega,struct str_glb_cfg* scfg,float dt,float* u_core);
void conalg_pid_mix(struct str_glb_cfg* glb_cfg,struct str_glb_input* glb_input,struct str_glb_output* glb_output);


#endif
