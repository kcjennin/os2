#include<stdint-gcc.h>

// Commands
#define GET_CONFIG 0x20
#define SET_CONFIG 0x60
#define DISABLE_PORT2 0xa7
#define ENABLE_PORT2 0xa8
#define TEST_PORT2 0xa9
#define TEST_CONTR 0xaa
#define TEST_PORT1 0xab
#define DISABLE_PORT1 0xad
#define ENABLE_PORT1 0xae
#define SEND_PORT1 0xd1
#define SEND_PORT2 0xd4

typedef struct __attribute__((packed)) StatusReg
{
    uint8_t out_status      : 1;
    uint8_t in_status       : 1;
    uint8_t sys_flag        : 1;
    uint8_t command_data    : 1;
    uint8_t                 : 1;
    uint8_t                 : 1;
    uint8_t timeout_error   : 1;
    uint8_t parity_error    : 1;
} StatusReg;

typedef struct __attribute__((packed)) ConfigByte
{
    uint8_t first_int       : 1;
    uint8_t second_int      : 1;
    uint8_t sys_flag        : 1;
    uint8_t                 : 1;
    uint8_t first_clock     : 1;
    uint8_t second_clock    : 1;
    uint8_t first_transl    : 1;
    uint8_t                 : 1;
} ConfigByte;

static volatile uint8_t * const ps2_data_reg = 0x60;
static volatile StatusReg * const ps2_status_reg = 0x64;
static volatile uint8_t * const ps2_command_reg = 0x64;

void wait_input_ready()
{
    while (ps2_status_reg->in_status != 0);
}

void wait_output_ready()
{
    while (ps2_status_reg->out_status != 1);
}

void ps2_command(uint8_t command)
{
    wait_input_ready();
    *ps2_command_reg = command;
}

void ps2_command_with_next(uint8_t command, uint8_t next)
{
    wait_input_ready();
    *ps2_command_reg = command;
    wait_input_ready();
    *ps2_data_reg = next;
}

uint8_t ps2_command_with_resp(uint8_t command)
{
    wait_input_ready();
    *ps2_command_reg = command;
    wait_output_ready();
    return *ps2_data_reg;
}

uint8_t ps2_send_port1(uint8_t data)
{
    wait_input_ready();
    *ps2_data_reg = data;
}

uint8_t ps2_send_port2(uint8_t command)
{
}

int ps2_setup(void)
{
    union Storage
    {
        uint8_t in_byte;
        ConfigByte config_byte;
    } storage, storage2;
    int two_channel = 1;
    int ports[2] = { 0 };
    
    // Disable devices
    ps2_command(DISABLE_PORT1);
    ps2_command(DISABLE_PORT2);

    // Clear buffer by reading from it
    storage.in_byte = *ps2_data_reg;
    
    // Read byte 0 from RAM (current configuration)
    storage.in_byte = ps2_command_with_resp(GET_CONFIG);
    
    // Set the config byte
    storage.config_byte.first_int = 0;
    storage.config_byte.second_int = 0;
    storage.config_byte.first_transl = 0;
    storage2.in_byte = storage.in_byte;
    ps2_command_with_next(SET_CONFIG, storage.in_byte);

    // Save the two channel status
    if (!storage2.config_byte.sys_flag)
        two_channel = 0;

    // Test the controller
    storage.in_byte = ps2_command_with_resp(TEST_CONTR);

    if (storage.in_byte == 0xfc)
    {
        printk("Controller test failed");
        return -1;
    }
    else if (storage.in_byte != 0x55)
    {
        printk("Controller test error: 0x%x", storage.in_byte);
        return -1;
    }

    ps2_command_with_next(SET_CONFIG, storage2.in_byte);

    // Check for two channels
    if (two_channel)
    {
        ps2_command(ENABLE_PORT2);
        storage.in_byte = ps2_command_with_resp(GET_CONFIG);

        if (storage.config_byte.sys_flag == 1)
            two_channel = 0;
        else
            ps2_command(DISABLE_PORT2);
    }

    // Interface tests
    storage.in_byte = ps2_command_with_resp(TEST_PORT1);
    if (storage.in_byte)
    {
        switch (storage.in_byte)
        {
        case 0x01:
            printk("Clock stuck low port 1\n");
            break;
        case 0x02:
            printk("Clock stuck high port 1\n");
            break;
        case 0x03:
            printk("Data line low port 1\n");
            break;
        case 0x04:
            printk("Data line high port 1\n");
            break;
        default:
            printk("Unknown port 1 test result\n");
            break;
        }
    }
    else
        ports[0] = 1;

    storage.in_byte = ps2_command_with_resp(TEST_PORT2);
    if (storage.in_byte)
    {
        switch (storage.in_byte)
        {
        case 0x01:
            printk("Clock stuck low port 2\n");
            break;
        case 0x02:
            printk("Clock stuck high port 2\n");
            break;
        case 0x03:
            printk("Data line low port 2\n");
            break;
        case 0x04:
            printk("Data line high port 2\n");
            break;
        default:
            printk("Unknown port 2 test result\n");
            break;
        }
    }
    else
        ports[1] = 1;
    
    if (!(ports[0]) && !(ports[1]))
    {
        printk("No working PS/2 ports\n");
        return -1;
    }

    // Enable ports (but just 1 for now)
    if (ports[0])
    {
        storage2.config_byte.first_clock = 1;
        storage2.config_byte.first_int = 1;
        storage2.config_byte.second_clock = 0;
        storage2.config_byte.second_int = 0;
        ps2_command_with_next(SET_CONFIG, storage2.in_byte);
        ps2_command(ENABLE_PORT1);
    }
    else
    {
        printk("Port 1 is not working\n");
        return -1;
    }

    // Reseting device(s)
    // STARTING HERE

 }