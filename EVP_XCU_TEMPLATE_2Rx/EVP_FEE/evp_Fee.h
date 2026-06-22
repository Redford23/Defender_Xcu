/*
 * evp_Fee.h
 *
 *  Created on: 27 Apr 2022
 *      Author: MarcWork
 */

#ifndef INCLUDE_EVP_FEE_H_
#define INCLUDE_EVP_FEE_H_

#define USE_FEE_FUNCTIONS
#define SIMULINK_FEEDATA_BLOCKSIZEWORDS (USER_BLOCK_SIZE >> 2U)
#define SIMULINK_FEEDATA_BLOCKSIZEBYTES USER_BLOCK_SIZE
#define SIMULINK_CONFIG_BLOCK 3U
#define SIMULINK_FEEDATA_STARTBLOCK 4U
#define SIMULINK_FEEDATA_SIZEWORDS 768U
#define SIMULINK_FEEDATA_SIZEBYTES (SIMULINK_FEEDATA_SIZEWORDS * 4U)
/* config variable array index*/
#define SIMULINKMODELSTEP 0
#define CAN1BITRATE 1
#define CAN2BITRATE 2
#define CAN3BITRATE 3
#define CAN1BTR 28
#define CAN2BTR 29
#define CAN3BTR 30
#define CONFIGINDEX 31

#define MINIMUM_STEP_TIME 5 // model task step time mS
#define MAXIMUM_STEP_TIME 300 // model task step time mS

#include "ti_fee.h"

typedef enum
{
    FEE_JOB_IDLE,
    FEE_JOB_PENDING,
    FEE_JOB_COMPLETE,
    FEE_JOB_FAILED,
    FEE_JOB_INVALID_PARAMETERS
}FEE_WRITE_STATUS;
FEE_WRITE_STATUS fee_write_status;

unsigned long feeWriteTaskOperationValue;
unsigned long feeReadTaskOperationValue;

unsigned int evpFeeJobStatus;
volatile unsigned int feeConfigData[SIMULINK_FEEDATA_BLOCKSIZEWORDS];
volatile unsigned int userData_BlockNumber,userData_WordNumber,userData_Length,userData_Word, userDataWriteNumber;
unsigned char feeTaskRamBlock[128U];
unsigned char* userDataReadBuffer;




/* ti fee reads / writes */
/* declaring user data buffer as array with size means simulink checks data size matches on model build */
FEE_WRITE_STATUS evpFeeWriteUserBlock (unsigned int userBlockNumber, const unsigned int userWriteData[32]);
FEE_WRITE_STATUS evpFeeWriteBlock (unsigned int userBlockNumber, const unsigned int userWriteData[32]);
FEE_WRITE_STATUS evpFeeWriteData (const unsigned int writeData[SIMULINK_FEEDATA_SIZEWORDS]);
FEE_WRITE_STATUS evpFeeReadUserBlock (unsigned int userBlockNumber, unsigned int userReadData[32]);
FEE_WRITE_STATUS evpFeeReadBlock (unsigned int userBlockNumber, unsigned int userReadData[32]);
FEE_WRITE_STATUS evpFeeReadData (unsigned int ReadData[SIMULINK_FEEDATA_SIZEWORDS]);
FEE_WRITE_STATUS evpFeeWriteConfig (const unsigned int configWriteData[SIMULINK_FEEDATA_BLOCKSIZEWORDS]);
FEE_WRITE_STATUS evpFeeReadConfig (unsigned int configReadData[SIMULINK_FEEDATA_BLOCKSIZEWORDS]);
FEE_WRITE_STATUS getEvpFeeStatus (void);

#endif /* INCLUDE_EVP_FEE_H_ */
