#pragma once

#include <stdint.h>
#include "ball.h"
#include "conn.h"

typedef struct {
    game_conn_t* conn;
    ball_t players[11];
} game_t;

void game_init(game_t* my);
void game_tick(game_t* my);
void game_frame(game_t* my);