#include <vga.h>
#include <string.h>

void kmain(void)
{
    int i,j=0;

    VGA_clear();
    for (i = 0; i < 107; i++)
        VGA_display_str("Hello, World!! ");
    
    while (1) asm("hlt");
}