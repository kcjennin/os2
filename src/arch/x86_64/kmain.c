#include <vga.h>
#include <string.h>
#include <printk.h>

void kmain(void)
{
    int i, j=0;
    // while(!j);

    VGA_clear();
    // normals
    // printk("string: %s\n", "Hello, World!");
    // printk("d: %d\n", 0);
    // printk("u: %u\n", 0);
    // printk("x: 0x%x\n", 0);
    // printk("c: %c\n", '\0');

    // longs
    // printk("ld: %ld\n", -10000000L);
    // printk("lu: %lu\n", 10000000L);
    // printk("lx: 0x%lx\n", -1L);

    // shorts
    // printk("hd: %hd\n", -12000);
    // printk("hu: %hu\n", 12000);
    // printk("hx: 0x%hx\n", -1);

    while (1) asm("hlt");
}