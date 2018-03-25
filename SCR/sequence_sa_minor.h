#ifndef __SEQUENCE_SA_MINOR
#define __SEQUENCE_SA_MINOR

#include "def_datastructure.h"
#include <math.h>
#include "config.h"

void sq_sa_cali_sampling(
	struct str_glb_identity* sidentity,
	struct str_sa_sensor* ssensor,
	struct str_glb_cali* scali);
void sq_sa_cali_update(
	struct str_glb_identity* sidentity,
	struct str_glb_cfg* scfg,
	struct str_glb_cali* scali);
void sq_sa_cali_gyro(
	struct str_glb_identity* sidentity,
	struct str_sa_sensor* ssensor,
	struct str_glb_cfg* scfg);
void sq_sa_cali_acc_quick(
	struct str_glb_identity* sidentity,
	struct str_sa_sensor* ssensor,
	struct str_glb_cali* scali,
	struct str_glb_cfg* scfg);
#endif
