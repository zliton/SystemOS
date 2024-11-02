#include <stddef.h>
#include <stdint.h>

#ifndef KERNEL_H
#define KERNEL_H
#define WHITE_TXT 0x07

void k_main();
void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);

#endif