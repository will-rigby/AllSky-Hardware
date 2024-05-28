#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcp3021.h"

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

    

    printf("Voltage: %fV\r\n", voltage);
    return 0;
}