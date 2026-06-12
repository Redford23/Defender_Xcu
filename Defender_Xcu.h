/*
 * File: EVOYAGER_VCU_2R1HW.h
 *
 * Code generated for Simulink model 'EVOYAGER_VCU_2R1HW'.
 *
 * Model version                  : 8.50
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Sun Apr 19 14:37:40 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EVOYAGER_VCU_2R1HW_h_
#define RTW_HEADER_EVOYAGER_VCU_2R1HW_h_
#ifndef EVOYAGER_VCU_2R1HW_COMMON_INCLUDES_
#define EVOYAGER_VCU_2R1HW_COMMON_INCLUDES_
#include <math.h>
#include "rtwtypes.h"
#include "can_message.h"
#endif                                 /* EVOYAGER_VCU_2R1HW_COMMON_INCLUDES_ */

#include "EVOYAGER_VCU_2R1HW_types.h"
#include "can_input_simulink.h"
#include "evp_UDS.h"
#include "evp_fee.h"
#include <string.h>
#include "rtw_modelmap.h"
#include "zero_crossing_types.h"

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

#define EVOYAGER_VCU_2R1HW_M           (rtM)

/* user code (top of header file) */
#include "can_input_simulink.h"
#include "evp_UDS.h"
#include "evp_fee.h"

/* Block states (default storage) for system '<S24>/Chart' */
typedef struct {
  uint32_T durationCounter_1;          /* '<S24>/Chart' */
  struct {
    uint_T is_c1_EVP_XCU_lib:2;        /* '<S24>/Chart' */
    uint_T is_active_c1_EVP_XCU_lib:1; /* '<S24>/Chart' */
  } bitsForTID0;
} DW_Chart;

/* Block states (default storage) for system '<S32>/Chart' */
typedef struct {
  uint32_T durationCounter_1;          /* '<S32>/Chart' */
  struct {
    uint_T is_c1_EVP_XCU_lib:2;        /* '<S32>/Chart' */
    uint_T is_active_c1_EVP_XCU_lib:1; /* '<S32>/Chart' */
  } bitsForTID0;
} DW_Chart_b;

/* Block signals (default storage) */
typedef struct {
  ANALOG_INPUT_BUS AnalogInputs;       /* '<Root>/Analog Inputs' */
  UDSDATARX udsDataRx;                 /* '<S1>/decodeUDS' */
  UDSDATATX encodeUDS;                 /* '<S3>/encodeUDS' */
  CAN_MESSAGE_BUS CANinput;            /* '<S41>/CAN input' */
  CAN_MESSAGE_BUS clearData;           /* '<S18>/clearData ' */
  CAN_MESSAGE_BUS Switch;              /* '<S18>/Switch' */
  CAN_MESSAGE_BUS CANinput_p;          /* '<S45>/CAN input' */
  CAN_MESSAGE_BUS clearData_i;         /* '<S19>/clearData ' */
  CAN_MESSAGE_BUS Switch_p;            /* '<S19>/Switch' */
  CAN_MESSAGE_BUS CANPack;             /* '<S2>/CAN Pack' */
  CAN_MESSAGE_BUS CANinput_f;          /* '<S25>/CAN input' */
  CAN_MESSAGE_BUS clearData_e;         /* '<S20>/clearData ' */
  CAN_MESSAGE_BUS Switch_n;            /* '<S20>/Switch' */
  CAN_MESSAGE_BUS CANinput_n;          /* '<S29>/CAN input' */
  CAN_MESSAGE_BUS clearData_j;         /* '<S21>/clearData ' */
  CAN_MESSAGE_BUS Switch_i;            /* '<S21>/Switch' */
  CAN_MESSAGE_BUS CANinput_np;         /* '<S33>/CAN input' */
  CAN_MESSAGE_BUS clearData_c;         /* '<S16>/clearData ' */
  CAN_MESSAGE_BUS Switch_k;            /* '<S16>/Switch' */
  CAN_MESSAGE_BUS CANinput_c;          /* '<S37>/CAN input' */
  CAN_MESSAGE_BUS clearData_a;         /* '<S17>/clearData ' */
  CAN_MESSAGE_BUS Switch_kp;           /* '<S17>/Switch' */
  CAN_MESSAGE_BUS CANinput_i;          /* '<S49>/CAN input' */
  CAN_MESSAGE_BUS clearData_cx;        /* '<S22>/clearData ' */
  CAN_MESSAGE_BUS Switch_c;            /* '<S22>/Switch' */
  CAN_MESSAGE_BUS CANPack1;            /* '<S2>/CAN Pack1' */
  CAN_MESSAGE_BUS CAN2input6;          /* '<S1>/CAN2 input6' */
  CAN_MESSAGE_BUS CANPack2;            /* '<S3>/CAN Pack2' */
  CAN_MESSAGE_BUS CANPack1_j;          /* '<S3>/CAN Pack1' */
  CAN_MESSAGE_BUS CANPack4;            /* '<S3>/CAN Pack4' */
  CAN_MESSAGE_BUS CANPack_o;           /* '<S3>/CAN Pack' */
  CAN_MESSAGE_BUS CANinput_g;          /* '<S53>/CAN input' */
  CAN_MESSAGE_BUS clearData_f;         /* '<S23>/clearData ' */
  CAN_MESSAGE_BUS Switch_d;            /* '<S23>/Switch' */
  DIGITAL_OUTPUT_BUS BusConversion_InsertedFor_Digit;
  DIGITAL_INPUT_BUS DigitalInputs;     /* '<Root>/Digital Inputs' */
  real_T Uk1;                          /* '<S43>/Delay Input1' */
  real_T batteryCapacity;              /* '<S1>/CAN Unpack8' */
  real_T batteryCurrent;               /* '<S1>/CAN Unpack8' */
  real_T batterySOC;                   /* '<S1>/CAN Unpack8' */
  real_T batterySOH;                   /* '<S1>/CAN Unpack8' */
  real_T batteryStatus;                /* '<S1>/CAN Unpack8' */
  real_T batteryTemp;                  /* '<S1>/CAN Unpack8' */
  real_T batteryVoltage;               /* '<S1>/CAN Unpack8' */
  real_T CANUnpack8_o8;                /* '<S1>/CAN Unpack8' */
  real_T CANUnpack8_o9;                /* '<S1>/CAN Unpack8' */
  real_T Uk1_d;                        /* '<S47>/Delay Input1' */
  real_T CANUnpack9_o1;                /* '<S1>/CAN Unpack9' */
  real_T CANUnpack9_o2;                /* '<S1>/CAN Unpack9' */
  real_T CANUnpack9_o3;                /* '<S1>/CAN Unpack9' */
  real_T CANUnpack9_o4;                /* '<S1>/CAN Unpack9' */
  real_T CANUnpack9_o5;                /* '<S1>/CAN Unpack9' */
  real_T m160_MaxdriveTemp;            /* '<S1>/Max of Elements' */
  real_T Uk1_j;                        /* '<S27>/Delay Input1' */
  real_T data_from_can1_messagebox2;   /* '<S1>/CAN Unpack' */
  real_T CANUnpack_o2;                 /* '<S1>/CAN Unpack' */
  real_T CANUnpack_o3;                 /* '<S1>/CAN Unpack' */
  real_T CANUnpack_o4;                 /* '<S1>/CAN Unpack' */
  real_T etc2_tsg;                     /* '<S1>/CAN Unpack' */
  real_T CANUnpack_o6;                 /* '<S1>/CAN Unpack' */
  real_T Uk1_a;                        /* '<S31>/Delay Input1' */
  real_T CANUnpack1_o1;                /* '<S1>/CAN Unpack1' */
  real_T eec2_ap1pos;                  /* '<S1>/CAN Unpack1' */
  real_T CANUnpack1_o3;                /* '<S1>/CAN Unpack1' */
  real_T CANUnpack1_o4;                /* '<S1>/CAN Unpack1' */
  real_T CANUnpack1_o5;                /* '<S1>/CAN Unpack1' */
  real_T CANUnpack1_o6;                /* '<S1>/CAN Unpack1' */
  real_T CANUnpack1_o7;                /* '<S1>/CAN Unpack1' */
  real_T CANUnpack1_o8;                /* '<S1>/CAN Unpack1' */
  real_T CANUnpack1_o9;                /* '<S1>/CAN Unpack1' */
  real_T Uk1_c;                        /* '<S35>/Delay Input1' */
  real_T m170_d1_vsm_state;            /* '<S1>/CAN Unpack10' */
  real_T m170_d2_inverter_state;       /* '<S1>/CAN Unpack10' */
  real_T can2Rx;                       /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o4;               /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o5;               /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o6;               /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o7;               /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o8;               /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o9;               /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o10;              /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o11;              /* '<S1>/CAN Unpack10' */
  real_T m170_d6_inverter_enable_lockout;/* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o13;              /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o14;              /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o15;              /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o16;              /* '<S1>/CAN Unpack10' */
  real_T CANUnpack10_o17;              /* '<S1>/CAN Unpack10' */
  real_T Uk1_n;                        /* '<S39>/Delay Input1' */
  real_T m167_d1_dc_bus_voltage;       /* '<S1>/CAN Unpack4' */
  real_T can2box2Timestamp;            /* '<S1>/CAN Unpack4' */
  real_T CANUnpack4_o3;                /* '<S1>/CAN Unpack4' */
  real_T CANUnpack4_o4;                /* '<S1>/CAN Unpack4' */
  real_T CANUnpack4_o5;                /* '<S1>/CAN Unpack4' */
  real_T Uk1_jh;                       /* '<S51>/Delay Input1' */
  real_T CANUnpack2_o1;                /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o2;                /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o3;                /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o4;                /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o5;                /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o6;                /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o7;                /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o8;                /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o9;                /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o10;               /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o11;               /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o12;               /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o13;               /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o14;               /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o15;               /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o16;               /* '<S1>/CAN Unpack2' */
  real_T NLG_S_Prox_Det;               /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o18;               /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o19;               /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o20;               /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o21;               /* '<S1>/CAN Unpack2' */
  real_T CANUnpack2_o22;               /* '<S1>/CAN Unpack2' */
  real_T Multiply;                     /* '<S2>/Multiply' */
  real_T CANUnpack5_o2;                /* '<S1>/CAN Unpack5' */
  real_T DataTypeConversion1;          /* '<S53>/Data Type Conversion1' */
  real_T Uk1_l;                        /* '<S55>/Delay Input1' */
  real_T initialiseCounter;            /* '<S4>/Discrete-Time Integrator' */
  real_T responseBytes;                /* '<S7>/DiagnosticCANProcess' */
  real_T secureAccess;                 /* '<S7>/DiagnosticCANProcess' */
  real_T sendNegativeResponse;         /* '<S7>/DiagnosticCANProcess' */
  real_T sendPositiveResponse;         /* '<S7>/DiagnosticCANProcess' */
  real_T testerPresent;                /* '<S7>/DiagnosticCANProcess' */
  real_T inhibitCharge;                /* '<S7>/DiagnosticCANProcess' */
  real_T inhibitDrive;                 /* '<S7>/DiagnosticCANProcess' */
  real_T pauseCanTx2;                  /* '<S7>/DiagnosticCANProcess' */
  real_T pauseCanTx1;                  /* '<S7>/DiagnosticCANProcess' */
  real_T ignition;                     /* '<S5>/IgnSWCheck' */
  real_T dIgnition;                    /* '<S5>/Chart' */
  real_T bmsLvPower;                   /* '<S5>/Chart' */
  real_T demand;                       /* '<S5>/Chart' */
  real_T direction;                    /* '<S5>/Chart' */
  real_T state;                        /* '<S5>/Chart' */
  real_T inverterEnable;               /* '<S5>/Chart' */
  real_T sendBatteryStatus;            /* '<S5>/Chart' */
  real_T inverterFault;                /* '<S5>/Chart' */
  real_T torqueLimit;                  /* '<S5>/Chart' */
  real_T torque;                       /* '<S5>/Chart' */
  real_T bCharge;                      /* '<S5>/Chart' */
  real_T bDrive;                       /* '<S5>/Chart' */
  uint32_T Constant2;                  /* '<S45>/Constant2' */
  uint32_T DataTypeConversion;         /* '<S7>/Data Type Conversion' */
  uint32_T evpFeeReadConfig_o2[32];    /* '<S59>/evpFeeReadConfig' */
  uint32_T Selector2;                  /* '<S61>/Selector2' */
  uint32_T Merge;                      /* '<S64>/Merge' */
  uint32_T Merge_o;                    /* '<S65>/Merge' */
  uint32_T Merge_c;                    /* '<S66>/Merge' */
  uint32_T Merge_k;                    /* '<S67>/Merge' */
  uint32_T VectorConcatenate[31];      /* '<S63>/Vector Concatenate' */
  uint32_T SumofElements;              /* '<S63>/Sum of Elements' */
  uint32_T VectorConcatenate1[32];     /* '<S63>/Vector Concatenate1' */
  uint32_T Selector1;                  /* '<S61>/Selector1' */
  real32_T DataTypeConversion2;        /* '<S5>/Data Type Conversion2' */
  real32_T Multiply_e;                 /* '<S5>/Multiply' */
  real32_T DataTypeConversion1_j;      /* '<S59>/Data Type Conversion1' */
  RESETCAUSEFORSIMULINK readresetcause1;/* '<S59>/read reset cause1' */
  FEE_WRITE_STATUS evpFeeReadConfig_o1;/* '<S59>/evpFeeReadConfig' */
  FEE_WRITE_STATUS evpFeeWriteConfig;  /* '<S62>/evpFeeWriteConfig' */
  uint8_T CANUnpack8_o10;              /* '<S1>/CAN Unpack8' */
  uint8_T CANUnpack8_o11;              /* '<S1>/CAN Unpack8' */
  uint8_T CANUnpack9_o6;               /* '<S1>/CAN Unpack9' */
  uint8_T CANUnpack9_o7;               /* '<S1>/CAN Unpack9' */
  uint8_T CANUnpack_o7;                /* '<S1>/CAN Unpack' */
  uint8_T CANUnpack1_o10;              /* '<S1>/CAN Unpack1' */
  uint8_T Compare;                     /* '<S84>/Compare' */
  uint8_T CANUnpack10_o18;             /* '<S1>/CAN Unpack10' */
  uint8_T CANUnpack4_o6;               /* '<S1>/CAN Unpack4' */
  uint8_T CANUnpack4_o7;               /* '<S1>/CAN Unpack4' */
  uint8_T CANUnpack2_o23;              /* '<S1>/CAN Unpack2' */
  uint8_T CANUnpack2_o24;              /* '<S1>/CAN Unpack2' */
  uint8_T Compare_k;                   /* '<S85>/Compare' */
  uint8_T CANUnpack5_o1[8];            /* '<S1>/CAN Unpack5' */
  uint8_T CANUnpack5_o3;               /* '<S1>/CAN Unpack5' */
  uint8_T DataTypeConversion1_a;       /* '<S7>/Data Type Conversion1' */
  uint8_T DataTypeConversion2_e;       /* '<S7>/Data Type Conversion2' */
  uint8_T DataTypeConversion_a;        /* '<S5>/Data Type Conversion' */
  uint8_T Output;                      /* '<S56>/Output' */
  uint8_T FixPtSum1;                   /* '<S57>/FixPt Sum1' */
  uint8_T FixPtSwitch;                 /* '<S58>/FixPt Switch' */
  uint8_T DataTypeConversion_j;        /* '<S2>/Data Type Conversion' */
  uint8_T txByte[7];                   /* '<S7>/DiagnosticCANProcess' */
  uint8_T Add;                         /* '<S87>/Add' */
  uint8_T sendM192;                    /* '<S5>/Chart' */
  uint8_T canTxEn;                     /* '<S5>/Chart' */
  boolean_T FixPtRelationalOperator;   /* '<S43>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_l; /* '<S47>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_a; /* '<S27>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_e; /* '<S31>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_b; /* '<S35>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_c; /* '<S39>/FixPt Relational Operator' */
  boolean_T FixPtRelationalOperator_j; /* '<S51>/FixPt Relational Operator' */
  boolean_T OR1;                       /* '<S5>/OR1' */
  boolean_T OR;                        /* '<S5>/OR' */
  boolean_T sendBatteryStatus_l;       /* '<S5>/AND' */
  boolean_T FixPtRelationalOperator_jx;/* '<S55>/FixPt Relational Operator' */
  boolean_T Compare_l;                 /* '<S60>/Compare' */
  boolean_T Equal;                     /* '<S61>/Equal' */
  boolean_T BitwiseNOT;                /* '<S61>/Bitwise NOT' */
  boolean_T OR1_p;                     /* '<S59>/OR1' */
  boolean_T TimedOut;                  /* '<S52>/Chart' */
  boolean_T TimedOut_e;                /* '<S48>/Chart' */
  boolean_T TimedOut_a;                /* '<S44>/Chart' */
  boolean_T TimedOut_c;                /* '<S40>/Chart' */
  boolean_T TimedOut_m;                /* '<S36>/Chart' */
  boolean_T TimedOut_g;                /* '<S32>/Chart' */
  boolean_T TimedOut_i;                /* '<S28>/Chart' */
  boolean_T TimedOut_o;                /* '<S24>/Chart' */
} B;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DelayInput1_DSTATE;           /* '<S43>/Delay Input1' */
  real_T DelayInput1_DSTATE_f;         /* '<S47>/Delay Input1' */
  real_T DelayInput1_DSTATE_e;         /* '<S27>/Delay Input1' */
  real_T DelayInput1_DSTATE_p;         /* '<S31>/Delay Input1' */
  real_T DelayInput1_DSTATE_m;         /* '<S35>/Delay Input1' */
  real_T DelayInput1_DSTATE_j;         /* '<S39>/Delay Input1' */
  real_T DelayInput1_DSTATE_d;         /* '<S51>/Delay Input1' */
  real_T DelayInput1_DSTATE_n;         /* '<S55>/Delay Input1' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S4>/Discrete-Time Integrator' */
  uint64_T SumofElements_DWORK1;       /* '<S63>/Sum of Elements' */
  int32_T sfEvent;                     /* '<S7>/DiagnosticCANProcess' */
  uint32_T receivedKey;                /* '<S7>/DiagnosticCANProcess' */
  uint32_T Add_DWORK1;                 /* '<S87>/Add' */
  uint32_T durationCounter_1;          /* '<S5>/IgnSWCheck' */
  uint32_T durationCounter_1_i;        /* '<S5>/IgnSWCheck' */
  uint32_T durationCounter_2;          /* '<S5>/IgnSWCheck' */
  uint32_T durationCounter_1_o;        /* '<S5>/Chart' */
  int_T CANUnpack8_ModeSignalID;       /* '<S1>/CAN Unpack8' */
  int_T CANUnpack8_StatusPortID;       /* '<S1>/CAN Unpack8' */
  int_T CANUnpack9_ModeSignalID;       /* '<S1>/CAN Unpack9' */
  int_T CANUnpack9_StatusPortID;       /* '<S1>/CAN Unpack9' */
  int_T CANPack_ModeSignalID;          /* '<S2>/CAN Pack' */
  int_T CANUnpack_ModeSignalID;        /* '<S1>/CAN Unpack' */
  int_T CANUnpack_StatusPortID;        /* '<S1>/CAN Unpack' */
  int_T CANUnpack1_ModeSignalID;       /* '<S1>/CAN Unpack1' */
  int_T CANUnpack1_StatusPortID;       /* '<S1>/CAN Unpack1' */
  int_T CANUnpack10_ModeSignalID;      /* '<S1>/CAN Unpack10' */
  int_T CANUnpack10_StatusPortID;      /* '<S1>/CAN Unpack10' */
  int_T CANUnpack4_ModeSignalID;       /* '<S1>/CAN Unpack4' */
  int_T CANUnpack4_StatusPortID;       /* '<S1>/CAN Unpack4' */
  int_T CANUnpack2_ModeSignalID;       /* '<S1>/CAN Unpack2' */
  int_T CANUnpack2_StatusPortID;       /* '<S1>/CAN Unpack2' */
  int_T CANPack1_ModeSignalID;         /* '<S2>/CAN Pack1' */
  int_T CANUnpack5_ModeSignalID;       /* '<S1>/CAN Unpack5' */
  int_T CANUnpack5_StatusPortID;       /* '<S1>/CAN Unpack5' */
  int_T CANPack2_ModeSignalID;         /* '<S3>/CAN Pack2' */
  int_T CANPack1_ModeSignalID_l;       /* '<S3>/CAN Pack1' */
  int_T CANPack4_ModeSignalID;         /* '<S3>/CAN Pack4' */
  int_T CANPack_ModeSignalID_e;        /* '<S3>/CAN Pack' */
  struct {
    uint_T is_c2_EVOYAGER_VCU_2R1HW:4; /* '<S7>/DiagnosticCANProcess' */
    uint_T is_c3_EVOYAGER_VCU_2R1HW:4; /* '<S5>/Chart' */
    uint_T is_keyChecker:3;            /* '<S7>/DiagnosticCANProcess' */
    uint_T is_Charge:3;                /* '<S5>/Chart' */
    uint_T is_sysDriveRun:3;           /* '<S5>/Chart' */
    uint_T is_c5_EVOYAGER_VCU_2R1HW:2; /* '<S5>/IgnSWCheck' */
    uint_T is_active_c2_EVOYAGER_VCU_2R1HW:1;/* '<S7>/DiagnosticCANProcess' */
    uint_T is_active_c5_EVOYAGER_VCU_2R1HW:1;/* '<S5>/IgnSWCheck' */
    uint_T is_active_c3_EVOYAGER_VCU_2R1HW:1;/* '<S5>/Chart' */
  } bitsForTID0;

  uint16_T temporalCounter_i1;         /* '<S7>/DiagnosticCANProcess' */
  uint16_T temporalCounter_i1_l;       /* '<S5>/Chart' */
  uint8_T Output_DSTATE;               /* '<S56>/Output' */
  uint8_T diagSessionType;             /* '<S7>/DiagnosticCANProcess' */
  DW_Chart sf_Chart_k;                 /* '<S52>/Chart' */
  DW_Chart_b sf_Chart_f;               /* '<S48>/Chart' */
  DW_Chart_b sf_Chart_n;               /* '<S44>/Chart' */
  DW_Chart_b sf_Chart_db;              /* '<S40>/Chart' */
  DW_Chart_b sf_Chart_d;               /* '<S36>/Chart' */
  DW_Chart_b sf_Chart_a;               /* '<S32>/Chart' */
  DW_Chart sf_Chart_j;                 /* '<S28>/Chart' */
  DW_Chart sf_Chart;                   /* '<S24>/Chart' */
} DW;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState writeConfigToFEE_Trig_ZCE;/* '<S59>/writeConfigToFEE' */
} PrevZCX;

/* Parameters (default storage) */
struct P_ {
  real_T CAN2RXBlock2_MessageBoxNum;
                                   /* Mask Parameter: CAN2RXBlock2_MessageBoxNum
                                    * Referenced by: '<S41>/Constant'
                                    */
  real_T CAN2RXBlock3_MessageBoxNum;
                                   /* Mask Parameter: CAN2RXBlock3_MessageBoxNum
                                    * Referenced by: '<S45>/Constant'
                                    */
  real_T CAN1RXBlock_MessageBoxNum; /* Mask Parameter: CAN1RXBlock_MessageBoxNum
                                     * Referenced by: '<S25>/Constant'
                                     */
  real_T CAN1RXBlock1_MessageBoxNum;
                                   /* Mask Parameter: CAN1RXBlock1_MessageBoxNum
                                    * Referenced by: '<S29>/Constant'
                                    */
  real_T CAN2RXBlock_MessageBoxNum; /* Mask Parameter: CAN2RXBlock_MessageBoxNum
                                     * Referenced by: '<S33>/Constant'
                                     */
  real_T CAN2RXBlock1_MessageBoxNum;
                                   /* Mask Parameter: CAN2RXBlock1_MessageBoxNum
                                    * Referenced by: '<S37>/Constant'
                                    */
  real_T CAN2RXBlock4_MessageBoxNum;
                                   /* Mask Parameter: CAN2RXBlock4_MessageBoxNum
                                    * Referenced by: '<S49>/Constant'
                                    */
  real_T CAN2RXBlock5_MessageBoxNum;
                                   /* Mask Parameter: CAN2RXBlock5_MessageBoxNum
                                    * Referenced by: '<S53>/Constant'
                                    */
  real_T CAN2RXBlock2_canid;           /* Mask Parameter: CAN2RXBlock2_canid
                                        * Referenced by: '<S41>/Constant1'
                                        */
  real_T CAN2RXBlock3_canid;           /* Mask Parameter: CAN2RXBlock3_canid
                                        * Referenced by: '<S45>/Constant1'
                                        */
  real_T CAN1RXBlock_canid;            /* Mask Parameter: CAN1RXBlock_canid
                                        * Referenced by: '<S25>/Constant1'
                                        */
  real_T CAN1RXBlock1_canid;           /* Mask Parameter: CAN1RXBlock1_canid
                                        * Referenced by: '<S29>/Constant1'
                                        */
  real_T CAN2RXBlock_canid;            /* Mask Parameter: CAN2RXBlock_canid
                                        * Referenced by: '<S33>/Constant1'
                                        */
  real_T CAN2RXBlock1_canid;           /* Mask Parameter: CAN2RXBlock1_canid
                                        * Referenced by: '<S37>/Constant1'
                                        */
  real_T CAN2RXBlock4_canid;           /* Mask Parameter: CAN2RXBlock4_canid
                                        * Referenced by: '<S49>/Constant1'
                                        */
  real_T CAN2RXBlock2_timeout;         /* Mask Parameter: CAN2RXBlock2_timeout
                                        * Referenced by: '<S40>/Constant'
                                        */
  real_T CAN2RXBlock3_timeout;         /* Mask Parameter: CAN2RXBlock3_timeout
                                        * Referenced by: '<S44>/Constant'
                                        */
  real_T CAN1RXBlock_timeout;          /* Mask Parameter: CAN1RXBlock_timeout
                                        * Referenced by: '<S24>/Constant'
                                        */
  real_T CAN1RXBlock1_timeout;         /* Mask Parameter: CAN1RXBlock1_timeout
                                        * Referenced by: '<S28>/Constant'
                                        */
  real_T CAN2RXBlock_timeout;          /* Mask Parameter: CAN2RXBlock_timeout
                                        * Referenced by: '<S32>/Constant'
                                        */
  real_T CAN2RXBlock1_timeout;         /* Mask Parameter: CAN2RXBlock1_timeout
                                        * Referenced by: '<S36>/Constant'
                                        */
  real_T CAN2RXBlock4_timeout;         /* Mask Parameter: CAN2RXBlock4_timeout
                                        * Referenced by: '<S48>/Constant'
                                        */
  real_T CAN2RXBlock5_timeout;         /* Mask Parameter: CAN2RXBlock5_timeout
                                        * Referenced by: '<S52>/Constant'
                                        */
  real_T DetectChange_vinit;           /* Mask Parameter: DetectChange_vinit
                                        * Referenced by: '<S43>/Delay Input1'
                                        */
  real_T DetectChange_vinit_l;         /* Mask Parameter: DetectChange_vinit_l
                                        * Referenced by: '<S47>/Delay Input1'
                                        */
  real_T DetectChange_vinit_f;         /* Mask Parameter: DetectChange_vinit_f
                                        * Referenced by: '<S27>/Delay Input1'
                                        */
  real_T DetectChange_vinit_lm;        /* Mask Parameter: DetectChange_vinit_lm
                                        * Referenced by: '<S31>/Delay Input1'
                                        */
  real_T DetectChange_vinit_b;         /* Mask Parameter: DetectChange_vinit_b
                                        * Referenced by: '<S35>/Delay Input1'
                                        */
  real_T DetectChange_vinit_e;         /* Mask Parameter: DetectChange_vinit_e
                                        * Referenced by: '<S39>/Delay Input1'
                                        */
  real_T DetectChange_vinit_h;         /* Mask Parameter: DetectChange_vinit_h
                                        * Referenced by: '<S51>/Delay Input1'
                                        */
  real_T DetectChange_vinit_fm;        /* Mask Parameter: DetectChange_vinit_fm
                                        * Referenced by: '<S55>/Delay Input1'
                                        */
  real32_T CompareToConstant1_const; /* Mask Parameter: CompareToConstant1_const
                                      * Referenced by: '<S60>/Constant'
                                      */
  uint32_T xCUHardwareConfig_CAN1BitRate;
                                /* Mask Parameter: xCUHardwareConfig_CAN1BitRate
                                 * Referenced by: '<S63>/CAN 1 Bitrate'
                                 */
  uint32_T xCUHardwareConfig_CAN2BitRate;
                                /* Mask Parameter: xCUHardwareConfig_CAN2BitRate
                                 * Referenced by: '<S63>/CAN2 Bitrate'
                                 */
  uint32_T xCUHardwareConfig_CAN3BitRate;
                                /* Mask Parameter: xCUHardwareConfig_CAN3BitRate
                                 * Referenced by: '<S63>/CAN3 Bitrate'
                                 */
  uint32_T xCUHardwareConfig_ModelStep;
                                  /* Mask Parameter: xCUHardwareConfig_ModelStep
                                   * Referenced by: '<S63>/model step'
                                   */
  uint32_T xCUHardwareConfig_Value10;
                                    /* Mask Parameter: xCUHardwareConfig_Value10
                                     * Referenced by: '<S63>/Constant10'
                                     */
  uint32_T xCUHardwareConfig_Value11;
                                    /* Mask Parameter: xCUHardwareConfig_Value11
                                     * Referenced by: '<S63>/Constant11'
                                     */
  uint32_T xCUHardwareConfig_Value12;
                                    /* Mask Parameter: xCUHardwareConfig_Value12
                                     * Referenced by: '<S63>/Constant12'
                                     */
  uint32_T xCUHardwareConfig_Value13;
                                    /* Mask Parameter: xCUHardwareConfig_Value13
                                     * Referenced by: '<S63>/Constant13'
                                     */
  uint32_T xCUHardwareConfig_Value14;
                                    /* Mask Parameter: xCUHardwareConfig_Value14
                                     * Referenced by: '<S63>/Constant14'
                                     */
  uint32_T xCUHardwareConfig_Value15;
                                    /* Mask Parameter: xCUHardwareConfig_Value15
                                     * Referenced by: '<S63>/Constant15'
                                     */
  uint32_T xCUHardwareConfig_Value16;
                                    /* Mask Parameter: xCUHardwareConfig_Value16
                                     * Referenced by: '<S63>/Constant16'
                                     */
  uint32_T xCUHardwareConfig_Value17;
                                    /* Mask Parameter: xCUHardwareConfig_Value17
                                     * Referenced by: '<S63>/Constant17'
                                     */
  uint32_T xCUHardwareConfig_Value18;
                                    /* Mask Parameter: xCUHardwareConfig_Value18
                                     * Referenced by: '<S63>/Constant18'
                                     */
  uint32_T xCUHardwareConfig_Value19;
                                    /* Mask Parameter: xCUHardwareConfig_Value19
                                     * Referenced by: '<S63>/Constant19'
                                     */
  uint32_T xCUHardwareConfig_Value20;
                                    /* Mask Parameter: xCUHardwareConfig_Value20
                                     * Referenced by: '<S63>/Constant20'
                                     */
  uint32_T xCUHardwareConfig_Value21;
                                    /* Mask Parameter: xCUHardwareConfig_Value21
                                     * Referenced by: '<S63>/Constant21'
                                     */
  uint32_T xCUHardwareConfig_Value22;
                                    /* Mask Parameter: xCUHardwareConfig_Value22
                                     * Referenced by: '<S63>/Constant22'
                                     */
  uint32_T xCUHardwareConfig_Value23;
                                    /* Mask Parameter: xCUHardwareConfig_Value23
                                     * Referenced by: '<S63>/Constant23'
                                     */
  uint32_T xCUHardwareConfig_Value24;
                                    /* Mask Parameter: xCUHardwareConfig_Value24
                                     * Referenced by: '<S63>/Constant24'
                                     */
  uint32_T xCUHardwareConfig_Value26;
                                    /* Mask Parameter: xCUHardwareConfig_Value26
                                     * Referenced by: '<S63>/Constant26'
                                     */
  uint32_T xCUHardwareConfig_Value27;
                                    /* Mask Parameter: xCUHardwareConfig_Value27
                                     * Referenced by: '<S63>/Constant27'
                                     */
  uint32_T xCUHardwareConfig_Value28;
                                    /* Mask Parameter: xCUHardwareConfig_Value28
                                     * Referenced by: '<S63>/Constant28'
                                     */
  uint32_T xCUHardwareConfig_Value5; /* Mask Parameter: xCUHardwareConfig_Value5
                                      * Referenced by: '<S63>/Constant5'
                                      */
  uint32_T xCUHardwareConfig_Value6; /* Mask Parameter: xCUHardwareConfig_Value6
                                      * Referenced by: '<S63>/Constant6'
                                      */
  uint32_T xCUHardwareConfig_Value7; /* Mask Parameter: xCUHardwareConfig_Value7
                                      * Referenced by: '<S63>/Constant7'
                                      */
  uint32_T xCUHardwareConfig_Value8; /* Mask Parameter: xCUHardwareConfig_Value8
                                      * Referenced by: '<S63>/Constant8'
                                      */
  uint32_T xCUHardwareConfig_Value9; /* Mask Parameter: xCUHardwareConfig_Value9
                                      * Referenced by: '<S63>/Constant9'
                                      */
  uint32_T CAN2RXBlock5_canid;         /* Mask Parameter: CAN2RXBlock5_canid
                                        * Referenced by: '<S53>/Constant1'
                                        */
  uint32_T CompareToConstant_const;   /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S84>/Constant'
                                       */
  uint32_T CompareToConstant1_const_g;
                                   /* Mask Parameter: CompareToConstant1_const_g
                                    * Referenced by: '<S85>/Constant'
                                    */
  uint32_T CAN2RxMessagebox_rxMask;   /* Mask Parameter: CAN2RxMessagebox_rxMask
                                       * Referenced by: '<S41>/Constant2'
                                       */
  uint32_T CAN1RxMessagebox_rxMask;   /* Mask Parameter: CAN1RxMessagebox_rxMask
                                       * Referenced by: '<S25>/Constant2'
                                       */
  uint32_T CAN1RxMessagebox_rxMask_n;
                                    /* Mask Parameter: CAN1RxMessagebox_rxMask_n
                                     * Referenced by: '<S29>/Constant2'
                                     */
  uint32_T CAN2RxMessagebox_rxMask_m;
                                    /* Mask Parameter: CAN2RxMessagebox_rxMask_m
                                     * Referenced by: '<S33>/Constant2'
                                     */
  uint32_T CAN2RxMessagebox_rxMask_i;
                                    /* Mask Parameter: CAN2RxMessagebox_rxMask_i
                                     * Referenced by: '<S37>/Constant2'
                                     */
  uint32_T CAN2RxMessagebox_rxMask_l;
                                    /* Mask Parameter: CAN2RxMessagebox_rxMask_l
                                     * Referenced by: '<S49>/Constant2'
                                     */
  uint32_T CAN2RxMessagebox_rxMask_j;
                                    /* Mask Parameter: CAN2RxMessagebox_rxMask_j
                                     * Referenced by: '<S53>/Constant2'
                                     */
  uint16_T CAN2RxMessagebox_rxMask_c;
                                    /* Mask Parameter: CAN2RxMessagebox_rxMask_c
                                     * Referenced by: '<S45>/Constant2'
                                     */
  uint8_T WrapToZero_Threshold;        /* Mask Parameter: WrapToZero_Threshold
                                        * Referenced by: '<S58>/FixPt Switch'
                                        */
  uint8_T CAN2RXBlock2_dlc;            /* Mask Parameter: CAN2RXBlock2_dlc
                                        * Referenced by: '<S41>/Constant3'
                                        */
  uint8_T CAN2RXBlock3_dlc;            /* Mask Parameter: CAN2RXBlock3_dlc
                                        * Referenced by: '<S45>/Constant3'
                                        */
  uint8_T CAN1RXBlock_dlc;             /* Mask Parameter: CAN1RXBlock_dlc
                                        * Referenced by: '<S25>/Constant3'
                                        */
  uint8_T CAN1RXBlock1_dlc;            /* Mask Parameter: CAN1RXBlock1_dlc
                                        * Referenced by: '<S29>/Constant3'
                                        */
  uint8_T CAN2RXBlock_dlc;             /* Mask Parameter: CAN2RXBlock_dlc
                                        * Referenced by: '<S33>/Constant3'
                                        */
  uint8_T CAN2RXBlock1_dlc;            /* Mask Parameter: CAN2RXBlock1_dlc
                                        * Referenced by: '<S37>/Constant3'
                                        */
  uint8_T CAN2RXBlock4_dlc;            /* Mask Parameter: CAN2RXBlock4_dlc
                                        * Referenced by: '<S49>/Constant3'
                                        */
  uint8_T CAN2RXBlock5_dlc;            /* Mask Parameter: CAN2RXBlock5_dlc
                                        * Referenced by: '<S53>/Constant3'
                                        */
  real_T Constant_Value;               /* Expression: 32
                                        * Referenced by: '<S61>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 32
                                        * Referenced by: '<S61>/Constant1'
                                        */
  real_T Constant1_Value_g;            /* Expression: 0
                                        * Referenced by: '<S59>/Constant1'
                                        */
  real_T Multiply_Gain;                /* Expression: 2
                                        * Referenced by: '<S2>/Multiply'
                                        */
  real_T CAN2input6_messageBox;        /* Expression: 6
                                        * Referenced by: '<S1>/CAN2 input6'
                                        */
  real_T CAN2input6_canFilterID;       /* Expression: 2016
                                        * Referenced by: '<S1>/CAN2 input6'
                                        */
  real_T Constant_Value_k;             /* Expression: 1
                                        * Referenced by: '<S7>/Constant'
                                        */
  real_T CAN2output3_txInterval;       /* Expression: 0
                                        * Referenced by: '<S3>/CAN2 output 3'
                                        */
  real_T CAN2output3_buffer;           /* Expression: 3
                                        * Referenced by: '<S3>/CAN2 output 3'
                                        */
  real_T Constant1_Value_f;            /* Expression: 1
                                        * Referenced by: '<S5>/Constant1'
                                        */
  real_T CAN2output0_txInterval;       /* Expression: 100
                                        * Referenced by: '<S3>/CAN2 output0'
                                        */
  real_T CAN2output0_buffer;           /* Expression: 0
                                        * Referenced by: '<S3>/CAN2 output0'
                                        */
  real_T CAN2output1_txInterval;       /* Expression: 100
                                        * Referenced by: '<S3>/CAN2 output1'
                                        */
  real_T CAN2output1_buffer;           /* Expression: 1
                                        * Referenced by: '<S3>/CAN2 output1'
                                        */
  real_T CAN2output3_txInterval_l;     /* Expression: 100
                                        * Referenced by: '<S3>/CAN2 output3'
                                        */
  real_T CAN2output3_buffer_k;         /* Expression: 5
                                        * Referenced by: '<S3>/CAN2 output3'
                                        */
  real_T CAN2output4_txInterval;       /* Expression: 100
                                        * Referenced by: '<S3>/CAN2 output4'
                                        */
  real_T CAN2output4_buffer;           /* Expression: 4
                                        * Referenced by: '<S3>/CAN2 output4'
                                        */
  real_T CAN1Txbuffer1_txInterval;     /* Expression: 100
                                        * Referenced by: '<S2>/CAN1 Tx buffer 1'
                                        */
  real_T CAN1Txbuffer1_buffer;         /* Expression: 1
                                        * Referenced by: '<S2>/CAN1 Tx buffer 1'
                                        */
  real_T CAN1Txbuffer0_txInterval;     /* Expression: 100
                                        * Referenced by: '<S2>/CAN1 Tx buffer 0'
                                        */
  real_T CAN1Txbuffer0_buffer;         /* Expression: 0
                                        * Referenced by: '<S2>/CAN1 Tx buffer 0'
                                        */
  real_T CAN1Txbuffer2_txInterval;     /* Expression: 100
                                        * Referenced by: '<S2>/CAN1 Tx buffer 2'
                                        */
  real_T CAN1Txbuffer2_buffer;         /* Expression: 2
                                        * Referenced by: '<S2>/CAN1 Tx buffer 2'
                                        */
  real_T Constant_Value_n;             /* Expression: 1
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T DiscreteTimeIntegrator_gainval;
                           /* Computed Parameter: DiscreteTimeIntegrator_gainval
                            * Referenced by: '<S4>/Discrete-Time Integrator'
                            */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: 0
                                        * Referenced by: '<S4>/Discrete-Time Integrator'
                                        */
  FEE_WRITE_STATUS Outport_Y0;         /* Computed Parameter: Outport_Y0
                                        * Referenced by: '<S62>/Outport'
                                        */
  real32_T Multiply_Gain_k;            /* Computed Parameter: Multiply_Gain_k
                                        * Referenced by: '<S5>/Multiply'
                                        */
  uint32_T MAXSTEPTIME_MS_Value;     /* Computed Parameter: MAXSTEPTIME_MS_Value
                                      * Referenced by: '<S64>/MAXSTEPTIME_MS'
                                      */
  uint32_T MINSTEPTIME_MS_Value;     /* Computed Parameter: MINSTEPTIME_MS_Value
                                      * Referenced by: '<S64>/MINSTEPTIME_MS'
                                      */
  uint32_T Constant25_Value;           /* Computed Parameter: Constant25_Value
                                        * Referenced by: '<S63>/Constant25'
                                        */
  uint32_T CAN500K_Value;              /* Expression: 0xF1302A97
                                        * Referenced by: '<S65>/CAN500K'
                                        */
  uint32_T CAN1000K_Value;             /* Expression: 0xF5402A8B
                                        * Referenced by: '<S65>/CAN1000K'
                                        */
  uint32_T CAN250K_Value;              /* Expression: 0xf9202aaf
                                        * Referenced by: '<S65>/CAN250K'
                                        */
  uint32_T CAN125K_Value;              /* Expression: 0xda112a9f
                                        * Referenced by: '<S65>/CAN125K'
                                        */
  uint32_T CAN500K_Value_l;            /* Expression: 0xF1302A97
                                        * Referenced by: '<S66>/CAN500K'
                                        */
  uint32_T CAN1000K_Value_k;           /* Expression: 0xF5402A8B
                                        * Referenced by: '<S66>/CAN1000K'
                                        */
  uint32_T CAN250K_Value_g;            /* Expression: 0xf9202aaf
                                        * Referenced by: '<S66>/CAN250K'
                                        */
  uint32_T CAN125K_Value_j;            /* Expression: 0xda112a9f
                                        * Referenced by: '<S66>/CAN125K'
                                        */
  uint32_T CAN500K_Value_a;            /* Expression: 0xF1302A97
                                        * Referenced by: '<S67>/CAN500K'
                                        */
  uint32_T CAN1000K_Value_n;           /* Expression: 0xF5402A8B
                                        * Referenced by: '<S67>/CAN1000K'
                                        */
  uint32_T CAN250K_Value_l;            /* Expression: 0xf9202aaf
                                        * Referenced by: '<S67>/CAN250K'
                                        */
  uint32_T CAN125K_Value_l;            /* Expression: 0xda112a9f
                                        * Referenced by: '<S67>/CAN125K'
                                        */
  uint32_T Constant_Value_h;           /* Computed Parameter: Constant_Value_h
                                        * Referenced by: '<S89>/Constant'
                                        */
  uint32_T Constant_Value_i;           /* Computed Parameter: Constant_Value_i
                                        * Referenced by: '<S87>/Constant'
                                        */
  uint32_T CAN2input6_rxMask;          /* Expression: 0x000007ff
                                        * Referenced by: '<S1>/CAN2 input6'
                                        */
  uint32_T encodeUDS_txID;             /* Expression: 0x000007e8
                                        * Referenced by: '<S3>/encodeUDS'
                                        */
  uint32_T Constant_Value_nv;          /* Computed Parameter: Constant_Value_nv
                                        * Referenced by: '<S6>/Constant'
                                        */
  uint32_T Constant2_Value;            /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S6>/Constant2'
                                        */
  uint32_T DigitalOutput_coilResistanceNom;/* Expression: uint32(40)
                                            * Referenced by: '<S6>/Digital Output'
                                            */
  uint32_T DigitalOutput_holdCurrentNomina;/* Expression: uint32(156)
                                            * Referenced by: '<S6>/Digital Output'
                                            */
  boolean_T Constant1_Value_n;         /* Computed Parameter: Constant1_Value_n
                                        * Referenced by: '<S87>/Constant1'
                                        */
  boolean_T Constant2_Value_n;         /* Computed Parameter: Constant2_Value_n
                                        * Referenced by: '<S87>/Constant2'
                                        */
  uint8_T Constant_Value_m;            /* Computed Parameter: Constant_Value_m
                                        * Referenced by: '<S58>/Constant'
                                        */
  uint8_T Out1_Y0;                     /* Computed Parameter: Out1_Y0
                                        * Referenced by: '<S87>/Out1'
                                        */
  uint8_T Constant_Value_kh[8];        /* Computed Parameter: Constant_Value_kh
                                        * Referenced by: '<S18>/Constant'
                                        */
  uint8_T Constant_Value_np[8];        /* Computed Parameter: Constant_Value_np
                                        * Referenced by: '<S19>/Constant'
                                        */
  uint8_T Constant_Value_c[8];         /* Computed Parameter: Constant_Value_c
                                        * Referenced by: '<S20>/Constant'
                                        */
  uint8_T Constant_Value_l[8];         /* Computed Parameter: Constant_Value_l
                                        * Referenced by: '<S21>/Constant'
                                        */
  uint8_T Constant_Value_e[8];         /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S16>/Constant'
                                        */
  uint8_T Constant_Value_ij[8];        /* Computed Parameter: Constant_Value_ij
                                        * Referenced by: '<S17>/Constant'
                                        */
  uint8_T Constant_Value_d[8];         /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S22>/Constant'
                                        */
  uint8_T Constant_Value_g[8];         /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S23>/Constant'
                                        */
  uint8_T CAN2input6_dlc;              /* Expression: 0x08
                                        * Referenced by: '<S1>/CAN2 input6'
                                        */
  uint8_T encodeUDS_extended;          /* Expression: 0x00
                                        * Referenced by: '<S3>/encodeUDS'
                                        */
  uint8_T constant6_Value;             /* Computed Parameter: constant6_Value
                                        * Referenced by: '<S5>/constant6'
                                        */
  uint8_T constant1_Value;             /* Computed Parameter: constant1_Value
                                        * Referenced by: '<S5>/constant1'
                                        */
  uint8_T constant2_Value;             /* Computed Parameter: constant2_Value
                                        * Referenced by: '<S5>/constant2'
                                        */
  uint8_T constant3_Value;             /* Computed Parameter: constant3_Value
                                        * Referenced by: '<S5>/constant3'
                                        */
  uint8_T Constant1_Value_d;           /* Computed Parameter: Constant1_Value_d
                                        * Referenced by: '<S6>/Constant1'
                                        */
  uint8_T Output_InitialCondition;/* Computed Parameter: Output_InitialCondition
                                   * Referenced by: '<S56>/Output'
                                   */
  uint8_T FixPtConstant_Value;        /* Computed Parameter: FixPtConstant_Value
                                       * Referenced by: '<S57>/FixPt Constant'
                                       */
};

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
  } DataMapInfo;
};

/* Block parameters (default storage) */
extern P rtP;

/* Block signals (default storage) */
extern B rtB;

/* Block states (default storage) */
extern DW rtDW;

/* Zero-crossing (trigger) state */
extern PrevZCX rtPrevZCX;

/* Model entry point functions */
extern void EVOYAGER_VCU_2R1HW_initialize(void);
extern void EVOYAGER_VCU_2R1HW_step(void);
extern void EVOYAGER_VCU_2R1HW_terminate(void);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  EVOYAGER_VCU_2R1HW_GetCAPIStaticMap(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

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
 * '<Root>' : 'EVOYAGER_VCU_2R1HW'
 * '<S1>'   : 'EVOYAGER_VCU_2R1HW/CAN data acquisition'
 * '<S2>'   : 'EVOYAGER_VCU_2R1HW/CAN1 output'
 * '<S3>'   : 'EVOYAGER_VCU_2R1HW/CAN2 output'
 * '<S4>'   : 'EVOYAGER_VCU_2R1HW/Startup Functions'
 * '<S5>'   : 'EVOYAGER_VCU_2R1HW/Subsystem'
 * '<S6>'   : 'EVOYAGER_VCU_2R1HW/Subsystem1'
 * '<S7>'   : 'EVOYAGER_VCU_2R1HW/UDS process '
 * '<S8>'   : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 1 RX Block'
 * '<S9>'   : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 1 RX Block1'
 * '<S10>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block'
 * '<S11>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block1'
 * '<S12>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block2'
 * '<S13>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block3'
 * '<S14>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block4'
 * '<S15>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block5'
 * '<S16>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/clearData'
 * '<S17>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/clearData1'
 * '<S18>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/clearData2'
 * '<S19>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/clearData3'
 * '<S20>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/clearData4'
 * '<S21>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/clearData5'
 * '<S22>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/clearData6'
 * '<S23>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/clearData7'
 * '<S24>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 1 RX Block/CAN RX Internal'
 * '<S25>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 1 RX Block/CAN1RxMessagebox'
 * '<S26>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 1 RX Block/CAN RX Internal/Chart'
 * '<S27>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 1 RX Block/CAN RX Internal/Detect Change'
 * '<S28>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 1 RX Block1/CAN RX Internal'
 * '<S29>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 1 RX Block1/CAN1RxMessagebox'
 * '<S30>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 1 RX Block1/CAN RX Internal/Chart'
 * '<S31>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 1 RX Block1/CAN RX Internal/Detect Change'
 * '<S32>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block/CAN RX Internal'
 * '<S33>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block/CAN2RxMessagebox'
 * '<S34>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block/CAN RX Internal/Chart'
 * '<S35>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block/CAN RX Internal/Detect Change'
 * '<S36>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block1/CAN RX Internal'
 * '<S37>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block1/CAN2RxMessagebox'
 * '<S38>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block1/CAN RX Internal/Chart'
 * '<S39>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block1/CAN RX Internal/Detect Change'
 * '<S40>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block2/CAN RX Internal'
 * '<S41>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block2/CAN2RxMessagebox'
 * '<S42>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block2/CAN RX Internal/Chart'
 * '<S43>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block2/CAN RX Internal/Detect Change'
 * '<S44>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block3/CAN RX Internal'
 * '<S45>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block3/CAN2RxMessagebox'
 * '<S46>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block3/CAN RX Internal/Chart'
 * '<S47>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block3/CAN RX Internal/Detect Change'
 * '<S48>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block4/CAN RX Internal'
 * '<S49>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block4/CAN2RxMessagebox'
 * '<S50>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block4/CAN RX Internal/Chart'
 * '<S51>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block4/CAN RX Internal/Detect Change'
 * '<S52>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block5/CAN RX Internal'
 * '<S53>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block5/CAN2RxMessagebox'
 * '<S54>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block5/CAN RX Internal/Chart'
 * '<S55>'  : 'EVOYAGER_VCU_2R1HW/CAN data acquisition/CAN 2 RX Block5/CAN RX Internal/Detect Change'
 * '<S56>'  : 'EVOYAGER_VCU_2R1HW/CAN2 output/Counter Free-Running'
 * '<S57>'  : 'EVOYAGER_VCU_2R1HW/CAN2 output/Counter Free-Running/Increment Real World'
 * '<S58>'  : 'EVOYAGER_VCU_2R1HW/CAN2 output/Counter Free-Running/Wrap To Zero'
 * '<S59>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function'
 * '<S60>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/Compare To Constant1'
 * '<S61>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/check data1'
 * '<S62>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/writeConfigToFEE'
 * '<S63>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig'
 * '<S64>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/CHECK STEP TIME'
 * '<S65>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR'
 * '<S66>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR1'
 * '<S67>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR2'
 * '<S68>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/CHECK STEP TIME/If Action Subsystem'
 * '<S69>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/CHECK STEP TIME/If Action Subsystem1'
 * '<S70>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/CHECK STEP TIME/If Action Subsystem2'
 * '<S71>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR/If Action Subsystem'
 * '<S72>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR/If Action Subsystem1'
 * '<S73>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR/If Action Subsystem2'
 * '<S74>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR/If Action Subsystem3'
 * '<S75>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR1/If Action Subsystem'
 * '<S76>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR1/If Action Subsystem1'
 * '<S77>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR1/If Action Subsystem2'
 * '<S78>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR1/If Action Subsystem3'
 * '<S79>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR2/If Action Subsystem'
 * '<S80>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR2/If Action Subsystem1'
 * '<S81>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR2/If Action Subsystem2'
 * '<S82>'  : 'EVOYAGER_VCU_2R1HW/Startup Functions/Initialize Function/xCUHardwareConfig/select CAN BTR2/If Action Subsystem3'
 * '<S83>'  : 'EVOYAGER_VCU_2R1HW/Subsystem/Chart'
 * '<S84>'  : 'EVOYAGER_VCU_2R1HW/Subsystem/Compare To Constant'
 * '<S85>'  : 'EVOYAGER_VCU_2R1HW/Subsystem/Compare To Constant1'
 * '<S86>'  : 'EVOYAGER_VCU_2R1HW/Subsystem/IgnSWCheck'
 * '<S87>'  : 'EVOYAGER_VCU_2R1HW/UDS process /BMSupdateMode'
 * '<S88>'  : 'EVOYAGER_VCU_2R1HW/UDS process /DiagnosticCANProcess'
 * '<S89>'  : 'EVOYAGER_VCU_2R1HW/UDS process /jumpToBootloader'
 */
#endif                                 /* RTW_HEADER_EVOYAGER_VCU_2R1HW_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
