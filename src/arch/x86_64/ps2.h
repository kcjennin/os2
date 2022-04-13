#ifndef PS2_H
#define PS2_H

#include<stdint-gcc.h>

void ps2_command(uint8_t command);
void ps2_command_with_next(uint8_t command, uint8_t next);
uint8_t ps2_command_with_resp(uint8_t command);
uint8_t ps2_read_data(void);
void ps2_setup(void);

#endif