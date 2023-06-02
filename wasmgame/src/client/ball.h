#pragma once

#include <stdint.h>

typedef struct {
    uint32_t id;
    uint32_t radius;
    float x;
    float y;
    float rot;
    float _old_x;
    float _old_y;
    uint8_t skin;
} ball_t;

void ball_render(ball_t* ball);