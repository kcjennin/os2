#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint-gcc.h>

int keyboard_reset();
int keyboard_command(uint8_t command);
int keyboard_command_with_data(uint8_t command, uint8_t data);
void keyboard_setup(void);

#endif