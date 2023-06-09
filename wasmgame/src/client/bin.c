#include "bin.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

buffer_t* buffer_new(uint32_t size) {
    buffer_t* new = (buffer_t*) malloc(sizeof(buffer_t));
    new->data = calloc(size, 1);
    new->size = size;

    return new;
}

void buffer_destroy(buffer_t* buffer) {
    free(buffer->data);
    free(buffer);
}

bool buffer_oob(buffer_view_t* my, uint32_t inc) {
    if ((my->pos + inc) >= my->buffer->size) return true;

    return false;
}

void qreader_init(qreader_t* my, buffer_t* buffer) {
    my->buffer = buffer;
    my->pos = 0;
}

bool qreader_oob(qreader_t* my, uint32_t inc) {
    return buffer_oob((buffer_view_t*) my, inc);
}

uint32_t qreader_vu32(qreader_t* my) {
    if (qreader_oob(my, 0)) return 0;
    uint32_t out = my->buffer->data[my->pos] & 0x7F;
    uint8_t i = 0;
    while (my->buffer->data[my->pos++] & 0x80) {
        if (qreader_oob(my, 0)) return 0;
        i += 7;
        out |= (my->buffer->data[my->pos] & 0x7F) << i;
    
        if (i > 32) break;
    }

    return out;
}

union {
    float f32;
    uint8_t u8[4];
} view;

float qreader_f32(qreader_t* my) {
    if (buffer_oob(my, 3)) return 0.0;

    view.u8[0] = my->buffer->data[my->pos++];
    view.u8[1] = my->buffer->data[my->pos++];
    view.u8[2] = my->buffer->data[my->pos++];
    view.u8[3] = my->buffer->data[my->pos++];

    return view.f32;
}

void qwriter_new(qwriter_t* my, uint32_t size_max) {
    my->buffer = buffer_new(size_max);
    my->pos = 0;
}

void qwriter_init(qwriter_t* my, buffer_t* buffer) {
    my->buffer = buffer;
    my->pos = 0;
}

buffer_t* qwriter_done(qwriter_t* my) {
    my->buffer->size = my->pos;
    return my->buffer;
}

bool qwriter_oob(qwriter_t* my, uint32_t inc) {
    return buffer_oob((buffer_view_t*) my, inc);
}

qwriter_t* qwriter_vu32(qwriter_t* my, uint32_t num) {
    do {
        if (qwriter_oob(my, 0)) break;
        my->buffer->data[my->pos] = num & 0x7F;
        num >>= 7;
        if (num) my->buffer->data[my->pos] |= 0x80;
        my->pos += 1;
    } while (num > 0);

    return my;
}

qwriter_t* qwriter_f32(qwriter_t* my, float num) {
    if (buffer_oob(my, 3)) return my;

    view.f32 = num;
    my->buffer->data[my->pos++] = view.u8[0];
    my->buffer->data[my->pos++] = view.u8[1];
    my->buffer->data[my->pos++] = view.u8[2];
    my->buffer->data[my->pos++] = view.u8[3];

    return my;
}

// Only call if the qwriter is qwriter_new-ed
void qwriter_destroy(qwriter_t* my) {
    buffer_destroy(my->buffer);
}