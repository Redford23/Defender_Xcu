#pragma once

#include <stdint.h>
#include <stdbool.h>

/*
    FLASH0  (RX) : origin=(0x00018040) length= (0x0013FFE0 - 0x00018020) // was 0x0011ffe0 in the first bootloader release
    STACKS  (RW) : origin=0x08000000 length=0x00000800
    KRAM    (RW) : origin=0x08000800 length=0x00000800
    RAM     (RW) : origin=(0x08000800+0x00000800) length=(0x0002f800 - 0x00000800)
    */

#define FLASH_ORIGIN 0x00018040
#define FLASH_LENGTH 0x0013FFE0 - 0x00018020
#define RAM_ORIGIN   0x08000800 + 0x00000800
#define RAM_LENGTH   0x0002f800 - 0x00000800

#define ADDRESS_VALID_FLASH(addr) \
    ((addr >= FLASH_ORIGIN) && ( addr <  (FLASH_ORIGIN + FLASH_LENGTH)))

#define ADDRESS_VALID_RAM(addr) \
    ((addr >= RAM_ORIGIN) && ( addr <  (RAM_ORIGIN + RAM_LENGTH)))

#define ADDRESS_VALID(addr) \
    (ADDRESS_VALID_FLASH(addr) || ADDRESS_VALID_RAM(addr))

bool read_from_address(uint32_t addr, uint8_t * buf, uint16_t buf_len);

