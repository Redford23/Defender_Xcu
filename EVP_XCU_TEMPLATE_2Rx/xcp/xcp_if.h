//----------------------------------------------------------------------------
/*****************************************************************************
| Project Name:   XCP V1.0 - Driver
|    File Name:   xcp_if.h
|
|  Description:
|   XCP driver custom module
|   This module provides the adaption to a particular platform
|   It contains all platform specific functions
|
|***************************************************************************/
#if defined ( __XCP_IF_H__ )
#else
#define __XCP_IF_H__

#include "can_input_simulink.h"
#include "xcp/XcpBasic.h"
#include <stdbool.h>

#define XCP_CAN_RX_MESSAGE_BOX 32
#define XCP_CAN_SLAVE_ID 0x1001
#define XCP_CAN_MASTER_ID 0x1002
#define XCP_CAN_ID_EXTD 1


//void ApplXcpSend( vuint8 len, MEMORY_ROM BYTEPTR msg );
//
//vuint8 ApplXcpSendStall( void );
//


//----------------------------------------------------------------------------
// XcpHandler
// Cyclic XCP task to handle incoming commands and their responses

// TODO : This needs to be able to run faster than the 20ms loop too.
void XcpRxHandler( void );

void XcpTxHandler( void );

//------------------------------------------------------------------------------
// Platform dependent functions

// Convert a XCP address to a pointer
MTABYTEPTR ApplXcpGetPointer( vuint8 addr_ext, vuint32 addr );



#endif

