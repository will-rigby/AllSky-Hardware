#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include "mcp9808.h"

#define MCP9808_ADDRESS 0x18

#define TEMPERATURE_REGISTER 0b0101

int mcp9808Fd;

int mcp9808_init(void){
    char* fileName = "/dev/i2c-1";
    if((mcp9808Fd = open(fileName, O_RDWR)) < 0){
        mcp9808Fd = -1;
        return 1;
    }

     if (ioctl(mcp9808Fd, I2C_SLAVE, MCP9808_ADDRESS) < 0){
        mcp9808Fd = -1;
        return 2;
     }

    return 0;
}

int mcp9808_write(int registerAddress, uint8_t* data, int length){
    uint8_t dataArray[256];
    for(int i = 0; i < length; i++){
        dataArray[i+1] = data[i];
    }

    dataArray[0] = registerAddress;
    if (write(mcp9808Fd, dataArray, length+1) != (length+1)) {
        mcp9808Fd = -1; 
        return -1;/* ERROR HANDLING: i2c transaction failed */
    }

    return 0;
}

int mcp9808_read(int registerAddress, uint8_t* data, int length){
    if (write(mcp9808Fd, &registerAddress, 1) != 1) {
        return -1;/* ERROR HANDLING: i2c transaction failed */
    }

    int value = (read(mcp9808Fd, data, length));
    if (value != length) {
        printf("I2C Read Failure: Returned number of bytes does not match requested.\r\nReturned: %d\r\nRequested: %d\r\n", value, length);
	    return -1;/* ERROR HANDLING: i2c transaction failed */
    }

    return 0;
}

int mcp9808_get_temperature(float* temperature){
    uint8_t dataArray[2];
    
    if(mcp9808_read(TEMPERATURE_REGISTER, dataArray, 2) != 0){
        return -1;
    }

    uint8_t upperByte = dataArray[0] & 0x1F;
    uint8_t lowerByte = dataArray[1];


    if ((upperByte & 0x10) == 0x10) {
        float fUpperByte = upperByte & 0x0F;
        float fLowerByte = lowerByte;
        *temperature = 256 - (fUpperByte * 16 + fLowerByte / 16);
    } else {
        float fUpperByte = upperByte;
        float fLowerByte = lowerByte;
        *temperature = fUpperByte * 16 + fLowerByte / 16;
    }
    return 0;
}

