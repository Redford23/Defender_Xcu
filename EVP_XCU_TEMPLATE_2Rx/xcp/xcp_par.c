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
#include "xcpBasic.h"

// Slave device id
#if defined ( kXcpStationIdLength )
  V_MEMROM0 MEMORY_ROM vuint8 kXcpStationId[kXcpStationIdLength] = kXcpStationIdString;
#endif

#ifdef XCP_ENABLE_DAQ_EVENT_INFO
V_MEMROM0 static vuint8 MEMORY_ROM kXcpEventName_0[] = "20ms";
V_MEMROM0 static vuint8 MEMORY_ROM kXcpEventName_1[] = "100ms DAQ";
V_MEMROM0 static vuint8 MEMORY_ROM kXcpEventName_2[] = "100ms STIM";
V_MEMROM0 MEMORY_ROM vuint8* MEMORY_ROM kXcpEventName[] =
{
 &kXcpEventName_0[0],
 &kXcpEventName_1[0],
 &kXcpEventName_2[0]
};
V_MEMROM0 vuint8 MEMORY_ROM kXcpEventNameLength[] =
{
 4,
 9,
 10
};
V_MEMROM0 vuint8 MEMORY_ROM kXcpEventCycle[] =
{
 10,
 100,
 100
};
V_MEMROM0 vuint8 MEMORY_ROM kXcpEventDirection[] =
{
 kXcpEventDirectionDaq
};
#endif
/* implement here parameters for customizing XcpBasic driver (e.g. kXcpStationId) */


