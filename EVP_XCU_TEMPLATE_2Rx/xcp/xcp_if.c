//----------------------------------------------------------------------------
/*****************************************************************************
| Project Name:   XCP V1.0 - Driver
|    File Name:   xcp_if.c
|
|  Description:
|   XCP driver custom module
|   This module provides the adaption to a particular platform
|   It contains all platform specific functions
|
|***************************************************************************/

#include "xcp/xcp_if.h"

//----------------------------------------------------------------------------
// Transport Layer

// TODO : I think that this will be called multiple times per simulation loop, so we need a way to send messages immediately and to check the transmission success of messages
void ApplXcpSend( vuint8 len, MEMORY_ROM BYTEPTR msg ) { 
      CAN_MESSAGE_BUS can_msg = {.ID=XCP_CAN_SLAVE_ID, .Length=len, .Extended=XCP_CAN_ID_EXTD};
    uint8_t i;
    for (i = 0; i < len; i++){
        can_msg.Data[i] = msg[i];
    }
//    dcan2Messagebox1Transmit (can_msg, 1, 0, XCP_CAN_MESSAGE_BOX);
    xcpMessageboxTransmit(can_msg);
}

vuint8 ApplXcpSendStall( void ) {

// while (!0);
 XcpSendCallBack();
 return 1;
}



//----------------------------------------------------------------------------
// XcpHandler
// Cyclic XCP task to handle incoming commands and their responses

// TODO : This needs to be able to run faster than the 20ms loop too.
void XcpRxHandler( void ) {
  CAN_MESSAGE_BUS can_msg;
  static double timestamp = 0;
  can_msg = dcan3MessageboxRead(XCP_CAN_RX_MESSAGE_BOX, XCP_CAN_MASTER_ID, 0x7FFFFFFF, 8);
  if (can_msg.Timestamp > timestamp){
      XcpCommand((MEMORY_CONST vuint32*)&can_msg.Data[0]);
  } 
  timestamp = can_msg.Timestamp;
}

void XcpTxHandler( void ) {
  XcpSendCallBack();
}


//------------------------------------------------------------------------------
// Platform dependent functions

// Convert a XCP address to a pointer
MTABYTEPTR ApplXcpGetPointer( vuint8 addr_ext, vuint32 addr ) {
  return (MTABYTEPTR)addr;
}



//void ApplXcpStartDaq( void ) {
//
//  #if defined(VX1000_STIM_BENCHMARK)
//    gVX1000.Stim.TimeoutCtr = 0;
//    gVX1000.Stim.TimeoutCtr2 = 0;
//    vx1000_StimBenchmarkInit();
//  #endif /* VX1000_STIM_BENCHMARK */
//}


//------------------------------------------------------------------------------
// Bypass

// Special implementation which reuses the VX1000 bypass benchmarking code

#ifdef XCP_ENABLE_STIM

vuint8 XcpBypass( vuint8 daq_event, vuint8 stim_event, vuint32 timeout_us ) {

  vuint8 status,timeout;
  vuint32 t1;

  #if defined(VX1000_STIM_BENCHMARK)
    vx1000_StimBenchmarkStimBegin(EVENT_BYPASS_0);
  #endif /* VX1000_STIM_BENCHMARK */

  /* Data acquisition for bypass */
  /* Busy wait for stimulation data if data acquisition is active */
  XcpStimEventStatus(stim_event, STIM_RESET_ODT_BUFFER);
  status = XcpEvent(daq_event);
  timeout = 0;
  if (status&XCP_EVENT_DAQ) { // DAQ event active
    t1 = VX1000_CLOCK();
    while (!XcpStimEventStatus(stim_event, STIM_CHECK_ODT_BUFFER)) { // Wait while STIM is active for EVENT_BYPASS_0 and STIM data is not complete
      XcpTxHandler(); // Handle XCP on CAN transmisssion of pending messages
      XcpRxHandler(); // Handle XCP on CAN RX
      if ((VX1000_CLOCK()-t1)>(timeout_us*VX1000_CLOCK_TICKS_PER_US)) {
        timeout = 1;
        break;
      }
    }
  }

  /* Data stimulation for bypass */
  status = XcpEvent(stim_event);

  #if defined(VX1000_STIM_BENCHMARK)
    vx1000_StimBenchmarkStimEnd(EVENT_BYPASS_0,timeout);
  #endif /* VX1000_STIM_BENCHMARK */

  // Execute the original code if stimulation is not active
  // Do nothing if timeout
  if (((status&(XCP_EVENT_STIM|XCP_EVENT_STIM_OVERRUN)))!=XCP_EVENT_STIM) {
      // Stimulation not done
      if (timeout) {
        gVX1000.Stim.TimeoutCtr++;
        gVX1000.Stim.TimeoutCtr2++;
        return 2; // Bypass timeout
     } else {
       return 0; // Bypass inactive
     }
  }
  else {
    // Stimulation done
    gVX1000.Stim.TimeoutCtr2 = 0; /* Clear the timeout burst counter */
    return 1; // Bypass done
  }

}

#endif

