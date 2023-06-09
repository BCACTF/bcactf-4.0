#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t* data;
    uint32_t size;
} buffer_t;

typedef struct {
    buffer_t* buffer;
    uint32_t pos;
} buffer_view_t;

typedef buffer_view_t qwriter_t;
typedef buffer_view_t qreader_t;

bool buffer_oob(buffer_view_t* my, uint32_t inc);
void buffer_destroy(buffer_t* buffer);
buffer_t* buffer_new(uint32_t size);

void qreader_init(qreader_t* my, buffer_t* buffer);
bool qreader_oob(qreader_t* my, uint32_t inc);
uint32_t qreader_vu32(qreader_t* my);
float qreader_f32(qreader_t* my);


void qwriter_init(qwriter_t* my, buffer_t* buffer);
void qwriter_new(qwriter_t* my, uint32_t size_max);
buffer_t* qwriter_done(qwriter_t* my);
bool qwriter_oob(qwriter_t* my, uint32_t inc);
qwriter_t* qwriter_vu32(qwriter_t* my, uint32_t num);
qwriter_t* qwriter_f32(qwriter_t* my, float num);
void qwriter_destroy(qwriter_t* my);