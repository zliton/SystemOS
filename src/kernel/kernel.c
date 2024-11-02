#include "kernel.h"
#include "functions.h"
void k_main() 
{
	k_clear_screen();
	printk("Kernel Iniciado")
};

void k_clear_screen()
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
};
