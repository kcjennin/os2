#ifndef VGA_H
#define VGA_H

#define VGA_newline VGA_display_char('\n')

void VGA_clear(void);
void VGA_display_char(char c);
void VGA_display_str(const char *);

#endif