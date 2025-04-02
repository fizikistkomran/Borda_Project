#include "buffer.h"

// Start the buffer with empty values
void buffer_init(circular_buffer_t *buf) {
    buf->head = 0;
    buf->count = 0;
}

// Add a new value to the buffer
void buffer_add(circular_buffer_t *buf, float value) {
    buf->data[buf->head] = value;               // Add value at the current head position
    buf->head = (buf->head + 1) % BUFFER_SIZE;  // Move head forward (loop if needed)

    if (buf->count < BUFFER_SIZE)
        buf->count++;                           // Increase count if not full yet
}

// Copy all values from the buffer to an array
int buffer_get_all(circular_buffer_t *buf, float *out_array) {
    int index = buf->head - buf->count;         // Find the start point
    if (index < 0)
        index += BUFFER_SIZE;                   // Wrap around if needed

    for (int i = 0; i < buf->count; i++) {
        out_array[i] = buf->data[(index + i) % BUFFER_SIZE];
    }

    return buf->count;                          // Return how many values we copied
}

