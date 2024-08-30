#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint8_t *data;
    size_t size;
    size_t capacity;
} Buffer;

void buffer_init(Buffer *buf, size_t capacity);
void buffer_free(Buffer *buf);
void buffer_write(Buffer *buf, const void *src, size_t size, size_t offset);
void buffer_writeInt8(Buffer *buf, int8_t value, size_t offset);
void buffer_writeUInt8(Buffer *buf, uint8_t value, size_t offset);
void buffer_writeInt16(Buffer *buf, int16_t value, size_t offset);
void buffer_writeUInt16(Buffer *buf, uint16_t value, size_t offset);
void buffer_writeInt32(Buffer *buf, int32_t value, size_t offset);
void buffer_writeUInt32(Buffer *buf, uint32_t value, size_t offset);
void buffer_writeInt64(Buffer *buf, int64_t value, size_t offset);
void buffer_writeUInt64(Buffer *buf, uint64_t value, size_t offset);
void buffer_writeString(Buffer *buf, const char *str, size_t offset);
void buffer_read(Buffer *buf, void *dst, size_t size, size_t offset);
int8_t buffer_readInt8(Buffer *buf, size_t offset);
uint8_t buffer_readUInt8(Buffer *buf, size_t offset);
int16_t buffer_readInt16(Buffer *buf, size_t offset);
uint16_t buffer_readUInt16(Buffer *buf, size_t offset);
int32_t buffer_readInt32(Buffer *buf, size_t offset);
uint32_t buffer_readUInt32(Buffer *buf, size_t offset);
int64_t buffer_readInt64(Buffer *buf, size_t offset);
uint64_t buffer_readUInt64(Buffer *buf, size_t offset);
const uint8_t* buffer_data(const Buffer *buf);
size_t buffer_size(const Buffer *buf);

inline void buffer_writeInt8(Buffer *buf, int8_t value, size_t offset) {
    buffer_write(buf, &value, sizeof(value), offset);
}

inline void buffer_writeUInt8(Buffer *buf, uint8_t value, size_t offset) {
    buffer_write(buf, &value, sizeof(value), offset);
}

inline void buffer_writeInt16(Buffer *buf, int16_t value, size_t offset) {
    buffer_write(buf, &value, sizeof(value), offset);
}

inline void buffer_writeUInt16(Buffer *buf, uint16_t value, size_t offset) {
    buffer_write(buf, &value, sizeof(value), offset);
}

inline void buffer_writeInt32(Buffer *buf, int32_t value, size_t offset) {
    buffer_write(buf, &value, sizeof(value), offset);
}

inline void buffer_writeUInt32(Buffer *buf, uint32_t value, size_t offset) {
    buffer_write(buf, &value, sizeof(value), offset);
}

inline void buffer_writeInt64(Buffer *buf, int64_t value, size_t offset) {
    buffer_write(buf, &value, sizeof(value), offset);
}

inline void buffer_writeUInt64(Buffer *buf, uint64_t value, size_t offset) {
    buffer_write(buf, &value, sizeof(value), offset);
}

inline int8_t buffer_readInt8(Buffer *buf, size_t offset) {
    int8_t value;
    buffer_read(buf, &value, sizeof(value), offset);
    return value;
}

inline uint8_t buffer_readUInt8(Buffer *buf, size_t offset) {
    uint8_t value;
    buffer_read(buf, &value, sizeof(value), offset);
    return value;
}

inline int16_t buffer_readInt16(Buffer *buf, size_t offset) {
    int16_t value;
    buffer_read(buf, &value, sizeof(value), offset);
    return value;
}

inline uint16_t buffer_readUInt16(Buffer *buf, size_t offset) {
    uint16_t value;
    buffer_read(buf, &value, sizeof(value), offset);
    return value;
}

inline int32_t buffer_readInt32(Buffer *buf, size_t offset) {
    int32_t value;
    buffer_read(buf, &value, sizeof(value), offset);
    return value;
}

inline uint32_t buffer_readUInt32(Buffer *buf, size_t offset) {
    uint32_t value;
    buffer_read(buf, &value, sizeof(value), offset);
    return value;
}

inline int64_t buffer_readInt64(Buffer *buf, size_t offset) {
    int64_t value;
    buffer_read(buf, &value, sizeof(value), offset);
    return value;
}

inline uint64_t buffer_readUInt64(Buffer *buf, size_t offset) {
    uint64_t value;
    buffer_read(buf, &value, sizeof(value), offset);
    return value;
}

// Function implementations
void buffer_init(Buffer *buf, size_t capacity) {
    buf->data = (uint8_t *)malloc(capacity);
    if (!buf->data) {
        perror("Failed to allocate buffer");
        exit(EXIT_FAILURE);
    }
    buf->size = 0;
    buf->capacity = capacity;
    memset(buf->data, 0, capacity);
}

void buffer_free(Buffer *buf) {
    free(buf->data);
    buf->data = NULL;
    buf->size = 0;
    buf->capacity = 0;
}

void buffer_write(Buffer *buf, const void *src, size_t size, size_t offset) {
    if (offset + size > buf->capacity) {
        fprintf(stderr, "Buffer overflow\n");
        return;
    }
    memcpy(buf->data + offset, src, size);
    if (offset + size > buf->size) {
        buf->size = offset + size;
    }
}

void buffer_writeString(Buffer *buf, const char *str, size_t offset) {
    size_t len = strlen(str);
    buffer_write(buf, str, len, offset);
}

void buffer_read(Buffer *buf, void *dst, size_t size, size_t offset) {
    if (offset + size > buf->size) {
        fprintf(stderr, "Buffer underflow\n");
        return;
    }
    memcpy(dst, buf->data + offset, size);
}

const uint8_t* buffer_data(const Buffer *buf) {
    return buf->data;
}

size_t buffer_size(const Buffer *buf) {
    return buf->size;
}

#endif // BUFFER_H
