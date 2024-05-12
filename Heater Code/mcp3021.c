#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include "mcp3021.h"

#define DEVICE_ADDRESS 0x4D



int mcp3021Fd;

int mcp3021_init(void){
    char* fileName = "/dev/i2c-1";
    if((mcp3021Fd = open(fileName, O_RDWR)) < 0){
        mcp3021Fd = -1;
        return 1;
    }

     if (ioctl(mcp3021Fd, I2C_SLAVE, DEVICE_ADDRESS) < 0){
        mcp3021Fd = -1;
        return 2;
     }

    return 0;
}

int mcp3021_read(uint16_t* adcRead){
    uint8_t data[2];
    int success = (read(mcp3021Fd, data, 2));
    if (success != 2) {
        printf("I2C Read Failure: Returned number of bytes does not match requested.\r\n");
	    return -1;/* ERROR HANDLING: i2c transaction failed */
    }

    *adcRead = (((uint16_t)data[0]) << 8) | ((uint16_t)data[1]);

    return 0;
}

int mcp3021_get_voltage(float* voltage){
    uint16_t adcValue;
    if(mcp3021_read(&adcValue)){
        return -1;
    }
    adcValue = 0x0FFF&(adcValue>>2);
    float reading = adcValue;
    float inputVoltage = (3.3*reading)/1024.0;
    *voltage = (10200+1620)/1620*inputVoltage;
    return 0;
}

