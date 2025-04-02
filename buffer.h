#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_SIZE 30  // Max number of values stored in the buffer

// Holds the buffer data and its state
typedef struct {
    float data[BUFFER_SIZE];  // Stored values
    int head;                 // Next write position
    int count;                // How many values are in the buffer
} circular_buffer_t;

// Prepares the buffer for use (empty state)
void buffer_init(circular_buffer_t *buf);

// Adds a new value to the buffer (overwrites if full)
void buffer_add(circular_buffer_t *buf, float value);

// Copies all values from the buffer to an array
int buffer_get_all(circular_buffer_t *buf, float *out_array);

#endif

