#include <vga.h>
#include <string.h>

#define VGA_BASE 0xb8000

// VGA Color definitions
#define VGA_BLACK           0
#define VGA_BLUE            1
#define VGA_GREEN           2
#define VGA_CYAN            3
#define VGA_RED             4
#define VGA_MAGENTA         5
#define VGA_BROWN           6
#define VGA_WHITE           7
#define VGA_GRAY            8
#define VGA_LIGHT_BLUE      9
#define VGA_LIGHT_GREEN     10
#define VGA_LIGHT_CYAN      11
#define VGA_LIGHT_RED       12
#define VGA_LIGHT_MAGENTA   13
#define VGA_YELLOW          14
#define VGA_BRIGHT_WHITE    15

// Macros for whether a color is foreground or background
#define FG(color) (color)
#define BG(color) ((color << 4) & 0xF0)

// Macro for getting the line of the cursor
#define LINE(cursor) ((cursor / 80))

static unsigned short *vgaBuff = (unsigned short *)VGA_BASE;
static unsigned int width = 80;
static unsigned int height = 20;
static unsigned int cursor = 0;
static unsigned char color = FG(VGA_GRAY) | BG(VGA_BLACK);

static void scroll(void)
{
    memcpy(vgaBuff, vgaBuff+width, width*(height-1));
    memset(vgaBuff[width * (height - 1)], 0, width);
    cursor -= width * height;
}

void VGA_clear(void)
{
    memset(vgaBuff, 0, width*height);
    cursor = 0;
}

void VGA_display_char(char c)
{
    if (c == '\n')
    {
        cursor = (LINE(cursor) + 1) * width;
        if (cursor >= width * height)
            scroll();
    }
    else if (c == '\r')
        cursor = LINE(cursor);
    else
    {
        vgaBuff[cursor] = (color << 8) | c;
        if ( (cursor % width) < (width - 1) )
            cursor++;
        else if ( (cursor % width) == (width - 1))
            cursor = (LINE(cursor) + 1) * width;
    }
}

void VGA_display_str(const char * str)
{
    memcpy(&vgaBuff[cursor], str, strlen(str));
}