/*
 * File: Defender_Xcu.c
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

#include "Defender_Xcu.h"
#include <math.h>

/* Named constants for model */
#define EXAMPLE_CONSTANT 1U


/* Block signals (default storage) */
B rtB;

/* Block states (default storage) */
DW rtDW;



/* Forward declaration for local functions */
static void exampleFunction(void);



/* Function for Chart: '<S7>/DiagnosticCANProcess' */
static void calculateKey(void)
{
  int32_T tmp;
  uint32_T q0;
  uint32_T qY;
  boolean_T b_out;
  if (rtDW.receivedKey == 1677683898U) {
    rtDW.bitsForTID0.is_keyChecker = IN_NO_ACTIVE_CHILD;
    rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_grantSecureAccess;
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
    b_out = ((rtDW.sfEvent == -1) && (rtDW.temporalCounter_i1 >= 100) &&
             (rtDW.receivedKey != 1677683898U));
    if (b_out) {
      rtDW.bitsForTID0.is_keyChecker = IN_NO_ACTIVE_CHILD;
      rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_negativeResponse;
      rtB.sendNegativeResponse = 1.0;
      rtB.txByte[0] = rtB.udsDataRx.sID;
      rtB.txByte[1] = 53U;
      rtB.responseBytes = 2.0;
    } else if (rtP.Constant_Value_k == 0.0) {
      rtDW.bitsForTID0.is_keyChecker = IN_NO_ACTIVE_CHILD;
      rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_idle;
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
void EVOYAGER_VCU_2R1HW_step(void)
{
	/* local variables*/
  real_T maxV;
  int32_T i;
  boolean_T b_out;
  boolean_T guard1;

  /* example CAN input */
  rtB.CANinput = dcan2MessageboxRead(rtP.CAN2RXBlock2_MessageBoxNum,
    rtP.CAN2RXBlock2_canid, rtP.CAN2RxMessagebox_rxMask, rtP.CAN2RXBlock2_dlc);

/*  check timestamp and unpack received bytes */  



  /* CCaller: '<Root>/Digital Inputs' */
  rtB.DigitalInputs = digitalInputRead();

 


  /* UDS update process - @todo seperate files and pre compiles */

  /* CCaller: '<S1>/CAN2 input6' */
  rtB.CAN2input6 = dcan2MessageboxRead(rtP.CAN2input6_messageBox,
    rtP.CAN2input6_canFilterID, rtP.CAN2input6_rxMask, rtP.CAN2input6_dlc);

  /* S-Function (scanunpack): '<S1>/CAN Unpack5' */
  {
    /* S-Function (scanunpack): '<S1>/CAN Unpack5' */
    uint8_T msgReceived = 0;
    if ((8 == rtB.CAN2input6.Length) && (rtB.CAN2input6.ID != INVALID_CAN_ID) )
    {
      if ((2016 == rtB.CAN2input6.ID) && (0U == rtB.CAN2input6.Extended) ) {
        msgReceived = 1;
        (void) memcpy(&rtB.CANUnpack5_o1[0], rtB.CAN2input6.Data,
                      8 * sizeof(uint8_T));

        /* Extract the Timestamp */
        rtB.CANUnpack5_o2 = rtB.CAN2input6.Timestamp;
      }
    }

    /* Status port */
    rtB.CANUnpack5_o3 = msgReceived;
  }

  /* CCaller: '<S1>/decodeUDS' incorporates:
   *  S-Function (scanunpack): '<S1>/CAN Unpack5'
   */
  rtB.udsDataRx = udsDecode(&rtB.CANUnpack5_o1[0]);

  /* Chart: '<S7>/DiagnosticCANProcess' incorporates:
   *  Constant: '<S7>/Constant'
   */
  rtDW.sfEvent = -1;
  if (rtDW.temporalCounter_i1 < 1023U) {
    rtDW.temporalCounter_i1++;
  }

  if (rtDW.bitsForTID0.is_active_c2_EVOYAGER_VCU_2R1HW == 0U) {
    rtDW.bitsForTID0.is_active_c2_EVOYAGER_VCU_2R1HW = 1U;
    rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_idle;
    rtB.testerPresent = 0.0;
    rtB.sendPositiveResponse = 0.0;
    rtB.sendNegativeResponse = 0.0;
    rtB.inhibitDrive = 0.0;
    rtB.inhibitCharge = 0.0;
    rtB.pauseCanTx2 = 0.0;
  } else {
    switch (rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW) {
     case IN_bmsUpdateMode:
     case IN_jumpToBootloader:
      break;

     case IN_cCSProgrammingSession:
      rtB.sendPositiveResponse = 0.0;
      rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_bmsUpdateMode;

      /* Outputs for Function Call SubSystem: '<S7>/BMSupdateMode' */
      /* Sum: '<S87>/Add' incorporates:
       *  Constant: '<S87>/Constant1'
       *  Constant: '<S87>/Constant2'
       */
      rtB.Add = (uint8_T)((uint32_T)rtP.Constant1_Value_n +
                          rtP.Constant2_Value_n);

      /* CCaller: '<S87>/C Caller' incorporates:
       *  Constant: '<S87>/Constant'
       */
      bmsUpdateMode(rtP.Constant_Value_i);

      /* End of Outputs for SubSystem: '<S7>/BMSupdateMode' */
      break;

     case IN_calculateKey:
      calculateKey();
      break;

     case IN_grantSecureAccess:
      rtB.secureAccess = 1.0;
      if (rtB.udsDataRx.sID == 16) {
        rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_startDiagnosticSession;
        rtDW.temporalCounter_i1 = 0U;
        rtB.sendPositiveResponse = 0.0;
        rtB.sendNegativeResponse = 0.0;
        rtDW.diagSessionType = rtB.udsDataRx.uDSData[0];
      } else if (rtP.Constant_Value_k == 0.0) {
        rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_idle;
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
      b_out = ((rtB.udsDataRx.sID == 62) && (rtP.Constant_Value_k == 1.0));
      if (b_out) {
        rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_testerPresent;
        rtB.sendPositiveResponse = 1.0;
        rtB.testerPresent = 1.0;
        i = (int32_T)(rtB.udsDataRx.sID + 64U);
        if ((uint32_T)i > 255U) {
          i = 255;
        }

        rtB.txByte[0] = (uint8_T)i;
        rtB.txByte[1] = 0U;
        rtB.responseBytes = 2.0;
      } else {
        rtB.sendPositiveResponse = 0.0;
      }
      break;

     case IN_negativeResponse:
      rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_idle;
      rtB.testerPresent = 0.0;
      rtB.sendPositiveResponse = 0.0;
      rtB.sendNegativeResponse = 0.0;
      rtB.inhibitDrive = 0.0;
      rtB.inhibitCharge = 0.0;
      rtB.pauseCanTx2 = 0.0;
      break;

     case IN_negativeResponse1:
      rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_idle;
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
      rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_jumpToBootloader;

      /* Outputs for Function Call SubSystem: '<S7>/jumpToBootloader' */
      /* CCaller: '<S89>/C Caller' incorporates:
       *  Constant: '<S89>/Constant'
       */
      jumpToBootloader(rtP.Constant_Value_h);

      /* End of Outputs for SubSystem: '<S7>/jumpToBootloader' */
      break;

     case IN_sendSeed:
      b_out = ((rtB.udsDataRx.sID == 39) && (rtB.udsDataRx.uDSData[0] == 4));
      if (b_out) {
        rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_calculateKey;
        rtDW.temporalCounter_i1 = 0U;
        rtB.sendPositiveResponse = 0.0;
        rtDW.bitsForTID0.is_keyChecker = IN_step1;
        rtDW.receivedKey = rtB.udsDataRx.uDSData[1];
      } else if (rtP.Constant_Value_k == 0.0) {
        rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_idle;
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
        rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_programmingSession;
        rtB.pauseCanTx2 = 1.0;
        rtB.inhibitDrive = 1.0;
        rtB.inhibitCharge = 1.0;
        rtB.sendPositiveResponse = 1.0;
        rtB.sendNegativeResponse = 0.0;
        i = (int32_T)(rtB.udsDataRx.sID + 64U);
        if ((uint32_T)i > 255U) {
          i = 255;
        }

        rtB.txByte[0] = (uint8_T)i;
        rtB.txByte[1] = rtDW.diagSessionType;
        rtB.responseBytes = 2.0;
        break;

       case 64:
        rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_cCSProgrammingSession;
        rtB.pauseCanTx1 = 1.0;
        rtB.inhibitDrive = 1.0;
        rtB.inhibitCharge = 1.0;
        rtB.sendPositiveResponse = 1.0;
        rtB.sendNegativeResponse = 0.0;
        i = (int32_T)(rtB.udsDataRx.sID + 64U);
        if ((uint32_T)i > 255U) {
          i = 255;
        }

        rtB.txByte[0] = (uint8_T)i;
        rtB.txByte[1] = rtDW.diagSessionType;
        rtB.responseBytes = 2.0;
        break;

       default:
        b_out = ((rtDW.sfEvent == -1) && (rtDW.temporalCounter_i1 >= 1000) &&
                 (rtDW.diagSessionType != 2) && (rtDW.diagSessionType != 64));
        if (b_out) {
          rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_negativeResponse1;
          rtB.sendNegativeResponse = 1.0;
          rtB.txByte[0] = rtB.udsDataRx.sID;
          rtB.txByte[1] = rtDW.diagSessionType;
          rtB.responseBytes = 2.0;
        } else if (rtP.Constant_Value_k == 0.0) {
          rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_idle;
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
      if (rtP.Constant_Value_k == 0.0) {
        rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_idle;
        rtB.testerPresent = 0.0;
        rtB.sendPositiveResponse = 0.0;
        rtB.sendNegativeResponse = 0.0;
        rtB.inhibitDrive = 0.0;
        rtB.inhibitCharge = 0.0;
        rtB.pauseCanTx2 = 0.0;
      } else {
        b_out = ((rtB.udsDataRx.sID == 39) && (rtB.udsDataRx.uDSData[0] == 3));
        if (b_out) {
          rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_sendSeed;
          rtB.sendPositiveResponse = 1.0;
          rtB.sendNegativeResponse = 0.0;
          i = (int32_T)(rtB.udsDataRx.sID + 64U);
          if ((uint32_T)i > 255U) {
            i = 255;
          }

          rtB.txByte[0] = (uint8_T)i;
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
      b_out = ((rtB.udsDataRx.sID == 16) && (rtB.udsDataRx.uDSData[0] == 3));
      if (b_out) {
        rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_startExtendedSession;
        rtB.sendPositiveResponse = 1.0;
        rtB.sendNegativeResponse = 0.0;
        rtDW.diagSessionType = rtB.udsDataRx.uDSData[0];
        i = (int32_T)(rtB.udsDataRx.sID + 64U);
        if ((uint32_T)i > 255U) {
          i = 255;
        }

        rtB.txByte[0] = (uint8_T)i;
        rtB.txByte[1] = rtDW.diagSessionType;
        rtB.responseBytes = 2.0;
      } else if (rtP.Constant_Value_k == 0.0) {
        rtDW.bitsForTID0.is_c2_EVOYAGER_VCU_2R1HW = IN_idle;
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


  /* DataTypeConversion: '<S7>/Data Type Conversion' */
  rtB.DataTypeConversion = (uint32_T)rtB.responseBytes;

  /* DataTypeConversion: '<S7>/Data Type Conversion1' */
  rtB.DataTypeConversion1_a = (uint8_T)rtB.sendNegativeResponse;

  /* DataTypeConversion: '<S7>/Data Type Conversion2' */
  rtB.DataTypeConversion2_e = (uint8_T)rtB.sendPositiveResponse;

  /* CCaller: '<S3>/encodeUDS' */
  rtB.encodeUDS = udsEncode(rtB.DataTypeConversion, rtP.encodeUDS_txID,
    rtB.DataTypeConversion1_a, rtB.DataTypeConversion2_e, rtB.udsDataRx.pCI,
    &rtB.txByte[0], rtP.encodeUDS_extended);

  /* CCaller: '<S3>/CAN2 output 3' */
  dcan2Messagebox1Transmit(rtB.encodeUDS.canMsg, rtB.encodeUDS.sendUDS,
    rtP.CAN2output3_txInterval, rtP.CAN2output3_buffer);

  /* Logic: '<S5>/OR1' */
  rtB.OR1 = ((rtB.bmsLvPower != 0.0) || (rtB.Add != 0));

  /* DataTypeConversion: '<S5>/Data Type Conversion' */
  rtB.DataTypeConversion_a = rtB.OR1;

  /* Logic: '<S5>/OR' */
  rtB.OR = ((rtB.dIgnition != 0.0) || (rtB.ignition != 0.0));

  /* DataTypeConversion: '<S5>/Data Type Conversion1' */
  rtB.BusConversion_InsertedFor_Digit.digitalOutput3 = rtB.OR;
  
    /* End of UDS update process: '<S7>/DiagnosticCANProcess' */



/* @ RED 
*
* user code here 
*
*/


  /* set digital outputs - includes PWM control   */
  digitalOutputSet( <  example digital output array >);
  
  
  
  
  /* pack can data into array for Tx */
  
  
  /* example can tx */
  dcan1Messagebox1Transmit(rtB.Switch_d, rtB.DataTypeConversion_j,
    rtP.CAN1Txbuffer2_txInterval, rtP.CAN1Txbuffer2_buffer);



}

/* Model initialize function */
void EVOYAGER_VCU_2R1HW_initialize(void)
{
  /* Registration code */

  /* Initialize model as required
	* put code here that needs to be run on startup e.g key is on
  */
  EVOYAGER_VCU_2R1HW_InitializeDataMapInfo();

  {
/*@red  user code here */


}

/* Model terminate function 
*	put code here to execute on shutdown e.g key is off
*/
void EVOYAGER_VCU_2R1HW_terminate(void)
{
 /*@red  user code here */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
