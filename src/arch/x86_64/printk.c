#include <stdarg.h>
#include <vga.h>

#define MAX_INT_STR 11
#define MAX_HEX_STR 8

// %% %d %u %x %c %p %h[dux] %l[dux] %q[dux] %s
void print_decimal(int i)
{
    int negative = 0, index = MAX_INT_STR - 2;
    char str[MAX_INT_STR] = { 0 };

    if (i < 0)
    {
        negative = 1;
        i *= -1;
    }

    for (; i; i /= 10)
        str[index--] = (i % 10) + '0';

    if (negative) str[index--] = '-';

    VGA_display_str(&str[index+1]);
}

void print_unsigned_decimal(unsigned int i)
{
    int index = MAX_INT_STR - 2;
    char str[MAX_INT_STR] = { 0 };

    for (; i; i /= 10)
        str[index--] = (i % 10) + '0';

    VGA_display_str(&str[index+1]);
}

void print_unsigned_hex(unsigned int i)
{
    const char hex_lookup[] = "0123456789abcdef";
    char str[MAX_HEX_STR + 2] = { 0 };
    int n, len = 0;

    if (!i)
        len = 1;
    else
    {
        for (n = i; n; n >>= 4)
            len++;
    }

    str[len] = '\0';

    for (--len, n = i; len >= 0; n >>=4, --len)
        str[len] = hex_lookup[n & 0xf];

    VGA_display_str(str);
}

void print_char(char c)
{
    VGA_display_char(c);
}

void print_pointer(void *ptr)
{

}

void print_str(const char *str)
{

}

void print_uchar(unsigned char c)
{

}

void print_short(short s)
{

}

void print_long_hex(long l)
{

}

void printk(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    int d;
    unsigned int ux;
    char c;
    // h?
    // l?
    // q is ll
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
                    print_decimal(va_arg(args, int));
                    break;
                case 'u':
                    print_unsigned_decimal(va_arg(args, unsigned int));
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
                    // TODO
                    break;
                case 'l':
                    // TODO
                    break;
                case 'q':
                    // TODO
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
    VGA_display_char('\n');
}