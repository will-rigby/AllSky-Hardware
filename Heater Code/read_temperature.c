#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcp9808.h"

int main(int argc, char* argv[]){
    if(mcp9808_init()){
        printf("Error: Failed to initialise MCP9808\r\n");
        return 1;
    }
    float temperature;
    if(mcp9808_get_temperature(&temperature)){
        printf("Error: Failed to read MCP9808\r\n");
        return 1;
    }

    printf("Temperature: %fC\r\n", temperature);
    return 0;
}