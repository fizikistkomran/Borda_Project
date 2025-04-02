#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "sensors.h"
#include "filter.h"
#include "buffer.h"

#define WINDOW_SIZE 5
#define ENCODE(val) ((uint16_t)((val) * 100))

circular_buffer_t temp_buf, humid_buf, co2_buf;

int main() {
    srand(time(NULL));

    buffer_init(&temp_buf);
    buffer_init(&humid_buf);
    buffer_init(&co2_buf);

    // BLE advertisement permission
    system("sudo hciconfig hci0 up");

    float temp_window[WINDOW_SIZE];
    float humid_window[WINDOW_SIZE];
    float co2_window[WINDOW_SIZE];
    
    //infinite loop
    for (int cycle = 0; ; cycle++) {
        printf("\n--- [BLE Packet %d] ---\n", cycle + 1);

        // adds simulation measurement data to particular lists until window size full
        for (int i = 0; i < WINDOW_SIZE; i++) {
            temp_window[i] = i2c_sensor_read(0x44, SENSOR_TEMP);
            humid_window[i] = i2c_sensor_read(0x40, SENSOR_HUMIDITY);
            co2_window[i] = i2c_sensor_read(0x5A, SENSOR_CO2);
            sleep(1);
        }

        // Median data
        float temp = get_median(temp_window, WINDOW_SIZE);
        float humid = get_median(humid_window, WINDOW_SIZE);
        float co2 = get_median(co2_window, WINDOW_SIZE);

        buffer_add(&temp_buf, temp);
        buffer_add(&humid_buf, humid);
        buffer_add(&co2_buf, co2);

        // Buffer data
        float temp_vals[BUFFER_SIZE], humid_vals[BUFFER_SIZE], co2_vals[BUFFER_SIZE];
        int temp_count = buffer_get_all(&temp_buf, temp_vals);
        int humid_count = buffer_get_all(&humid_buf, humid_vals);
        int co2_count = buffer_get_all(&co2_buf, co2_vals);

        float stats[12] = {
            get_median(temp_vals, temp_count),
            get_min(temp_vals, temp_count),
            get_max(temp_vals, temp_count),
            get_std(temp_vals, temp_count),

            get_median(humid_vals, humid_count),
            get_min(humid_vals, humid_count),
            get_max(humid_vals, humid_count),
            get_std(humid_vals, humid_count),

            get_median(co2_vals, co2_count),
            get_min(co2_vals, co2_count),
            get_max(co2_vals, co2_count),
            get_std(co2_vals, co2_count)
        };

        //predefined encode function converts stats[] data to 16 bit.
        uint16_t encoded[12];
        for (int i = 0; i < 12; i++)
            encoded[i] = ENCODE(stats[i]);

        //advertisement starting command
        char payload[512] = "sudo hcitool -i hci0 cmd 0x08 0x0008 1F 02 01 06 1A FF 00 FF";
        char hex[16];
        //divides upper and lower byte parts because BLE only advertise bytes.
        for (int i = 0; i < 12; i++) {
            sprintf(hex, " %02X %02X", encoded[i] >> 8, encoded[i] & 0xFF);
            strcat(payload, hex);
        }

        
        system("sudo hciconfig hci0 noleadv");
        printf("BLE Payload:\n%s\n", payload);
        system(payload);
        system("sudo hciconfig hci0 leadv 3");

        printf("Packet sent. Waiting 30 seconds...\n");
        sleep(30);
    }

    return 0;
}

