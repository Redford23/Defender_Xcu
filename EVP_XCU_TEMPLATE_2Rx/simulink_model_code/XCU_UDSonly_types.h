/*
 * File: XCU_UDSonly_types.h
 *
 * Code generated for Simulink model 'XCU_UDSonly'.
 *
 * Model version                  : 8.84
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Wed Jun 17 15:21:00 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_XCU_UDSonly_types_h_
#define RTW_HEADER_XCU_UDSonly_types_h_
#include "rtwtypes.h"
#include "evp_UDS.h"
#ifndef DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_
#define DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_

typedef struct {
  uint8_T Extended;
  uint8_T Length;
  uint8_T Remote;
  uint8_T Error;
  uint32_T ID;
  real_T Timestamp;
  uint8_T Data[8];
} CAN_MESSAGE_BUS;

#endif

#ifndef SS_UINT64
#define SS_UINT64                      20
#endif

#ifndef SS_INT64
#define SS_INT64                       21
#endif

/* Parameters (default storage) */
typedef struct P_ P;

/* Forward declaration for rtModel */
//typedef struct tag_RTM RT_MODEL;

#endif                                 /* RTW_HEADER_XCU_UDSonly_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
