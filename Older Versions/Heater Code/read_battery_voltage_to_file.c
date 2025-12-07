#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
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

    printf("Voltage=%.2f\r\n", voltage);

    // --- Logging section ---
    const char *home = getenv("HOME");
    if (!home) home = ".";
    char log_dir[512];
    snprintf(log_dir, sizeof(log_dir), "%s/logs", home);

    // Make sure ~/logs exists
    mkdir(log_dir, 0755);

    char log_path[512];
    snprintf(log_path, sizeof(log_path), "%s/battery_voltage.log", log_dir);

    FILE *f = fopen(log_path, "a");
    if (f) {
        time_t now = time(NULL);
        struct tm *utc_tm = gmtime(&now);
        struct tm *local_tm = localtime(&now);

        char utc_buf[64], local_buf[64];
        strftime(utc_buf, sizeof(utc_buf), "%Y-%m-%d %H:%M:%S UTC", utc_tm);
        strftime(local_buf, sizeof(local_buf), "%Y-%m-%d %H:%M:%S %Z", local_tm);

        fprintf(f, "%s, %s, %.2fV\n", utc_buf, local_buf, voltage);
        fclose(f);
    } else {
        perror("Failed to open log file");
    }

    return 0;
}

