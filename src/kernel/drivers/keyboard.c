#include "keyboard.h"

// puertos del teclado xd
#define KEYBOARD_DATA_PORT    0x60
#define KEYBOARD_STATUS_PORT  0x64

// asm
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// mapa de teclas
static char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};


char get_key() {
    char c = 0;
    while((inb(KEYBOARD_STATUS_PORT) & 1) == 0);

    uint8_t scancode = inb(KEYBOARD_DATA_PORT);
    
    if (scancode < 128) {
        c = keyboard_map[scancode];
    }
    
    return c;
}