#include <stdint-gcc.h>
#include "ps2.h"
#include "printk.h"

#define TEST_PASSED     0xaa
#define SET_SCAN_SET    0xf0
#define ENABLE          0xf4
#define ACK             0xfa
#define TEST_FAILED1    0xfc
#define TEST_FAILED2    0xfd
#define RESEND          0xfe
#define RESET_AND_TEST  0xff

#define SCAN_SET1       0x01

int keyboard_reset()
{
    uint8_t ret_val;

    ps2_write_data(RESET_AND_TEST);
    
    while ((ret_val = ps2_read_data()) != TEST_PASSED)
    {
        if (ret_val == TEST_FAILED1 || ret_val == TEST_FAILED2)
            return -1;
        else if (ret_val != RESEND)
        {
            printk("Unexpected return code in reset: 0x%x", ret_val);
            return -1;
        }
    }
    return ret_val;
}

int keyboard_command(uint8_t command)
{
    uint8_t ret_val;

    ps2_write_data(command);

    while ((ret_val = ps2_read_data()) != ACK) 
    {
        if (ret_val != RESEND)
        {
            printk("Unexpected return code: 0x%x", ret_val);
            return -1;
        }
    }
}

int keyboard_command_with_data(uint8_t command, uint8_t data)
{
    ps2_write_data(command);
    return keyboard_command(data);
}

void keyboard_setup(void)
{
    uint8_t in_byte;
    
    // Try to reset the keyboard
    keyboard_reset();

    // Set the keyboard to a known scan code.
    keyboard_command_with_data(SET_SCAN_SET, SCAN_SET1);

    // Enable the keyboard.
    keyboard_command(ENABLE);
}