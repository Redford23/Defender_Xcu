#ifndef RTW_HEADER_XCU_UDSonly_cap_host_h__
#define RTW_HEADER_XCU_UDSonly_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

typedef struct {
  rtwCAPI_ModelMappingInfo mmi;
} XCU_UDSonly_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C"
{

#endif

  void XCU_UDSonly_host_InitializeDataMapInfo(XCU_UDSonly_host_DataMapInfo_T
    *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif                                 /* RTW_HEADER_XCU_UDSonly_cap_host_h__ */

/* EOF: XCU_UDSonly_capi_host.h */
