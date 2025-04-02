#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>  // For uint8_t type

// Sensor types (as enum)
enum sensor_t {
    SENSOR_TEMP,
    SENSOR_HUMIDITY,
    SENSOR_CO2
};

// Returns simulated sensor data for the given sensor type and address
float i2c_sensor_read(uint8_t device_address, enum sensor_t sensor_type);

#endif

