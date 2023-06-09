#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "flush.h"

typedef struct {
    uint32_t pos;
    buffer_t* buffers[200];
} district_t;
district_t* districts[20];

void init_districts() {
    for (int i = 0; i < 20; ++i) {
        districts[i] = malloc(sizeof(district_t));
        districts[i]->pos = 0;
    }
}

uint32_t district_buffer_size(uint32_t id) {
    if (districts[0] == NULL) init_districts();

    return districts[id]->pos;
}

void add_and_clone_packet_to_district(uint32_t id, buffer_t* buffer) {
    if (districts[0] == NULL) init_districts();

    district_t* bin = districts[id];

    buffer_t* n = buffer_new(buffer->size);
    memcpy(n->data, buffer->data, buffer->size);
    for (int i = 0; i < buffer->size; ++i) n->data[i] ^= (i + id);
    for (int i = bin->pos + 1; i --> 1;) {
        bin->buffers[i] = bin->buffers[i - 1];
    }
    bin->buffers[0] = n;
    bin->pos++;
}

buffer_t* pop_packet_from_district_into_new_buffer(uint32_t id) {
    if (districts[0] == NULL) init_districts();

    district_t* bin = districts[id];
    buffer_t* old = bin->buffers[--bin->pos];

    buffer_t* n = buffer_new(old->size);
    memcpy(n->data, old->data, old->size);
    for (int i = 0; i < n->size; ++i) n->data[i] ^= (i + id);
    return n;
}