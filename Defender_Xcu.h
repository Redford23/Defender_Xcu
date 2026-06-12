/*
 * File: Defender_Xcu.h
 *
 * template generated for test 'Defender_Xcu'.
 *
 * Model version                  : 8.50
 * Date : Sun Apr 19 14:37:40 2026
 *
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef DEFENDER_XCU_h_
#define DEFENDER_XCU_h_
#ifndef DEFENDER_XCU_COMMON_INCLUDES_
#define DEFENDER_XCU_COMMON_INCLUDES_
#include <math.h>
#include "can_message.h"
#endif                                 
/* DEFENDER_XCU_COMMON_INCLUDES_ */

#include "can_input_simulink.h"
#include "evp_UDS.h"
#include "evp_fee.h"
#include <string.h> //may not be required


/* user code (top of header file) */
#include "can_input_simulink.h"
#include "evp_UDS.h"
#include "evp_fee.h"


/* Block signals (default storage) */
typedef struct {
  ANALOG_INPUT_BUS AnalogInputs;       /* '<Root>/Analog Inputs' */
  UDSDATARX udsDataRx;                 /* '<S1>/decodeUDS' */
  UDSDATATX encodeUDS;                 /* '<S3>/encodeUDS' */
  CAN_MESSAGE_BUS CANinput1;            /* '<S41>/CAN input' */
  //CAN_MESSAGE_BUS clearData;           /* '<S18>/clearData ' */
  //CAN_MESSAGE_BUS Switch;              /* '<S18>/Switch' */
  //CAN_MESSAGE_BUS CANinput_p;          /* '<S45>/CAN input' */
  //CAN_MESSAGE_BUS clearData_i;         /* '<S19>/clearData ' */
  //CAN_MESSAGE_BUS Switch_p;            /* '<S19>/Switch' */
 // CAN_MESSAGE_BUS CANPack;             /* '<S2>/CAN Pack' */
 
  CAN_MESSAGE_BUS CAN2input6;          /* '<S1>/CAN2 input6' required for UDS*/
  
  DIGITAL_OUTPUT_BUS BusConversion_InsertedFor_Digit;
  DIGITAL_INPUT_BUS DigitalInputs;     /* '<Root>/Digital Inputs' */

  real_T responseBytes;                /* '<S7>/DiagnosticCANProcess' */
  real_T secureAccess;                 /* '<S7>/DiagnosticCANProcess' */
  real_T sendNegativeResponse;         /* '<S7>/DiagnosticCANProcess' */
  real_T sendPositiveResponse;         /* '<S7>/DiagnosticCANProcess' */
  real_T testerPresent;                /* '<S7>/DiagnosticCANProcess' */
  real_T inhibitCharge;                /* '<S7>/DiagnosticCANProcess' */
  real_T inhibitDrive;                 /* '<S7>/DiagnosticCANProcess' */
  real_T pauseCanTx2;                  /* '<S7>/DiagnosticCANProcess' */
  real_T pauseCanTx1;                  /* '<S7>/DiagnosticCANProcess' */
   
  uint32_T evpFeeReadConfig_o2[32];    /* '<S59>/evpFeeReadConfig' */

  RESETCAUSEFORSIMULINK readresetcause1;/* '<S59>/read reset cause1' */
  FEE_WRITE_STATUS evpFeeReadConfig_o1;/* '<S59>/evpFeeReadConfig' */
  FEE_WRITE_STATUS evpFeeWriteConfig;  /* '<S62>/evpFeeWriteConfig' */
  
  uint8_T canTxEn;                     /* '<S5>/Chart' */
  
} B;

/* Block states (default storage) for system '<Root>' @todo may net be used */
typedef struct {
  
  int32_T sfEvent;                     /* '<S7>/DiagnosticCANProcess' */
  uint32_T receivedKey;                /* '<S7>/DiagnosticCANProcess' */
 
  struct {
    uint_T is_c2_EVOYAGER_VCU_2R1HW:4; /* '<S7>/DiagnosticCANProcess' */
    uint_T is_keyChecker:3;            /* '<S7>/DiagnosticCANProcess' */
    
    uint_T is_active_c2_EVOYAGER_VCU_2R1HW:1;/* '<S7>/DiagnosticCANProcess' */
   
  } bitsForTID0;

  uint16_T temporalCounter_i1;         /* '<S7>/DiagnosticCANProcess' */

  uint8_T diagSessionType;             /* '<S7>/DiagnosticCANProcess' */
 
} DW;


/* Model entry point functions */
extern void EVOYAGER_VCU_2R1HW_initialize(void);
extern void EVOYAGER_VCU_2R1HW_step(void);
extern void EVOYAGER_VCU_2R1HW_terminate(void);




#endif                                 /* RTW_HEADER_EVOYAGER_VCU_2R1HW_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
