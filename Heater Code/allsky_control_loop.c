#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcp3021.h"
#include "mcp9808.h"
#include "heater.h"

#define LOG_FILE "allsky_hw.log"

void log_state(float temperature, float voltage, int heaterState, char* logFileName){
    FILE *fptr;
    fptr = fopen(logFileName,"w");
    if(fptr == NULL){
        printf("Error: Failed to log\r\n");
        return;
    }

    fprintf(fptr, "Battery Voltage: %.2fV\r\n", voltage);
    fprintf(fptr, "Board Temp: %.1fC\r\n", temperature);
    if(heaterState){
        fprintf(fptr, "Heater: ON\r\n");
    } else {
         fprintf(fptr, "Heater: OFF\r\n");
    }

    fclose(fptr);
}

int init_peripherals(void){
    int success = 0;
    if(mcp3021_init()){
        printf("Error: Failed to initialise MCP3021\r\n");
        success |= 1;
    }
    
    if(mcp9808_init()){
        printf("Error: Failed to initialise MCP9808\r\n");
        success |= 1;
    }

    if(heater_init()){
        printf("Error: Failed to initialise Heater GPIO\r\n");
        success |= 1;
    }
    return success;
}

int main(int argc, char* argv[]){
    if(init_peripherals()){
        printf("Failed to initialise peripherals.\r\nExiting.\r\n");
        return 1;
    }
    printf("Peripherals Initialised\r\n");
    while(1){
        float voltage;
        float temperature;
        int heaterState = 0;

        if(mcp3021_get_voltage(&voltage)){
            printf("Error: Failed to read MCP3021\r\n");
        }
        voltage = voltage + 1.1;
        
        if(mcp9808_get_temperature(&temperature)){
            printf("Error: Failed to read MCP9808\r\n");
        }
        

        if(temperature < 30){
            heaterState = 1;
        }

        log_state(temperature, voltage, heaterState, LOG_FILE);

        if(heaterState){
            heater_on();
            printf("Heater ON\r\n");
        } else{
            heater_off();
        }
        sleep(5);
        heater_off();
        printf("Heater OFF\r\n");
        sleep(55);

    }
    return 0;
}