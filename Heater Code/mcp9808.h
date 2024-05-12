#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <math.h>


extern int mcp9808_init(void);
extern int mcp9808_write(int registerAddress, uint8_t* data, int length);
extern int mcp9808_read(int registerAddress, uint8_t* data, int length);
extern int mcp9808_get_temperature(float* temperature);