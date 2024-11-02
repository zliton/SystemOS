#include "print.c"
#include <stdio.h>
#include <unistd.h>
void welcomeMessage(unsigned int line){
    printk("=================\n    System OS    \n=================", line);
}

void ruuningKernel(){
    const char *message = "Running Kernel";
    for (int i = 1; i <= 4; i++) {
        printk("%s", message);
        
        // Imprimir puntos
        for (int j = 0; j < i; j++) {
            printk(".",0);
            fflush(stdout);
            sleep(1);
        }
        
        printk("\n",1);
        sleep(1);
    }
}