#include <stdarg.h>
#include <vga.h>

#define MAX_INT_STR 10
#define MAX_LONG_INT_STR 20
#define MAX_SHORT_INT_STR 5
#define MAX_HEX_STR 8
#define MAX_LONG_HEX_STR 16
#define MAX_SHORT_HEX_STR 4

// %% %d %u %x %c %p %h[dux] %l[dux] %q[dux] %s
void print_int(int i)
{
    int negative = 0, index = MAX_INT_STR - 2;
    char str[MAX_INT_STR + 1] = { 0 };

    if (i < 0)
    {
        negative = 1;
        i *= -1;
    }
    else if (!i)
        str[index--] = '0';

    for (; i; i /= 10)
        str[index--] = (i % 10) + '0';

    if (negative) str[index--] = '-';

    VGA_display_str(&str[index+1]);
}

void print_long_int(long int i)
{
    int negative = 0, index = MAX_LONG_INT_STR - 2;
    char str[MAX_LONG_INT_STR + 1] = { 0 };

    if (i < 0)
    {
        negative = 1;
        i *= -1;
    }
    else if (!i)
        str[index--] = '0';

    for (; i; i /= 10)
        str[index--] = (i % 10) + '0';

    if (negative) str[index--] = '-';

    VGA_display_str(&str[index+1]);
}

void print_short_int(short int i)
{
    int negative = 0, index = MAX_SHORT_INT_STR - 2;
    char str[MAX_SHORT_INT_STR + 1] = { 0 };

    if (i < 0)
    {
        negative = 1;
        i *= -1;
    }
    else if (!i)
        str[index--] = '0';

    for (; i; i /= 10)
        str[index--] = (i % 10) + '0';

    if (negative) str[index--] = '-';

    VGA_display_str(&str[index+1]);
}

void print_long_long_int(long long int i)
{
    int negative = 0, index = MAX_LONG_INT_STR - 2;
    char str[MAX_LONG_INT_STR + 1] = { 0 };

    if (i < 0)
    {
        negative = 1;
        i *= -1;
    }
    else if (!i)
        str[index--] = '0';

    for (; i; i /= 10)
        str[index--] = (i % 10) + '0';

    if (negative) str[index--] = '-';

    VGA_display_str(&str[index+1]);
}

void print_unsigned_int(unsigned int i)
{
    int index = MAX_INT_STR - 2;
    char str[MAX_INT_STR] = { 0 };

    if (!i)
        str[index--] = '0';

    for (; i; i /= 10)
        str[index--] = (i % 10) + '0';

    VGA_display_str(&str[index+1]);
}

void print_long_unsigned_int(long unsigned int i)
{
    int index = MAX_LONG_INT_STR - 2;
    char str[MAX_LONG_INT_STR] = { 0 };

    if (!i)
        str[index--] = '0';

    for (; i; i /= 10)
        str[index--] = (i % 10) + '0';

    VGA_display_str(&str[index+1]);
}

void print_short_unsigned_int(short unsigned int i)
{
    int index = MAX_SHORT_INT_STR - 2;
    char str[MAX_SHORT_INT_STR] = { 0 };

    if (!i)
        str[index--] = '0';

    for (; i; i /= 10)
        str[index--] = (i % 10) + '0';

    VGA_display_str(&str[index+1]);
}

void print_long_long_unsigned_int(long long unsigned int i)
{
    int index = MAX_LONG_INT_STR - 2;
    char str[MAX_LONG_INT_STR] = { 0 };

    if (!i)
        str[index--] = '0';

    for (; i; i /= 10)
        str[index--] = (i % 10) + '0';

    VGA_display_str(&str[index+1]);
}

void print_unsigned_hex(unsigned int i)
{
    const char hex_lookup[] = "0123456789abcdef";
    char str[MAX_HEX_STR] = { 0 };
    unsigned int n;
    int len = 0;

    if (!i)
        len = 1;
    else
    {
        for (n = i; n; n >>= 4)
            len++;
    }

    str[len] = '\0';

    for (--len; len >= 0; i>>=4, --len)
        str[len] = hex_lookup[i & 0xf];

    VGA_display_str(str);
}

void print_long_unsigned_hex(long unsigned int i)
{
    const char hex_lookup[] = "0123456789abcdef";
    char str[MAX_LONG_HEX_STR] = { 0 };
    long unsigned int n;
    int len = 0;

    if (!i)
        len = 1;
    else
    {
        for (n = i; n; n >>= 4)
            len++;
    }

    str[len] = '\0';

    for (--len; len >= 0; i>>=4, --len)
        str[len] = hex_lookup[i & 0xf];

    VGA_display_str(str);
}

void print_short_unsigned_hex(short unsigned int i)
{
    const char hex_lookup[] = "0123456789abcdef";
    char str[MAX_SHORT_HEX_STR] = { 0 };
    short unsigned int n;
    int len = 0;

    if (!i)
        len = 1;
    else
    {
        for (n = i; n; n >>= 4)
            len++;
    }

    str[len] = '\0';

    for (--len; len >= 0; i>>=4, --len)
        str[len] = hex_lookup[i & 0xf];

    VGA_display_str(str);
}

void print_long_long_unsigned_hex(long long unsigned int i)
{
    const char hex_lookup[] = "0123456789abcdef";
    char str[MAX_LONG_HEX_STR] = { 0 };
    long long unsigned int n;
    int len = 0;

    if (!i)
        len = 1;
    else
    {
        for (n = i; n; n >>= 4)
            len++;
    }

    str[len] = '\0';

    for (--len; len >= 0; i>>=4, --len)
        str[len] = hex_lookup[i & 0xf];

    VGA_display_str(str);
}

void print_char(char c)
{
    VGA_display_char(c);
}

void print_pointer(void *ptr)
{
    VGA_display_char('0');
    VGA_display_char('x');
    print_long_unsigned_hex((long unsigned int)ptr);
}

void print_str(const char *str)
{
    VGA_display_str(str);
}

void printk(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char * str;

    while (*fmt != '\0')
    {
        if (*fmt == '%')
        {
            fmt++;
            switch (*fmt)
            {
            case '%':
                VGA_display_char('%');
                break;
            case 'd':
                print_int(va_arg(args, int));
                break;
            case 'u':
                print_unsigned_int(va_arg(args, unsigned int));
                break;
            case 'x':
                print_unsigned_hex(va_arg(args, unsigned int));
                break;
            case 'c':
                print_char(va_arg(args, int));
                break;
            case 'p':
                print_pointer(va_arg(args, void *));
                break;
            case 'h':
                fmt++;
                switch (*fmt)
                {
                case 'd':
                    print_short_int(va_arg(args, int));
                    break;
                case 'u':
                    print_short_unsigned_int(va_arg(args, unsigned int));
                    break;
                case 'x':
                    print_short_unsigned_hex(va_arg(args, unsigned int));
                    break;
                default:
                    break;
                }
                break;
            case 'l':
                fmt++;
                switch (*fmt)
                {
                case 'd':
                    print_long_int(va_arg(args, long int));
                    break;
                case 'u':
                    print_long_unsigned_int(va_arg(args, long unsigned int));
                    break;
                case 'x':
                    print_long_unsigned_hex(va_arg(args, long unsigned int));
                    break;
                default:
                    break;
                }
                break;
            case 'q':
                fmt++;
                switch (*fmt)
                {
                case 'd':
                    print_long_long_int(va_arg(args, long long int));
                    break;
                case 'u':
                    print_long_long_unsigned_int(va_arg(args, long long unsigned int));
                    break;
                case 'x':
                    print_long_long_unsigned_hex(va_arg(args, long long unsigned int));
                    break;
                default:
                    break;
                }
                break;
            case 's':
                print_str(va_arg(args, char *));
                break;
            default:
                break;
            }
        }
        else
            VGA_display_char(*fmt);
        fmt++;
    }
    va_end(args);
}