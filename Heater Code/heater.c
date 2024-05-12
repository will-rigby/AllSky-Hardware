#include "heater.h"

int heater_init(void){
    if (gpioInitialise() < 0)
    {
        return 1;
    }
    if(gpioSetMode(15, PI_OUTPUT)){
        gpioWrite(15, 0);
        return 1;
    }
    gpioWrite(15, 0);
    return 0;
}

void heater_on(void){
    gpioWrite(15, 1);
}

void heater_off(void){
    gpioWrite(15, 0);
}

void heater_close(void){
    gpioTerminate();
}