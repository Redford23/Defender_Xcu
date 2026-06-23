/*
 * File: XCU_UDSonly.c
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

#include "XCU_UDSonly.h"
#include "rtwtypes.h"
#include "XCU_UDSonly_private.h"
//#include "XCU_UDSonly_capi.h"

/* Named constants for Chart: '<S3>/DiagnosticCANProcess' */
#define CALL_EVENT                     (-1)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_bmsUpdateMode               ((uint8_T)1U)
#define IN_cCSProgrammingSession       ((uint8_T)2U)
#define IN_calculateKey                ((uint8_T)3U)
#define IN_grantSecureAccess           ((uint8_T)4U)
#define IN_idle                        ((uint8_T)5U)
#define IN_jumpToBootloader            ((uint8_T)6U)
#define IN_negativeResponse            ((uint8_T)7U)
#define IN_negativeResponse1           ((uint8_T)8U)
#define IN_programmingSession          ((uint8_T)9U)
#define IN_sendSeed                    ((uint8_T)10U)
#define IN_startDiagnosticSession      ((uint8_T)11U)
#define IN_startExtendedSession        ((uint8_T)12U)
#define IN_step1                       ((uint8_T)1U)
#define IN_step2                       ((uint8_T)2U)
#define IN_step3                       ((uint8_T)3U)
#define IN_step4                       ((uint8_T)4U)
#define IN_testerPresent               ((uint8_T)13U)

/* Block signals (default storage) */
B rtB;

/* Block states (default storage) */
DW rtDW;

/* Real-time model */
//static RT_MODEL rtM_;
//RT_MODEL *const rtM = &rtM_;

/* Forward declaration for local functions */
static void calculateKey(void);

/* Function for Chart: '<S3>/DiagnosticCANProcess' */
static void calculateKey(void)
{
  int32_T tmp;
  uint32_T q0;
  uint32_T qY;
  boolean_T b_out;
  if (rtDW.receivedKey == 1677683898U) {
    rtDW.bitsForTID0.is_keyChecker = IN_NO_ACTIVE_CHILD;
    rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_grantSecureAccess;
    rtB.sendPositiveResponse = 1.0;
    rtB.sendNegativeResponse = 0.0;
    rtB.secureAccess = 1.0;
    tmp = (int32_T)(rtB.udsDataRx.sID + 64U);
    if ((uint32_T)tmp > 255U) {
      tmp = 255;
    }

    rtB.txByte[0] = (uint8_T)tmp;
    rtB.txByte[1] = rtB.udsDataRx.uDSData[0];
    rtB.responseBytes = 2.0;
  } else {
    b_out = ((rtDW.sfEvent == CALL_EVENT) && (rtDW.temporalCounter_i1 >= 100) &&
             (rtDW.receivedKey != 1677683898U));
    if (b_out) {
      rtDW.bitsForTID0.is_keyChecker = IN_NO_ACTIVE_CHILD;
      rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_negativeResponse;
      rtB.sendNegativeResponse = 1.0;
      rtB.txByte[0] = rtB.udsDataRx.sID;
      rtB.txByte[1] = 53U;
      rtB.responseBytes = 2.0;
    } else if (rtP.Constant_Value == 0.0) {
      rtDW.bitsForTID0.is_keyChecker = IN_NO_ACTIVE_CHILD;
      rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_idle;
      rtB.testerPresent = 0.0;
      rtB.sendPositiveResponse = 0.0;
      rtB.sendNegativeResponse = 0.0;
      rtB.inhibitDrive = 0.0;
      rtB.inhibitCharge = 0.0;
      rtB.pauseCanTx2 = 0.0;
    } else {
      switch (rtDW.bitsForTID0.is_keyChecker) {
       case IN_step1:
        rtDW.bitsForTID0.is_keyChecker = IN_step2;
        q0 = rtDW.receivedKey;
        qY = ((uint32_T)rtB.udsDataRx.uDSData[2] << 8) + /*MW:OvSatOk*/ q0;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        rtDW.receivedKey = qY;
        break;

       case IN_step2:
        rtDW.bitsForTID0.is_keyChecker = IN_step3;
        q0 = rtDW.receivedKey;
        qY = ((uint32_T)rtB.udsDataRx.uDSData[3] << 16) + /*MW:OvSatOk*/ q0;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        rtDW.receivedKey = qY;
        break;

       case IN_step3:
        rtDW.bitsForTID0.is_keyChecker = IN_step4;
        q0 = rtDW.receivedKey;
        qY = ((uint32_T)rtB.udsDataRx.uDSData[4] << 24) + /*MW:OvSatOk*/ q0;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        rtDW.receivedKey = qY;
        break;

       default:
        /* case IN_step4: */
        break;
      }
    }
  }
}

/* Model step function */
void XCU_UDSonly_step(void)
{
  int32_T tmp;
  boolean_T f_out;

  /* CCaller: '<S4>/CAN input' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant1'
   *  Constant: '<S4>/Constant2'
   *  Constant: '<S4>/Constant3'
   */
  rtB.CANinput = dcan2MessageboxRead(rtP.CAN2RxMessagebox1_MessageBoxNum,
    rtP.CAN2RxMessagebox1_canID, rtP.CAN2RxMessagebox1_rxMask,
    rtP.CAN2RxMessagebox1_dlc);

  /* CCaller: '<S1>/decodeUDS' */
  rtB.udsDataRx = udsDecode(&rtB.CANinput.Data[0]);

  /* Chart: '<S3>/DiagnosticCANProcess' incorporates:
   *  Constant: '<S3>/Constant'
   */
  rtDW.sfEvent = CALL_EVENT;
  if (rtDW.temporalCounter_i1 < 1023U) {
    rtDW.temporalCounter_i1++;
  }

  if (rtDW.bitsForTID0.is_active_c2_EVP_XCU_lib == 0U) {
    rtDW.bitsForTID0.is_active_c2_EVP_XCU_lib = 1U;
    rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_idle;
    rtB.testerPresent = 0.0;
    rtB.sendPositiveResponse = 0.0;
    rtB.sendNegativeResponse = 0.0;
    rtB.inhibitDrive = 0.0;
    rtB.inhibitCharge = 0.0;
    rtB.pauseCanTx2 = 0.0;
  } else {
    switch (rtDW.bitsForTID0.is_c2_EVP_XCU_lib) {
     case IN_bmsUpdateMode:
     case IN_jumpToBootloader:
      break;

     case IN_cCSProgrammingSession:
      rtB.sendPositiveResponse = 0.0;
      rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_bmsUpdateMode;

      /* Outputs for Function Call SubSystem: '<S3>/BMSupdateMode' */
      /* CCaller: '<S7>/C Caller' incorporates:
       *  Constant: '<S7>/Constant'
       */
      bmsUpdateMode(rtP.Constant_Value_c);

      /* End of Outputs for SubSystem: '<S3>/BMSupdateMode' */
      break;

     case IN_calculateKey:
      calculateKey();
      break;

     case IN_grantSecureAccess:
      rtB.secureAccess = 1.0;
      if (rtB.udsDataRx.sID == 16) {
        rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_startDiagnosticSession;
        rtDW.temporalCounter_i1 = 0U;
        rtB.sendPositiveResponse = 0.0;
        rtB.sendNegativeResponse = 0.0;
        rtDW.diagSessionType = rtB.udsDataRx.uDSData[0];
      } else if (rtP.Constant_Value == 0.0) {
        rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_idle;
        rtB.testerPresent = 0.0;
        rtB.sendPositiveResponse = 0.0;
        rtB.sendNegativeResponse = 0.0;
        rtB.inhibitDrive = 0.0;
        rtB.inhibitCharge = 0.0;
        rtB.pauseCanTx2 = 0.0;
      } else {
        rtB.sendPositiveResponse = 0.0;
      }
      break;

     case IN_idle:
      rtB.testerPresent = 0.0;
      rtB.pauseCanTx2 = 0.0;
      f_out = ((rtB.udsDataRx.sID == 62) && (rtP.Constant_Value == 1.0));
      if (f_out) {
        rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_testerPresent;
        rtB.sendPositiveResponse = 1.0;
        rtB.testerPresent = 1.0;
        tmp = (int32_T)(rtB.udsDataRx.sID + 64U);
        if ((uint32_T)tmp > 255U) {
          tmp = 255;
        }

        rtB.txByte[0] = (uint8_T)tmp;
        rtB.txByte[1] = 0U;
        rtB.responseBytes = 2.0;
      } else {
        rtB.sendPositiveResponse = 0.0;
      }
      break;

     case IN_negativeResponse:
      rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_idle;
      rtB.testerPresent = 0.0;
      rtB.sendPositiveResponse = 0.0;
      rtB.sendNegativeResponse = 0.0;
      rtB.inhibitDrive = 0.0;
      rtB.inhibitCharge = 0.0;
      rtB.pauseCanTx2 = 0.0;
      break;

     case IN_negativeResponse1:
      rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_idle;
      rtB.testerPresent = 0.0;
      rtB.sendPositiveResponse = 0.0;
      rtB.sendNegativeResponse = 0.0;
      rtB.inhibitDrive = 0.0;
      rtB.inhibitCharge = 0.0;
      rtB.pauseCanTx2 = 0.0;
      break;

     case IN_programmingSession:
      rtB.pauseCanTx2 = 1.0;
      rtB.sendPositiveResponse = 0.0;
      rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_jumpToBootloader;

      /* Outputs for Function Call SubSystem: '<S3>/jumpToBootloader' */
      /* CCaller: '<S9>/C Caller' incorporates:
       *  Constant: '<S9>/Constant'
       */
      jumpToBootloader(rtP.Constant_Value_d);

      /* End of Outputs for SubSystem: '<S3>/jumpToBootloader' */
      break;

     case IN_sendSeed:
      f_out = ((rtB.udsDataRx.sID == 39) && (rtB.udsDataRx.uDSData[0] == 4));
      if (f_out) {
        rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_calculateKey;
        rtDW.temporalCounter_i1 = 0U;
        rtB.sendPositiveResponse = 0.0;
        rtDW.bitsForTID0.is_keyChecker = IN_step1;
        rtDW.receivedKey = rtB.udsDataRx.uDSData[1];
      } else if (rtP.Constant_Value == 0.0) {
        rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_idle;
        rtB.testerPresent = 0.0;
        rtB.sendPositiveResponse = 0.0;
        rtB.sendNegativeResponse = 0.0;
        rtB.inhibitDrive = 0.0;
        rtB.inhibitCharge = 0.0;
        rtB.pauseCanTx2 = 0.0;
      } else {
        rtB.sendPositiveResponse = 0.0;
      }
      break;

     case IN_startDiagnosticSession:
      switch (rtDW.diagSessionType) {
       case 2:
        rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_programmingSession;
        rtB.pauseCanTx2 = 1.0;
        rtB.inhibitDrive = 1.0;
        rtB.inhibitCharge = 1.0;
        rtB.sendPositiveResponse = 1.0;
        rtB.sendNegativeResponse = 0.0;
        tmp = (int32_T)(rtB.udsDataRx.sID + 64U);
        if ((uint32_T)tmp > 255U) {
          tmp = 255;
        }

        rtB.txByte[0] = (uint8_T)tmp;
        rtB.txByte[1] = rtDW.diagSessionType;
        rtB.responseBytes = 2.0;
        break;

       case 64:
        rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_cCSProgrammingSession;
        rtB.pauseCanTx1 = 1.0;
        rtB.inhibitDrive = 1.0;
        rtB.inhibitCharge = 1.0;
        rtB.sendPositiveResponse = 1.0;
        rtB.sendNegativeResponse = 0.0;
        tmp = (int32_T)(rtB.udsDataRx.sID + 64U);
        if ((uint32_T)tmp > 255U) {
          tmp = 255;
        }

        rtB.txByte[0] = (uint8_T)tmp;
        rtB.txByte[1] = rtDW.diagSessionType;
        rtB.responseBytes = 2.0;
        break;

       default:
        f_out = ((rtDW.sfEvent == CALL_EVENT) && (rtDW.temporalCounter_i1 >=
                  1000) && (rtDW.diagSessionType != 2) && (rtDW.diagSessionType
                  != 64));
        if (f_out) {
          rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_negativeResponse1;
          rtB.sendNegativeResponse = 1.0;
          rtB.txByte[0] = rtB.udsDataRx.sID;
          rtB.txByte[1] = rtDW.diagSessionType;
          rtB.responseBytes = 2.0;
        } else if (rtP.Constant_Value == 0.0) {
          rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_idle;
          rtB.testerPresent = 0.0;
          rtB.sendPositiveResponse = 0.0;
          rtB.sendNegativeResponse = 0.0;
          rtB.inhibitDrive = 0.0;
          rtB.inhibitCharge = 0.0;
          rtB.pauseCanTx2 = 0.0;
        }
        break;
      }
      break;

     case IN_startExtendedSession:
      if (rtP.Constant_Value == 0.0) {
        rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_idle;
        rtB.testerPresent = 0.0;
        rtB.sendPositiveResponse = 0.0;
        rtB.sendNegativeResponse = 0.0;
        rtB.inhibitDrive = 0.0;
        rtB.inhibitCharge = 0.0;
        rtB.pauseCanTx2 = 0.0;
      } else {
        f_out = ((rtB.udsDataRx.sID == 39) && (rtB.udsDataRx.uDSData[0] == 3));
        if (f_out) {
          rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_sendSeed;
          rtB.sendPositiveResponse = 1.0;
          rtB.sendNegativeResponse = 0.0;
          tmp = (int32_T)(rtB.udsDataRx.sID + 64U);
          if ((uint32_T)tmp > 255U) {
            tmp = 255;
          }

          rtB.txByte[0] = (uint8_T)tmp;
          rtB.txByte[1] = rtB.udsDataRx.uDSData[0];
          rtB.txByte[2] = 1U;
          rtB.txByte[3] = 2U;
          rtB.txByte[4] = 3U;
          rtB.txByte[5] = 4U;
          rtB.responseBytes = 6.0;
        } else {
          rtB.sendPositiveResponse = 0.0;
        }
      }
      break;

     default:
      /* case IN_testerPresent: */
      rtB.testerPresent = 1.0;
      f_out = ((rtB.udsDataRx.sID == 16) && (rtB.udsDataRx.uDSData[0] == 3));
      if (f_out) {
        rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_startExtendedSession;
        rtB.sendPositiveResponse = 1.0;
        rtB.sendNegativeResponse = 0.0;
        rtDW.diagSessionType = rtB.udsDataRx.uDSData[0];
        tmp = (int32_T)(rtB.udsDataRx.sID + 64U);
        if ((uint32_T)tmp > 255U) {
          tmp = 255;
        }

        rtB.txByte[0] = (uint8_T)tmp;
        rtB.txByte[1] = rtDW.diagSessionType;
        rtB.responseBytes = 2.0;
      } else if (rtP.Constant_Value == 0.0) {
        rtDW.bitsForTID0.is_c2_EVP_XCU_lib = IN_idle;
        rtB.testerPresent = 0.0;
        rtB.sendPositiveResponse = 0.0;
        rtB.sendNegativeResponse = 0.0;
        rtB.inhibitDrive = 0.0;
        rtB.inhibitCharge = 0.0;
        rtB.pauseCanTx2 = 0.0;
      } else {
        rtB.sendPositiveResponse = 0.0;
      }
      break;
    }
  }

  /* End of Chart: '<S3>/DiagnosticCANProcess' */

  /* DataTypeConversion: '<S3>/Data Type Conversion' */
  rtB.DataTypeConversion = (uint32_T)rtB.responseBytes;

  /* DataTypeConversion: '<S3>/Data Type Conversion1' */
  rtB.DataTypeConversion1 = (uint8_T)rtB.sendNegativeResponse;

  /* DataTypeConversion: '<S3>/Data Type Conversion2' */
  rtB.DataTypeConversion2 = (uint8_T)rtB.sendPositiveResponse;

  /* CCaller: '<S6>/encodeUDS' incorporates:
   *  Constant: '<S6>/CAN_ID'
   *  Constant: '<S6>/Constant'
   */
  rtB.encodeUDS = udsEncode(rtB.DataTypeConversion, rtP.Subsystem_CAN_ID,
    rtB.DataTypeConversion1, rtB.DataTypeConversion2, rtB.udsDataRx.pCI,
    &rtB.txByte[0], rtP.Constant_Value_k);

  /* CCaller: '<S5>/CAN2 Tx' incorporates:
   *  Constant: '<S5>/Constant'
   *  Constant: '<S5>/Constant1'
   */
  dcan2Messagebox1Transmit(rtB.encodeUDS.canMsg, rtB.encodeUDS.sendUDS,
    rtP.CAN2TxBuffer1_intervalmS, rtP.CAN2TxBuffer1_buffernumber);
}

/* Model initialize function */
void XCU_UDSonly_initialize(void)
{
  /* Registration code */

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
//  XCU_UDSonly_InitializeDataMapInfo();

  /* SystemInitialize for Chart: '<S3>/DiagnosticCANProcess' */
  rtDW.sfEvent = CALL_EVENT;
}

/* Model terminate function */
void XCU_UDSonly_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
