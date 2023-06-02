#include <emscripten.h>

#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <memory.h>

#include "game.h"
#include "conn.h"


void game_do_movement(game_t* my) {
    float x;
    float y;
    EM_ASM({
        HEAPF32[$0 >> 2] = window.mx;
        HEAPF32[$1 >> 2] = window.my;
    }, &x, &y);

    conn_trysend_movement(my->conn, x, y);
}

void game_init(game_t* my) {
    my->conn = (game_conn_t*) malloc(sizeof(game_conn_t));
    conn_init(my->conn);
    bzero(my->players, sizeof(my->players));
}

void game_tick(game_t* my) {
    ball_t players[11];
    
    conn_get_players(players);

    uint32_t j;
    uint32_t i;
    uint32_t cnt = 0;
    for (i = 11; i --> 0;) {
        for (j = 11; j --> 0;) {
            if (players[i].id == my->players[j].id) {
                if (players[j].skin != 0xFF) goto next;
            }
        }

        my->players[i].skin = 0xFF;
        continue;
        next:;
    }

    for (i = 11; i --> 0;) {
        for (j = 11; j --> 0;) {
            if (players[i].id == my->players[j].id) {
                goto found;
            }
        }
        players[i]._old_x = players[i].x;
        players[i]._old_y = players[i].y;
        continue;
        found:
        players[i]._old_x = my->players[j].x;
        players[i]._old_y = my->players[j].y;
    }

    memcpy(my->players, players, sizeof(ball_t) * 11);

    game_do_movement(my);
}
float fade = 0.0;
void game_frame(game_t* my) {
    bool loaded = false;
    for (uint32_t i = 0; i < 11; ++i) {
        if (my->players[i].skin != 0xFF) {
            loaded = true;
            break;
        }
    }

    if (loaded) {
        fade += ((1 - fade) * (1 - fade)) * 0.02;
        if (fade > 0.7) fade = 1;
    }

    EM_ASM({
        ctx.globalAlpha = 1 - $0;
        ctx.textAlign = "center";
        ctx.fillStyle = "white";
        ctx.font = "100px monospace";
        ctx.fillText("Super Circle Game", 0, 0);
        ctx.beginPath();
        ctx.arc(0, 0, 1024, 0, Math.PI * 2);
        ctx.closePath();
        ctx.globalAlpha = $0;
        ctx.fillStyle = "black";
        ctx.fill();
    }, fade);

    for (uint32_t i = 0; i < 11; ++i) {
        ball_t* p = &my->players[i];
        if (p->skin != 0xFF) {
            ball_render(p);
        }
    }
}
