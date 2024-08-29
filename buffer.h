#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    BUFFER_TYPE_INT,
    BUFFER_TYPE_FLOAT,
    BUFFER_TYPE_DOUBLE,
    BUFFER_TYPE_STRING,
    BUFFER_TYPE_COUNT
} BufferType;

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    BufferType type;
} Buffer;

void buffer_init(Buffer *buffer, BufferType type, size_t initial_capacity);

void buffer_free(Buffer *buffer);

bool buffer_put_int(Buffer *buffer, int value);

bool buffer_put_float(Buffer *buffer, float value);

bool buffer_put_double(Buffer *buffer, double value);

bool buffer_put_string(Buffer *buffer, const char *value);

bool buffer_get_int(Buffer *buffer, size_t index, int *value);

bool buffer_get_float(Buffer *buffer, size_t index, float *value);

bool buffer_get_double(Buffer *buffer, size_t index, double *value);

bool buffer_get_string(Buffer *buffer, size_t index, char **value);

bool buffer_remove(Buffer *buffer, size_t index);

bool buffer_resize(Buffer *buffer, size_t new_capacity);

#endif // BUFFER_H
