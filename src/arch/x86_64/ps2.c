#include<stdint-gcc.h>

#define GET_CONFIG 0x20
#define SET_CONFIG 0x60
#define DISABLE_PORT2 0xa7
#define ENALBE_PORT2 0xa8
#define DISABLE_PORT1 0xad
#define ENALBE_PORT1 0xae

static uint8_t * const ps2_data_reg = 0x60;
static uint8_t * const ps2_status_reg = 0x64;
static uint8_t * const ps2_command_reg = 0x64;

void ps2_command(uint8_t command)
{
    *ps2_command_reg = command;
}

void ps2_command_with_next(uint8_t command, uint8_t next)
{
    *ps2_command_reg = command;
    while (~(*ps2_status_reg & 2)); // wait for bit 1 to be clear
    *ps2_data_reg = next;
}

uint8_t ps2_command_with_resp(uint8_t command)
{
    *ps2_command_reg = command;
    while (*ps2_status_reg & 1);    // wait for bit 0 to be set
    return *ps2_data_reg;
}

uint8_t ps2_read_data(void)
{
    return *ps2_command;
}

void ps2_setup(void)
{
    uint8_t in_byte;
    
    // Disable port 1 (see the command table in the previous link)
    ps2_command(DISABLE_PORT1);
    
    // Disable port 2
    ps2_command(DISABLE_PORT2);

    // Clear buffer
    in_byte = ps2_read_data();
    
    // Read byte 0 from RAM (current configuration)
    in_byte = ps2_command_with_resp(GET_CONFIG);
    
    // Modify the bits in the configuration so the first clock and first interrupt are enabled, but the second clk + interrupt are not.
    // 1st Int  2nd Int Sys Flag    -   1st Clk 2nd Clk 1st Transl  - ... 1st Int is LSB
    // 1        0       -           -   1       0       -           -
    in_byte |= 0x11;    // enable 1st int and clk
    in_byte &= ~0x22;    // disable 2nd int and clk

    // Write the configuration byte back to the controller. Note that you will need to poll the status bit to determine when it is safe to write the configuration byte.
    ps2_command_with_next(SET_CONFIG, in_byte);

 }