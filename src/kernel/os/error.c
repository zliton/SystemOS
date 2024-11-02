#include "functions.h"

void errorMsg(char msg) {
    char message = "Error Code:" + msg;
    printk(message,6);
}
