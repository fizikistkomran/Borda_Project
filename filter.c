#include "filter.h"
#include <math.h>
#include <string.h>

// Returns the median value of a float array
float get_median(float *data, int size) {
    float temp[size];
    memcpy(temp, data, sizeof(float) * size);  // Copy original data to sort safely

    // Simple sorting (bubble sort)
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (temp[i] > temp[j]) {
                float t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    return temp[size / 2];  // Return middle value
}

// Returns standard deviation of a float array
float get_std(float *data, int size) {
    float sum = 0, mean = 0, std = 0;

    for (int i = 0; i < size; i++) sum += data[i];
    mean = sum / size;

    for (int i = 0; i < size; i++) std += pow(data[i] - mean, 2);

    return sqrt(std / size);
}

// Returns the smallest value in the array
float get_min(float *data, int size) {
    float min = data[0];
    for (int i = 1; i < size; i++)
        if (data[i] < min)
            min = data[i];
    return min;
}

// Returns the largest value in the array
float get_max(float *data, int size) {
    float max = data[0];
    for (int i = 1; i < size; i++)
        if (data[i] > max)
            max = data[i];
    return max;
}

