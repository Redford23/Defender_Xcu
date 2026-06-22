/*
 * evp_UDS.h
 *
 *  Created on: 25 Apr 2022
 *      Author: MarcWork
 *
 * UDS functions for EVP controller
 * extracted from simulink C function blocks for compatability with R2019b
 *
 */

#ifndef INCLUDE_EVP_UDS_H_
#define INCLUDE_EVP_UDS_H_

#include "can_input_simulink.h"

#define CAN_MSGID_MFR           0x5a0
#define CAN_API_UPD                     CAN_MSGID_MFR
#define CAN_COMMAND_PING               (CAN_API_UPD | 0) << 0
#define CAN_COMMAND_ADDR_SIZE           (CAN_API_UPD | 1) << 0
#define CAN_COMMAND_RUN                (CAN_API_UPD | 2) << 0
#define CAN_COMMAND_READ               (CAN_API_UPD | 3) << 0
#define CAN_COMMAND_DATA                (CAN_API_UPD | 4) << 0
#define CAN_COMMAND_RESET              (CAN_API_UPD | 5) << 0

/* response */
#define CAN_RESPONSE_ACK                (CAN_API_UPD | 6) << 0
#define CAN_RESPONSE_TX_DATA               (CAN_API_UPD | 7) << 0
#define CAN_RESPONSE_NEGATIVE               (CAN_API_UPD | 8) << 0
#define CAN_UDS_IDLE                                (CAN_API_UPD | 0x0A) << 0

typedef struct
{
    unsigned char pCI;
    unsigned char uDSData [34];
    unsigned char sID;
    unsigned char framesToSend;
    unsigned char clearToSend;

}UDSDATARX;

typedef struct
{
    CAN_MESSAGE_BUS canMsg;
    unsigned char sendUDS;

}UDSDATATX;

unsigned int jumptobootvalue, bmsUpdatevalue;

UDSDATARX udsDecode(const unsigned char g_pucCommandBuffer[8]);
UDSDATATX udsEncode(unsigned int responseBytes, unsigned int txID, unsigned char negative, unsigned char positive, unsigned char pCI, const unsigned char txByte[7], unsigned char extended);
void jumpToBootloader(unsigned int value);

/*dec 2020 use bms update mode reguest to verify update has UDS functions working fully
             * invalidate block one to block bootloader
             * has no effect if block is already invalid */
void bmsUpdateMode(unsigned int value);

#endif /* INCLUDE_EVP_UDS_H_ */
