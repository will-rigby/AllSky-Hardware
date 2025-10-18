#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "heater.h"

int main(int argc, char* argv[]){
    heater_init();
    gpio_heater_off();
    return 0;
}