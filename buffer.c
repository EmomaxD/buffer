#include "buffer.h"
#include <stdlib.h>
#include <string.h>

// Helper function to resize the buffer's internal storage.
static bool buffer_resize_internal(Buffer *buffer, size_t new_capacity) {
    void *new_data = realloc(buffer->data, new_capacity);
    if (!new_data) {
        return false;
    }
    buffer->data = new_data;
    buffer->capacity = new_capacity;
    return true;
}

void buffer_init(Buffer *buffer, BufferType type, size_t initial_capacity) {
    buffer->type = type;
    buffer->size = 0;
    buffer->capacity = initial_capacity;
    buffer->data = malloc(initial_capacity);
}

void buffer_free(Buffer *buffer) {
    if (buffer->type == BUFFER_TYPE_STRING) {
        // Free strings if any
        char **strings = (char **)buffer->data;
        for (size_t i = 0; i < buffer->size; ++i) {
            free(strings[i]);
        }
    }
    free(buffer->data);
    buffer->data = NULL;
    buffer->size = 0;
    buffer->capacity = 0;
}

bool buffer_put_int(Buffer *buffer, int value) {
    if (buffer->type != BUFFER_TYPE_INT) {
        return false;
    }
    if (buffer->size * sizeof(int) >= buffer->capacity) {
        if (!buffer_resize_internal(buffer, buffer->capacity * 2)) {
            return false;
        }
    }
    ((int *)buffer->data)[buffer->size++] = value;
    return true;
}

bool buffer_put_float(Buffer *buffer, float value) {
    if (buffer->type != BUFFER_TYPE_FLOAT) {
        return false;
    }
    if (buffer->size * sizeof(float) >= buffer->capacity) {
        if (!buffer_resize_internal(buffer, buffer->capacity * 2)) {
            return false;
        }
    }
    ((float *)buffer->data)[buffer->size++] = value;
    return true;
}

bool buffer_put_double(Buffer *buffer, double value) {
    if (buffer->type != BUFFER_TYPE_DOUBLE) {
        return false;
    }
    if (buffer->size * sizeof(double) >= buffer->capacity) {
        if (!buffer_resize_internal(buffer, buffer->capacity * 2)) {
            return false;
        }
    }
    ((double *)buffer->data)[buffer->size++] = value;
    return true;
}

bool buffer_put_string(Buffer *buffer, const char *value) {
    if (buffer->type != BUFFER_TYPE_STRING) {
        return false;
    }
    size_t length = strlen(value) + 1;
    if (buffer->size * length >= buffer->capacity) {
        if (!buffer_resize_internal(buffer, buffer->capacity * 2)) {
            return false;
        }
    }
    char **strings = (char **)buffer->data;
    strings[buffer->size] = strdup(value);
    if (!strings[buffer->size]) {
        return false;
    }
    buffer->size++;
    return true;
}

bool buffer_get_int(Buffer *buffer, size_t index, int *value) {
    if (buffer->type != BUFFER_TYPE_INT || index >= buffer->size) {
        return false;
    }
    *value = ((int *)buffer->data)[index];
    return true;
}

bool buffer_get_float(Buffer *buffer, size_t index, float *value) {
    if (buffer->type != BUFFER_TYPE_FLOAT || index >= buffer->size) {
        return false;
    }
    *value = ((float *)buffer->data)[index];
    return true;
}

bool buffer_get_double(Buffer *buffer, size_t index, double *value) {
    if (buffer->type != BUFFER_TYPE_DOUBLE || index >= buffer->size) {
        return false;
    }
    *value = ((double *)buffer->data)[index];
    return true;
}

bool buffer_get_string(Buffer *buffer, size_t index, char **value) {
    if (buffer->type != BUFFER_TYPE_STRING || index >= buffer->size) {
        return false;
    }
    *value = ((char **)buffer->data)[index];
    return true;
}

bool buffer_remove(Buffer *buffer, size_t index) {
    if (index >= buffer->size) {
        return false;
    }

    if (buffer->type == BUFFER_TYPE_STRING) {
        char **strings = (char **)buffer->data;
        free(strings[index]);
    }

    memmove((char *)buffer->data + (index * sizeof(void *)), 
            (char *)buffer->data + ((index + 1) * sizeof(void *)),
            (buffer->size - index - 1) * sizeof(void *));
    
    buffer->size--;
    return true;
}

bool buffer_resize(Buffer *buffer, size_t new_capacity) {
    if (new_capacity < buffer->size * sizeof(void *)) {
        return false;
    }
    return buffer_resize_internal(buffer, new_capacity);
}
