/*
 * UDS functions for EVP controller
 * extracted from simulink C function blocks for compatability with R2019b
 * April 2022
 *
 */
#include "evp_UDS.h"


UDSDATARX udsDecode(const unsigned char g_pucCommandBuffer[8])
{
    static unsigned int nBytes = 0;
    static unsigned int rxByteIndex = 0;
#ifdef FRAMECOUNTER
    static unsigned char frameCounter = 0;
#endif
    static unsigned char i = 0;
    static unsigned char lastSID = 0;

    UDSDATARX udsDataRx;

    udsDataRx.pCI = (g_pucCommandBuffer[0] & 0xf0);
    udsDataRx.pCI >>= 4;

    if(udsDataRx.pCI == 0U)   // we have received single frame -
    {
        nBytes = (g_pucCommandBuffer[0] & 0x0f);
        udsDataRx.sID = g_pucCommandBuffer[1];
        lastSID = udsDataRx.sID;
        if (nBytes > 1U)
        {
            for (i = 0; i < 6; i++)
            {
                udsDataRx.uDSData[i] = g_pucCommandBuffer[(i+2)];
            }
        }
        else
        {//clear buffer
            for (i = 0; i < 6; i++)
            {
                udsDataRx.uDSData[i] = 0U;
            }

        }

    }
    else if (udsDataRx.pCI == 1U) // we have first frame
    {
        nBytes = (g_pucCommandBuffer[0] & 0x0f);
        nBytes <<= 8;
        nBytes += g_pucCommandBuffer[1];
        udsDataRx.sID = g_pucCommandBuffer[2];
        lastSID = udsDataRx.sID;
        rxByteIndex = 0;
#ifdef FRAMECOUNTER
        frameCounter = 0U;
#endif
        for (i=0; i<5; i++)
        {
            udsDataRx.uDSData[rxByteIndex] = g_pucCommandBuffer[(i+3)];
            rxByteIndex ++;
        }

    }
    else if (udsDataRx.pCI == 2U) // consecutive frame
    { // received some data!! sort into sensible buffer order
#ifdef FRAMECOUNTER
        frameCounter = (g_pucCommandBuffer[0] & 0x0fU);
#endif
        udsDataRx.sID = lastSID;
        for (i=0; i<7; i++)
        {
            if(rxByteIndex < nBytes)
            {
                udsDataRx.uDSData[rxByteIndex] = g_pucCommandBuffer[(i+1)];
                rxByteIndex ++;
            }
        }

    }
    else if (udsDataRx.pCI == 3U)     // flow control frame (FC)
    {
        udsDataRx.framesToSend = g_pucCommandBuffer[1]; // number of frames we can send before waiting for next FC frame
        udsDataRx.clearToSend = g_pucCommandBuffer[0] & 0x0f;
        udsDataRx.sID = lastSID;
    }

    return udsDataRx;
}

UDSDATATX udsEncode (unsigned int responseBytes, unsigned int txID, unsigned char negative, unsigned char positive, unsigned char pCI, const unsigned char txByte[7], unsigned char extended)
{
    static unsigned int flowControlResponse = 0;
    UDSDATATX txData;
    txData.sendUDS = 0;


    /*  uds response C function */
    /*  2021 EVP                */

    if (positive == 1)
    {
        flowControlResponse = 0;
        txData.canMsg.ID = (txID & 0x1FFFFFFF);
        txData.canMsg.Length = 0x08U;
        txData.canMsg.Extended = extended;
        txData.sendUDS = 1;
        txData.canMsg.Data[0] = responseBytes;
        txData.canMsg.Data[1] = txByte[0];

        if (responseBytes == 2)
        {
            txData.canMsg.Data[2] = txByte[1];
            txData.canMsg.Data[3] = 0x00;
            txData.canMsg.Data[4] = 0x00;
            txData.canMsg.Data[5] = 0x00;
            txData.canMsg.Data[6] = 0x00;
            txData.canMsg.Data[7] = 0x00;
        }
        else if (responseBytes == 3)
        {
            txData.canMsg.Data[2] = txByte[1];
            txData.canMsg.Data[3] = txByte[2];
            txData.canMsg.Data[4] = 0x00;
            txData.canMsg.Data[5] = 0x00;
            txData.canMsg.Data[6] = 0x00;
            txData.canMsg.Data[7] = 0x00;
        }
        else if (responseBytes == 4)
        {
            txData.canMsg.Data[2] = txByte[1];
            txData.canMsg.Data[3] = txByte[2];
            txData.canMsg.Data[4] = txByte[3];
            txData.canMsg.Data[5] = 0x00;
            txData.canMsg.Data[6] = 0x00;
            txData.canMsg.Data[7] = 0x00;
        }
        else if (responseBytes == 5)
        {
            txData.canMsg.Data[2] = txByte[1];
            txData.canMsg.Data[3] = txByte[2];
            txData.canMsg.Data[4] = txByte[3];
            txData.canMsg.Data[5] = txByte[4];
            txData.canMsg.Data[6] = 0x00;
            txData.canMsg.Data[7] = 0x00;
        }
        else if (responseBytes == 6)
        {
            txData.canMsg.Data[2] = txByte[1];
            txData.canMsg.Data[3] = txByte[2];
            txData.canMsg.Data[4] = txByte[3];
            txData.canMsg.Data[5] = txByte[4];
            txData.canMsg.Data[6] = txByte[5];
            txData.canMsg.Data[7] = 0x00;
        }
        else if (responseBytes == 7)
        {
            txData.canMsg.Data[2] = txByte[1];
            txData.canMsg.Data[3] = txByte[2];
            txData.canMsg.Data[4] = txByte[3];
            txData.canMsg.Data[5] = txByte[4];
            txData.canMsg.Data[6] = txByte[5];
            txData.canMsg.Data[7] = txByte[6];
        }


    }
    else if (negative == 1)
    {
        flowControlResponse = 0;
        txData.sendUDS = 1;
        txData.canMsg.Data[0] = responseBytes;
        txData.canMsg.Data[1] = 0x7f;
        txData.canMsg.Data[2] = txByte[1];
        txData.canMsg.Data[3] = txByte[2];
        txData.canMsg.Data[4] = 0x00;
        txData.canMsg.Data[5] = 0x00;
        txData.canMsg.Data[6] = 0x00;
        txData.canMsg.Data[7] = 0x00;
    }
    else if ((pCI == 3) && (flowControlResponse == 0))
    {
        txData.sendUDS = 1;
        flowControlResponse ++;
        txData.canMsg.Data[0] = responseBytes;
        txData.canMsg.Data[1] = 0x7f;
        txData.canMsg.Data[2] = txByte[1];
        txData.canMsg.Data[3] = txByte[2];
        txData.canMsg.Data[4] = 0x00;
        txData.canMsg.Data[5] = 0x00;
        txData.canMsg.Data[6] = 0x00;
        txData.canMsg.Data[7] = 0x00;
    }
    else
    {
        txData.sendUDS = 0;

        /* do nothing */

    }

    return txData;
}

void jumpToBootloader(unsigned int value)
{
        jumptobootvalue = value;
}

void bmsUpdateMode(unsigned int value)
{
        bmsUpdatevalue = value;
}

