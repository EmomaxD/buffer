## Usage
```c
typedef struct {
    int id;
    float value;
    char name[50];
} Data;

void serializeData(Buffer *buffer, const Data *data) {
    buffer_writeInt32(buffer, data->id, 0);
    buffer_write(buffer, &data->value, sizeof(data->value), 4);
    buffer_writeString(buffer, data->name, 8);
}

void deserializeData(Buffer *buffer, Data *data) {
    data->id = buffer_readInt32(buffer, 0);
    buffer_read(buffer, &data->value, sizeof(data->value), 4);
    memcpy(data->name, buffer_data(buffer) + 8, 50);
    data->name[49] = '\0'; // Ensure null-termination
}

int main() {
    Buffer buffer;
    buffer_init(&buffer, 1024); // Allocate 1024 bytes

    Data data = {1, 3.14f, "Example"};
    serializeData(&buffer, &data);

    Data deserializedData;
    deserializeData(&buffer, &deserializedData);

    buffer_free(&buffer);
    return 0;
}
```