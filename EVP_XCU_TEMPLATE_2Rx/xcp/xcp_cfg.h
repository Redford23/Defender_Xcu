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

#if !defined(__XCP_CFG_H__)
#define __XCP_CFG_H__
#include <stdint.h>

/* define here configuration parameters for customizing XcpBasic driver */

#define XCP_ENABLE_DAQ
//#define XCP_DISABLE_DAQ_PRESCALER
//#define XCP_DISABLE_DAQ_OVERRUN_INDICATION
//#define XCP_DISABLE_DAQ_HDR_ODT_DAQ1
//#define XCP_DISABLE_DAQ_PROCESSOR_INFO
//#define XCP_DISABLE_DAQ_RESOLUTION_INFO
//#define XCP_DISABLE_DAQ_EVENT_INFO
//#define XCP_DISABLE_DAQ_TIMESTAMP
//#define XCP_DISABLE_DAQ_TIMESTAMP_FIXED
//#define XCP_DISABLE_SEED_KEY
//#define XCP_DISABLE_CHECKSUM
//#define XCP_DISABLE_PARAMETER_CHECK
#define XCP_ENABLE_SEND_QUEUE
//#define XCP_DISABLE_SEND_EVENT
//#define XCP_DISABLE_USER_COMMAND
//#define XCP_DISABLE_COMM_MODE_INFO
//#define XCP_DISABLE_CALIBRATION_PAGE
//#define XCP_DISABLE_PAGE_INFO
//#define XCP_DISABLE_PAGE_FREEZE
//#define XCP_DISABLE_PAGE_COPY
//#define XCP_DISABLE_DPRAM




#define vuint8 uint8_t
#define vuint16 uint16_t
#define vuint32 uint32_t


#define C_CPUTYPE_BIGENDIAN
#define XCP_DISABLE_DAQ_EVENT_INFO


#endif /* __XCP_CFG_H__ */
