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

void msgBiosOff(){
    const char *message = "Turning off BIOS";
    for (int i = 1; i <= 4; i++) {
        printk("%s", message);
        
        for (int j = 0; j < i; j++) {
            printk(".",1);
            fflush(stdout);
            sleep(1);
        }
        
        printk("\n",2);
        sleep(1);
    }
}


void welcomeOs() {
    printk("SYSTEM OS (v0.0.1)",0);
    printk("johndoe@coredata",1);
    printk("----------------",2);
    printk("OS: System OS 0.0.1",3);
    printk("Kernel: 0.0.1-generic",4);
    printk("Packages: 3 (dpkg)",5);
    printk("Shell: bash 5.2.15",6);
    printk("Terminal: /dev/pts/0",7);
}