#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "mcp3021.h"
#include "mcp9808.h"
#include "heater.h"

#define LOG_FILE "/home/pi/heater/allsky_hw.log"

static volatile int keepRunning = 1;


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
        fprintf(fptr, "Heater: ON - ");
    } else {
         fprintf(fptr, "Heater: OFF - ");
    }
    
    time_t rawtime;
    struct tm * timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    fprintf(fptr, "%02d:%02d:%02d\r\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
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

void intHandler(int dummy) {
    heater_off();
    keepRunning = 0;
    printf("Signal to stop received.\r\n");
}

int main(int argc, char* argv[]){
    signal(2, intHandler);
    signal(SIGINT, intHandler);
    signal(SIGKILL, intHandler);
    signal(SIGSTOP, intHandler);
    signal(SIGTERM, intHandler);
    if(init_peripherals()){
        printf("Failed to initialise peripherals.\r\nExiting.\r\n");
        return 1;
    }
    printf("Peripherals Initialised\r\n");
    while(keepRunning){
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
        
        
        time_t rawtime;
        struct tm * timeinfo;
        
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        printf("%02d:%02d:%02d\r\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        if((timeinfo->tm_hour > 18) || (timeinfo->tm_hour < 6)){
            if(temperature < 20){
                heaterState = 2;
            } else if (temperature < 30){
                heaterState = 1;
            }
            
        }
        printf("Set Heater value\r\n");
        log_state(temperature, voltage, heaterState, LOG_FILE);
        printf("Logged\r\n");
        

        if(heaterState == 2){
            heater_on();
            printf("Heater ON for 5 seconds.\r\n");
            sleep(5);
            heater_off();
            printf("Heater OFF for 25 seconds.\r\n");
            sleep(25);  
        } else if (heaterState == 1){
            heater_on();
            printf("Heater ON for 5 seconds.\r\n");
            sleep(5);
            heater_off();
            printf("Heater OFF for 55 seconds.\r\n");
            sleep(55);  
        } else {
            heater_off();
            sleep(60);
        }
        heater_off();
        
        
        
       

    }
    heater_close();

    return 0;
}