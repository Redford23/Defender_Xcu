/*
 * File: XCU_UDSonly_capi.c
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

#include <stddef.h>
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "XCU_UDSonly_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#ifndef SS_UINT64
#define SS_UINT64                      20
#endif

#ifndef SS_INT64
#define SS_INT64                       21
#endif

#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "XCU_UDSonly.h"
#include "XCU_UDSonly_capi.h"
#include "XCU_UDSonly_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* Block output signal information */
static const rtwCAPI_Signals rtBlockSignals[] = {
  /* addrMapIndex, sysNum, blockPath,
   * signalName, portNumber, dataTypeIndex, dimIndex, fxpIndex, sTimeIndex
   */
  { 0, 0, TARGET_STRING("XCU_UDSonly/CAN data acquisition/decodeUDS"),
    TARGET_STRING("udsDataRx"), 0, 1, 0, 0, 0 },

  { 1, 2, TARGET_STRING("XCU_UDSonly/UDS process 1/DiagnosticCANProcess"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 2, 2, TARGET_STRING("XCU_UDSonly/UDS process 1/DiagnosticCANProcess"),
    TARGET_STRING(""), 1, 2, 0, 0, 0 },

  { 3, 2, TARGET_STRING("XCU_UDSonly/UDS process 1/DiagnosticCANProcess"),
    TARGET_STRING(""), 2, 2, 0, 0, 0 },

  { 4, 2, TARGET_STRING("XCU_UDSonly/UDS process 1/DiagnosticCANProcess"),
    TARGET_STRING(""), 3, 2, 0, 0, 0 },

  { 5, 2, TARGET_STRING("XCU_UDSonly/UDS process 1/DiagnosticCANProcess"),
    TARGET_STRING(""), 4, 2, 0, 0, 0 },

  { 6, 2, TARGET_STRING("XCU_UDSonly/UDS process 1/DiagnosticCANProcess"),
    TARGET_STRING(""), 5, 0, 2, 0, 0 },

  { 7, 2, TARGET_STRING("XCU_UDSonly/UDS process 1/DiagnosticCANProcess"),
    TARGET_STRING(""), 6, 2, 0, 0, 0 },

  { 8, 2, TARGET_STRING("XCU_UDSonly/UDS process 1/DiagnosticCANProcess"),
    TARGET_STRING(""), 7, 2, 0, 0, 0 },

  { 9, 2, TARGET_STRING("XCU_UDSonly/UDS process 1/DiagnosticCANProcess"),
    TARGET_STRING(""), 8, 2, 0, 0, 0 },

  { 10, 2, TARGET_STRING("XCU_UDSonly/UDS process 1/DiagnosticCANProcess"),
    TARGET_STRING(""), 9, 2, 0, 0, 0 },

  { 11, 0, TARGET_STRING("XCU_UDSonly/UDS process 1/Data Type Conversion"),
    TARGET_STRING(""), 0, 3, 0, 0, 0 },

  { 12, 0, TARGET_STRING("XCU_UDSonly/UDS process 1/Data Type Conversion1"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 13, 0, TARGET_STRING("XCU_UDSonly/UDS process 1/Data Type Conversion2"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 14, 0, TARGET_STRING(
    "XCU_UDSonly/CAN data acquisition/CAN2RxMessagebox1/CAN input"),
    TARGET_STRING(""), 0, 4, 0, 0, 0 },

  { 15, 0, TARGET_STRING("XCU_UDSonly/CAN2 output/Subsystem/encodeUDS"),
    TARGET_STRING(""), 0, 5, 0, 0, 0 },

  {
    0, 0, (NULL), (NULL), 0, 0, 0, 0, 0
  }
};

static const rtwCAPI_BlockParameters rtBlockParameters[] = {
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  { 16, TARGET_STRING("XCU_UDSonly/CAN data acquisition/CAN2RxMessagebox1"),
    TARGET_STRING("MessageBoxNum"), 2, 0, 0 },

  { 17, TARGET_STRING("XCU_UDSonly/CAN data acquisition/CAN2RxMessagebox1"),
    TARGET_STRING("canID"), 2, 0, 0 },

  { 18, TARGET_STRING("XCU_UDSonly/CAN data acquisition/CAN2RxMessagebox1"),
    TARGET_STRING("rxMask"), 3, 0, 0 },

  { 19, TARGET_STRING("XCU_UDSonly/CAN data acquisition/CAN2RxMessagebox1"),
    TARGET_STRING("dlc"), 0, 0, 0 },

  { 20, TARGET_STRING("XCU_UDSonly/CAN2 output/CAN2 Tx Buffer 1"),
    TARGET_STRING("intervalmS"), 2, 0, 0 },

  { 21, TARGET_STRING("XCU_UDSonly/CAN2 output/CAN2 Tx Buffer 1"),
    TARGET_STRING("buffernumber"), 2, 0, 0 },

  { 22, TARGET_STRING("XCU_UDSonly/CAN2 output/Subsystem"),
    TARGET_STRING("CAN_ID"), 3, 0, 0 },

  { 23, TARGET_STRING("XCU_UDSonly/UDS process 1/Constant"),
    TARGET_STRING("Value"), 2, 0, 0 },

  { 24, TARGET_STRING("XCU_UDSonly/CAN2 output/Subsystem/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 25, TARGET_STRING("XCU_UDSonly/UDS process 1/BMSupdateMode/Constant"),
    TARGET_STRING("Value"), 3, 0, 0 },

  { 26, TARGET_STRING("XCU_UDSonly/UDS process 1/jumpToBootloader/Constant"),
    TARGET_STRING("Value"), 3, 0, 0 },

  {
    0, (NULL), (NULL), 0, 0, 0
  }
};

/* Tunable variable parameters */
static const rtwCAPI_ModelParameters rtModelParameters[] = {
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  { 0, (NULL), 0, 0, 0 }
};

#ifndef HOST_CAPI_BUILD

/* Declare Data Addresses statically */
static void* rtDataAddrMap[] = {
  &rtB.udsDataRx,                      /* 0: Signal */
  &rtB.responseBytes,                  /* 1: Signal */
  &rtB.secureAccess,                   /* 2: Signal */
  &rtB.sendNegativeResponse,           /* 3: Signal */
  &rtB.sendPositiveResponse,           /* 4: Signal */
  &rtB.testerPresent,                  /* 5: Signal */
  &rtB.txByte[0],                      /* 6: Signal */
  &rtB.inhibitCharge,                  /* 7: Signal */
  &rtB.inhibitDrive,                   /* 8: Signal */
  &rtB.pauseCanTx2,                    /* 9: Signal */
  &rtB.pauseCanTx1,                    /* 10: Signal */
  &rtB.DataTypeConversion,             /* 11: Signal */
  &rtB.DataTypeConversion1,            /* 12: Signal */
  &rtB.DataTypeConversion2,            /* 13: Signal */
  &rtB.CANinput,                       /* 14: Signal */
  &rtB.encodeUDS,                      /* 15: Signal */
  &rtP.CAN2RxMessagebox1_MessageBoxNum,/* 16: Mask Parameter */
  &rtP.CAN2RxMessagebox1_canID,        /* 17: Mask Parameter */
  &rtP.CAN2RxMessagebox1_rxMask,       /* 18: Mask Parameter */
  &rtP.CAN2RxMessagebox1_dlc,          /* 19: Mask Parameter */
  &rtP.CAN2TxBuffer1_intervalmS,       /* 20: Mask Parameter */
  &rtP.CAN2TxBuffer1_buffernumber,     /* 21: Mask Parameter */
  &rtP.Subsystem_CAN_ID,               /* 22: Mask Parameter */
  &rtP.Constant_Value,                 /* 23: Block Parameter */
  &rtP.Constant_Value_k,               /* 24: Block Parameter */
  &rtP.Constant_Value_c,               /* 25: Block Parameter */
  &rtP.Constant_Value_d,               /* 26: Block Parameter */
};

/* Declare Data Run-Time Dimension Buffer Addresses statically */
static int32_T* rtVarDimsAddrMap[] = {
  (NULL)
};

#endif

/* Data Type Map - use dataTypeMapIndex to access this structure */
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] = {
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer, enumStorageType */
  { "unsigned char", "uint8_T", 0, 0, sizeof(uint8_T), (uint8_T)SS_UINT8, 0, 0,
    0 },

  { "struct", "UDSDATARX", 5, 1, sizeof(UDSDATARX), (uint8_T)SS_STRUCT, 0, 0, 0
  },

  { "double", "real_T", 0, 0, sizeof(real_T), (uint8_T)SS_DOUBLE, 0, 0, 0 },

  { "unsigned int", "uint32_T", 0, 0, sizeof(uint32_T), (uint8_T)SS_UINT32, 0, 0,
    0 },

  { "struct", "CAN_MESSAGE_BUS", 7, 6, sizeof(CAN_MESSAGE_BUS), (uint8_T)
    SS_STRUCT, 0, 0, 0 },

  { "struct", "UDSDATATX", 2, 13, sizeof(UDSDATATX), (uint8_T)SS_STRUCT, 0, 0, 0
  }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

/* Structure Element Map - use elemMapIndex to access this structure */
static TARGET_CONST rtwCAPI_ElementMap rtElementMap[] = {
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  { (NULL), 0, 0, 0, 0 },

  { "pCI", rt_offsetof(UDSDATARX, pCI), 0, 0, 0 },

  { "uDSData", rt_offsetof(UDSDATARX, uDSData), 0, 1, 0 },

  { "sID", rt_offsetof(UDSDATARX, sID), 0, 0, 0 },

  { "framesToSend", rt_offsetof(UDSDATARX, framesToSend), 0, 0, 0 },

  { "clearToSend", rt_offsetof(UDSDATARX, clearToSend), 0, 0, 0 },

  { "Extended", rt_offsetof(CAN_MESSAGE_BUS, Extended), 0, 0, 0 },

  { "Length", rt_offsetof(CAN_MESSAGE_BUS, Length), 0, 0, 0 },

  { "Remote", rt_offsetof(CAN_MESSAGE_BUS, Remote), 0, 0, 0 },

  { "Error", rt_offsetof(CAN_MESSAGE_BUS, Error), 0, 0, 0 },

  { "ID", rt_offsetof(CAN_MESSAGE_BUS, ID), 3, 0, 0 },

  { "Timestamp", rt_offsetof(CAN_MESSAGE_BUS, Timestamp), 2, 0, 0 },

  { "Data", rt_offsetof(CAN_MESSAGE_BUS, Data), 0, 3, 0 },

  { "canMsg", rt_offsetof(UDSDATATX, canMsg), 4, 0, 0 },

  { "sendUDS", rt_offsetof(UDSDATATX, sendUDS), 0, 0, 0 }
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static const rtwCAPI_DimensionMap rtDimensionMap[] = {
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  { rtwCAPI_SCALAR, 0, 2, 0 },

  { rtwCAPI_VECTOR, 2, 2, 0 },

  { rtwCAPI_VECTOR, 4, 2, 0 },

  { rtwCAPI_VECTOR, 6, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static const uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  1,                                   /* 1 */
  34,                                  /* 2 */
  1,                                   /* 3 */
  7,                                   /* 4 */
  1,                                   /* 5 */
  8,                                   /* 6 */
  1                                    /* 7 */
};

/* C-API stores floating point values in an array. The elements of this  *
 * are unique. This ensures that values which are shared across the model*
 * are stored in the most efficient way. These values are referenced by  *
 *           - rtwCAPI_FixPtMap.fracSlopePtr,                            *
 *           - rtwCAPI_FixPtMap.biasPtr,                                 *
 *           - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
 *           - rtwCAPI_SampleTimeMap.sampleOffsetPtr                     */
static const real_T rtcapiStoredFloats[] = {
  0.01, 0.0
};

/* Fixed Point Map */
static const rtwCAPI_FixPtMap rtFixPtMap[] = {
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { (NULL), (NULL), rtwCAPI_FIX_RESERVED, 0, 0, (boolean_T)0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static const rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  { (const void *) &rtcapiStoredFloats[0], (const void *) &rtcapiStoredFloats[1],
    (int8_T)0, (uint8_T)0 }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {
  /* Signals:{signals, numSignals,
   *           rootInputs, numRootInputs,
   *           rootOutputs, numRootOutputs},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  { rtBlockSignals, 16,
    (NULL), 0,
    (NULL), 0 },

  { rtBlockParameters, 11,
    rtModelParameters, 0 },

  { (NULL), 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 1304139612U,
    3359870734U,
    246540548U,
    193176864U },
  (NULL), 0,
  (boolean_T)0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  XCU_UDSonly_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void XCU_UDSonly_InitializeDataMapInfo(void)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(rtM->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(rtM->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(rtM->DataMapInfo.mmi, (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap(rtM->DataMapInfo.mmi, rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap(rtM->DataMapInfo.mmi, rtVarDimsAddrMap);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(rtM->DataMapInfo.mmi, (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(rtM->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArrayLen(rtM->DataMapInfo.mmi, 0);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C"
{

#endif

  void XCU_UDSonly_host_InitializeDataMapInfo(XCU_UDSonly_host_DataMapInfo_T
    *dataMap, const char *path)
  {
    /* Set C-API version */
    rtwCAPI_SetVersion(dataMap->mmi, 1);

    /* Cache static C-API data into the Real-time Model Data structure */
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);

    /* host data address map is NULL */
    rtwCAPI_SetDataAddressMap(dataMap->mmi, (NULL));

    /* host vardims address map is NULL */
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, (NULL));

    /* Set Instance specific path */
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, (NULL));

    /* Set reference to submodels */
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (NULL));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
  }

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
