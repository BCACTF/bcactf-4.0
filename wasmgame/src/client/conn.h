#pragma once

#include <emscripten.h>
#include <stdlib.h>
#include <stdint.h>
#include "bin.h"
#include "crypto.h"
#include "ball.h"

typedef struct {
    uint32_t cookie;
    uint32_t texture;
    uint32_t ping;
    uint32_t update;
} ops_t;

typedef struct {
    crypto_t crypto;
    rng_t rng;
    ops_t ops;
    buffer_t* space;
    uint8_t selected_skin;
} game_conn_t;

EMSCRIPTEN_KEEPALIVE void on_msg(uint8_t* space, uint32_t size);

void conn_init(game_conn_t* my);
// up to 11s
void conn_get_players(ball_t* list);

void conn_trysend_movement(game_conn_t* my, float x, float y);