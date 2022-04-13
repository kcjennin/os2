#ifndef PS2_H
#define PS2_H

#include<stdint-gcc.h>

typedef struct __attribute__((packed)) OutPort
{
    uint8_t sys_reset       : 1;
    uint8_t a20_gate        : 1;
    uint8_t second_clock    : 1;
    uint8_t second_data     : 1;
    uint8_t has_first_data  : 1;
    uint8_t has_second_data : 1;
    uint8_t first_clock     : 1;
    uint8_t first_data      : 1;
} OutPort;

void ps2_command(uint8_t command);
void ps2_command_with_next(uint8_t command, uint8_t next);
uint8_t ps2_command_with_resp(uint8_t command);
uint8_t ps2_read_data(void);
uint8_t ps2_write_data(uint8_t data);
void ps2_setup(void);

#endif