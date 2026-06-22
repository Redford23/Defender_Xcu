#include "mem_access.h"

bool read_from_address(uint32_t addr, uint8_t * buf, uint16_t buf_len){
    uint16_t i;
    if (ADDRESS_VALID(addr) & ADDRESS_VALID(addr + buf_len-1)){
        for (i = 0; i < buf_len; i++){
            buf[i] = *(uint8_t*)(addr+i);
        }
        return true;
    } else {
        return false;
    }
}
