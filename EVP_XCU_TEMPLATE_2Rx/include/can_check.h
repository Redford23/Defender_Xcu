//*****************************************************************************
//
// can_check.h - Definitions for the CAN timing check function.
//
//*****************************************************************************

#ifndef __CAN_CHECK_H__
#define __CAN_CHECK_H__


#include "sys_common.h"

/*BRPE 1, BRP 32, (1 x 64)+ 32 gives prescaler of 96, seg1 11, seg2 3, SJW 3,sample point 80% */
#define DEFAULT_BTR_VALUE_125K 0xda112a9fU

/*BRPE 0, BRP 48, seg1 11, seg2 3, SJW 3,sample point 80% */
#define DEFAULT_BTR_VALUE_250K 0xf9202aafU

/*BRPE 0, BRP 24, seg1 11, seg2 3, SJW 3,sample point 80% */
#define DEFAULT_BTR_VALUE_500K 0xf1302a97U

/*BRPE 0, BRP 12, seg1 11, seg2 3, SJW 3,sample point 80% */
#define DEFAULT_BTR_VALUE_1000K 0xf5402a8bU

#define MINIMUM_BIT_TIME 980 // 1 Mbit 2% minimum bit time expected for xcu

#define TARGET_BITRATE_125K 0x00100000U
#define TARGET_BITRATE_250K 0x00200000U
#define TARGET_BITRATE_500K 0x00300000U
#define TARGET_BITRATE_1000K 0x00400000U
#define VCLKA1_FREQ 180 //can module clock in Mhz
#define SYNC_SEG 1U
/* min max values for calculated valid combinations at 180mhz clock */
#define BRP_MAX 180
#define BRP_MIN 8
#define TSEG1_MAX 16
#define TSEG1_MIN 4
#define TSEG2_MAX 4
#define TSEG2_MIN 2
#define CAN_SAMPLE_POINT_MAX 90.0
#define CAN_SAMPLE_POINT_MIN 70.0

//*****************************************************************************
//
// Prototype for the CAN timing check function.
//
//*****************************************************************************
uint32_t CheckCanTiming(uint32_t btrValue, volatile float maxTimingError);


#endif // __CAN_CHECK_H__
