#include <vga.h>
#include <string.h>
#include <printk.h>

void test_printk(void);

void kmain(void)
{
    int i, j=0;
    // while(!j);

    VGA_clear();

    // test_printk();

    while (1) asm("hlt");
}

void test_printk(void)
{
    // normals
    printk("normals: ");
    printk("string: %s\n", "Hello, World!");
    printk("pointer: %p\n", &j);
    printk("d: %d ", -2000000);
    printk("u: %u ", 2000000);
    printk("x: 0x%x ", -1);
    printk("c: %c\n", '^');

    // longs
    printk("longs: ");
    printk("ld: %ld ", -10000000L);
    printk("lu: %lu ", 10000000L);
    printk("lx: 0x%lx\n", -1L);

    // shorts
    printk("shorts: ");
    printk("hd: %hd ", -12000);
    printk("hu: %hu ", 12000);
    printk("hx: 0x%hx\n", -1);

    // long longs
    printk("long longs: ");
    printk("qd: %qd ", -10000000LL);
    printk("qu: %qu ", 10000000LL);
    printk("qx: 0x%qx\n", -1LL);
}