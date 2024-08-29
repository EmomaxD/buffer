#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int header;
    char payload[256];
    double timestamp;
} NetworkPacket;

void print_packet(const Buffer *headerBuffer, const Buffer *payloadBuffer, const Buffer *timestampBuffer, size_t index);

int main() {
    Buffer headerBuffer;
    Buffer payloadBuffer;
    Buffer timestampBuffer;

    buffer_init(&headerBuffer, BUFFER_TYPE_INT, 10 * sizeof(int));
    buffer_init(&payloadBuffer, BUFFER_TYPE_STRING, 10 * sizeof(char *));
    buffer_init(&timestampBuffer, BUFFER_TYPE_DOUBLE, 10 * sizeof(double));

    NetworkPacket packet1 = {123, "Hello, World!", 1.234};
    NetworkPacket packet2 = {456, "Another Packet", 5.678};

    if (!buffer_put_int(&headerBuffer, packet1.header) ||
        !buffer_put_string(&payloadBuffer, packet1.payload) ||
        !buffer_put_double(&timestampBuffer, packet1.timestamp)) {
        fprintf(stderr, "Failed to add packet1 data to buffers\n");
    }

    if (!buffer_put_int(&headerBuffer, packet2.header) ||
        !buffer_put_string(&payloadBuffer, packet2.payload) ||
        !buffer_put_double(&timestampBuffer, packet2.timestamp)) {
        fprintf(stderr, "Failed to add packet2 data to buffers\n");
    }

    for (size_t i = 0; i < 2; ++i) {
        print_packet(&headerBuffer, &payloadBuffer, &timestampBuffer, i);
    }

    buffer_free(&headerBuffer);
    buffer_free(&payloadBuffer);
    buffer_free(&timestampBuffer);

    return 0;
}

void print_packet(const Buffer *headerBuffer, const Buffer *payloadBuffer, const Buffer *timestampBuffer, size_t index) {
    int header;
    char *payload;
    double timestamp;

    if (buffer_get_int(headerBuffer, index, &header) &&
        buffer_get_string(payloadBuffer, index, &payload) &&
        buffer_get_double(timestampBuffer, index, &timestamp)) {
        printf("Packet %zu:\n", index + 1);
        printf("  Header: %d\n", header);
        printf("  Payload: %s\n", payload);
        printf("  Timestamp: %f\n", timestamp);
    } else {
        fprintf(stderr, "Failed to retrieve packet %zu data from buffers\n", index + 1);
    }
}
