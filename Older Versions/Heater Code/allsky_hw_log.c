#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcp3021.h"
#include "mcp9808.h"


int main(int argc, char* argv[]){
    if(mcp3021_init()){
        printf("Error: Failed to initialise MCP3021\r\n");
        return 1;
    }
    float voltage;
    if(mcp3021_get_voltage(&voltage)){
        printf("Error: Failed to read MCP3021\r\n");
        return 1;
    }

    if(mcp9808_init()){
        printf("Error: Failed to initialise MCP9808\r\n");
        return 1;
    }
    float temperature;
    if(mcp9808_get_temperature(&temperature)){
        printf("Error: Failed to read MCP9808\r\n");
        return 1;
    }

    FILE *fptr;
    fptr = fopen("allsky_hw.log","w");
    if(fptr == NULL){
        return 1;
    }

    fprintf(fptr, "Battery Voltage: %.2fV\r\n", voltage+1.1);
    fprintf(fptr, "Board Temp %.1fC\r\n", temperature);

    fclose(fptr);
    return 0;
}