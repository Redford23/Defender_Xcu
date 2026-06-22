/*
 * user_model.h
 *
 *  Created on: 17 Jun 2026
 *      Author: mOffice
 */

#ifndef INCLUDE_USER_MODEL_H_
#define INCLUDE_USER_MODEL_H_

/* user model includes */
#include "can_input_simulink.h"
#include "evp_UDS.h"
#include "evp_fee.h"

/* user model constants */

/* user model variables
 * if external is required */

/* Model entry point functions */
extern void user_model_initialize(void);
extern void user_model_step(void);
extern void user_model_terminate(void);




#endif /* INCLUDE_USER_MODEL_H_ */
