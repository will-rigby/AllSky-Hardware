#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>

extern int mcp3021_init(void);
extern int mcp3021_read(uint16_t* adcRead);
extern int mcp3021_get_voltage(float* voltage);