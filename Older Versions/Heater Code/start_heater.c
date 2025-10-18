#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "heater.h"

int main(int argc, char* argv[]){
    if(!heater_init()){
        heater_on();
        return 0;
    }
    
    return 1;
}