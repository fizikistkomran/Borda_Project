#include "sensors.h"
#include <stdlib.h>
#include <time.h>

// Simulates sensor readings by generating random values
float i2c_sensor_read(uint8_t device_address, enum sensor_t sensor_type) {
    switch(sensor_type) {
        case SENSOR_TEMP:
            return 20.0 + rand() % 10;         // Returns 20–29 °C
        case SENSOR_HUMIDITY:
            return 40.0 + rand() % 10;         // Returns 40–49 % humidity
        case SENSOR_CO2:
            return 400.0 + rand() % 100;       // Returns 400–499 ppm CO2
        default:
            return 0.0;                        // Fallback for unknown sensor type
    }
}

