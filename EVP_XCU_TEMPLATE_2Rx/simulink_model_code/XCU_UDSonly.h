/*
 * File: XCU_UDSonly.h
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

#ifndef RTW_HEADER_XCU_UDSonly_h_
#define RTW_HEADER_XCU_UDSonly_h_
#ifndef XCU_UDSonly_COMMON_INCLUDES_
#define XCU_UDSonly_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* XCU_UDSonly_COMMON_INCLUDES_ */

#include "XCU_UDSonly_types.h"
#include "evp_UDS.h"
//#include "rtw_modelmap.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm)         ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)    ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define XCU_UDSonly_M                  (rtM)

/* user code (top of header file) */
#include "can_input_simulink.h"
#include "evp_UDS.h"
#include "evp_fee.h"

/* Block signals (default storage) */
typedef struct {
  UDSDATARX udsDataRx;                 /* '<S1>/decodeUDS' */
  UDSDATATX encodeUDS;                 /* '<S6>/encodeUDS' */
  CAN_MESSAGE_BUS CANinput;            /* '<S4>/CAN input' */
  real_T responseBytes;                /* '<S3>/DiagnosticCANProcess' */
  real_T secureAccess;                 /* '<S3>/DiagnosticCANProcess' */
  real_T sendNegativeResponse;         /* '<S3>/DiagnosticCANProcess' */
  real_T sendPositiveResponse;         /* '<S3>/DiagnosticCANProcess' */
  real_T testerPresent;                /* '<S3>/DiagnosticCANProcess' */
  real_T inhibitCharge;                /* '<S3>/DiagnosticCANProcess' */
  real_T inhibitDrive;                 /* '<S3>/DiagnosticCANProcess' */
  real_T pauseCanTx2;                  /* '<S3>/DiagnosticCANProcess' */
  real_T pauseCanTx1;                  /* '<S3>/DiagnosticCANProcess' */
  uint32_T DataTypeConversion;         /* '<S3>/Data Type Conversion' */
  uint8_T DataTypeConversion1;         /* '<S3>/Data Type Conversion1' */
  uint8_T DataTypeConversion2;         /* '<S3>/Data Type Conversion2' */
  uint8_T txByte[7];                   /* '<S3>/DiagnosticCANProcess' */
} B;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  int32_T sfEvent;                     /* '<S3>/DiagnosticCANProcess' */
  uint32_T receivedKey;                /* '<S3>/DiagnosticCANProcess' */
  struct {
    uint_T is_c2_EVP_XCU_lib:4;        /* '<S3>/DiagnosticCANProcess' */
    uint_T is_keyChecker:3;            /* '<S3>/DiagnosticCANProcess' */
    uint_T is_active_c2_EVP_XCU_lib:1; /* '<S3>/DiagnosticCANProcess' */
  } bitsForTID0;

  uint16_T temporalCounter_i1;         /* '<S3>/DiagnosticCANProcess' */
  uint8_T diagSessionType;             /* '<S3>/DiagnosticCANProcess' */
} DW;

/* Parameters (default storage) */
struct P_ {
  real_T CAN2RxMessagebox1_MessageBoxNum;
                              /* Mask Parameter: CAN2RxMessagebox1_MessageBoxNum
                               * Referenced by: '<S4>/Constant'
                               */
  real_T CAN2TxBuffer1_buffernumber;
                                   /* Mask Parameter: CAN2TxBuffer1_buffernumber
                                    * Referenced by: '<S5>/Constant1'
                                    */
  real_T CAN2RxMessagebox1_canID;     /* Mask Parameter: CAN2RxMessagebox1_canID
                                       * Referenced by: '<S4>/Constant1'
                                       */
  real_T CAN2TxBuffer1_intervalmS;   /* Mask Parameter: CAN2TxBuffer1_intervalmS
                                      * Referenced by: '<S5>/Constant'
                                      */
  uint32_T Subsystem_CAN_ID;           /* Mask Parameter: Subsystem_CAN_ID
                                        * Referenced by: '<S6>/CAN_ID'
                                        */
  uint32_T CAN2RxMessagebox1_rxMask; /* Mask Parameter: CAN2RxMessagebox1_rxMask
                                      * Referenced by: '<S4>/Constant2'
                                      */
  uint8_T CAN2RxMessagebox1_dlc;       /* Mask Parameter: CAN2RxMessagebox1_dlc
                                        * Referenced by: '<S4>/Constant3'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S3>/Constant'
                                        */
  uint32_T Constant_Value_d;           /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S9>/Constant'
                                        */
  uint32_T Constant_Value_c;           /* Computed Parameter: Constant_Value_c
                                        * Referenced by: '<S7>/Constant'
                                        */
  uint8_T Constant_Value_k;            /* Computed Parameter: Constant_Value_k
                                        * Referenced by: '<S6>/Constant'
                                        */
};

///* Real-time Model Data Structure */
//struct tag_RTM {
//  const char_T * volatile errorStatus;
//
//  /*
//   * DataMapInfo:
//   * The following substructure contains information regarding
//   * structures generated in the model's C API.
//   */
//  struct {
//    rtwCAPI_ModelMappingInfo mmi;
//  } DataMapInfo;
//};

/* Block parameters (default storage) */
extern P rtP;

/* Block signals (default storage) */
extern B rtB;

/* Block states (default storage) */
extern DW rtDW;

/* Model entry point functions */
extern void XCU_UDSonly_initialize(void);
extern void XCU_UDSonly_step(void);
extern void XCU_UDSonly_terminate(void);

/* Function to get C API Model Mapping Static Info */
//extern const rtwCAPI_ModelMappingStaticInfo*
//  XCU_UDSonly_GetCAPIStaticMap(void);

/* Real-time Model object */
//extern RT_MODEL *const rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'XCU_UDSonly'
 * '<S1>'   : 'XCU_UDSonly/CAN data acquisition'
 * '<S2>'   : 'XCU_UDSonly/CAN2 output'
 * '<S3>'   : 'XCU_UDSonly/UDS process 1'
 * '<S4>'   : 'XCU_UDSonly/CAN data acquisition/CAN2RxMessagebox1'
 * '<S5>'   : 'XCU_UDSonly/CAN2 output/CAN2 Tx Buffer 1'
 * '<S6>'   : 'XCU_UDSonly/CAN2 output/Subsystem'
 * '<S7>'   : 'XCU_UDSonly/UDS process 1/BMSupdateMode'
 * '<S8>'   : 'XCU_UDSonly/UDS process 1/DiagnosticCANProcess'
 * '<S9>'   : 'XCU_UDSonly/UDS process 1/jumpToBootloader'
 */
#endif                                 /* RTW_HEADER_XCU_UDSonly_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
