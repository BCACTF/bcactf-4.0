#include <emscripten.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"

game_t* game = NULL;

void frame() {
    EM_ASM({
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.save();
        ctx.translate(ctx.canvas.width / 2, ctx.canvas.height / 2);
        ctx.imageSmoothingEnabled = false;
    });

    if (game != NULL) {
        game_tick(game);
        game_frame(game);
    }

    EM_ASM({
        ctx.restore();
    });
}

int main() {
    srand(time(NULL));

    game = (game_t*) malloc(sizeof(game_t));
    game_init(game);

    emscripten_set_main_loop(frame, 60, false);

    return 0;
}
