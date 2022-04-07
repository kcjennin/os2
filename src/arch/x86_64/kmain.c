#include <vga.h>
#include <string.h>
#include <printk.h>

void kmain(void)
{
    int i, j=0;
    // while(!j);

    VGA_clear();
    printk("Hi! %c\n", 48);

    while (1) asm("hlt");
}