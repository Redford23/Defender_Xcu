/*----------------------------------------------------------------------------
| Project: XCP_Delivery
|
|  Description:   Implementation of the XCP Protocol Layer
|                 XCP V1.0 slave device driver
|                 Basic Version
|
|-----------------------------------------------------------------------------
| Copyright (c) by Vector Informatik GmbH.  All rights reserved.
----------------------------------------------------------------------------*/
#if defined ( __XCP_PAR_H__ )
#else
#define __XCP_PAR_H__

#include "xcp_def.h"

/* declare here parameters for customizing XcpBasic driver (e.g. kXcpStationId) */
#define kXcpStationIdLength 3
#define kXcpStationIdString "BCU"

extern const vuint8 kXcpStationId[];

V_MEMROM0 extern vuint8 MEMORY_ROM kXcpStationId[];

#define kXcpMaxEvent 8

V_MEMROM0 extern vuint8 MEMORY_ROM kXcpEventName_0[];
V_MEMROM0 extern vuint8 MEMORY_ROM kXcpEventName_1[];
V_MEMROM0 extern vuint8 MEMORY_ROM kXcpEventName_2[];


#endif
