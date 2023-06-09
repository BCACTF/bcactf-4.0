#include <emscripten.h>
#include <stdint.h>

#include "ball.h"
#include "texture.h"

void ball_render(ball_t* ball) {
    EM_ASM({
        ctx.save();
        ctx.translate($3, $4);
        ctx.rotate($5);
        ctx.beginPath();
        ctx.arc(0, 0, $2, 0, Math.PI * 2);
        ctx.closePath();
        ctx.fillStyle = J[$0];
        ctx.fill();
        ctx.globalAlpha = 0.9;
        const imgpath = UTF8ToString($1);
        if (!window.imageMap.has(imgpath)) {
            const img = new Image();
            img.src = "/" + imgpath;
            img.isloaded = false;
            img.onload = () => img.isloaded = true;
            window.imageMap.set(imgpath, img);
        } else {
            const img = window.imageMap.get(imgpath);
            if (img.isloaded) {
                ctx.drawImage(img, -$2, -$2, $2 * 2, $2 * 2);
            }
        }
        ctx.globalAlpha = 1.0;
        ctx.restore();
    }, ball->skin, get_texture_path(ball->skin), ball->radius, ball->x, ball->y, ball->rot);
}
