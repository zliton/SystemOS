#include "kernel.h"
#include "functions.h"
#include "keyboard.h"
#include "os.h"
void k_main() 
{

	init_keyboard();
	k_clear_screen();

	welcomeOs();
	while (1){

		
	}
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
