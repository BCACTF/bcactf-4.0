#include "conn.h"

#include <emscripten.h>
#include <stdlib.h>
#include <stdint.h>
#include "flush.h"
#include "texture.h"
#include "bin.h"
#include "crypto.h"
#include "ball.h"
#include <stdio.h>

ball_t players_cache[11];

void ops_init(ops_t* ops, rng_t* rng) {
    const uint32_t OPCODE_MAX = 182931;

    uint32_t op;
    ops->cookie = (uint32_t) (((float) OPCODE_MAX) * rng_randf(rng));

    while (true) {
        op = (uint32_t) (((float) OPCODE_MAX) * rng_randf(rng));
        if (ops->cookie == op) continue;
        ops->texture = op;
        break;
    }

    while (true) {
        op = (uint32_t) (((float) OPCODE_MAX) * rng_randf(rng));
        if (ops->cookie == op) continue;
        if (ops->texture == op) continue;
        ops->ping = op;
        break;
    }

    while (true) {
        op = (uint32_t) (((float) OPCODE_MAX) * rng_randf(rng));
        if (ops->cookie == op) continue;
        if (ops->texture == op) continue;
        if (ops->ping == op) continue;
        ops->update = op;
        break;
    }
}

void conn_init(game_conn_t* my) {
    crypto_init(&my->crypto);
    my->rng.state = 0;
    my->ops.cookie = 0;
    my->selected_skin = 0xFF;
    
    my->space = buffer_new(2048);
    *((void**) my->space->data) = my;

    EM_ASM({
        ws = new WebSocket((location.href + "super").replace(/^http/g, 'ws'));
        ws.binaryType = 'arraybuffer';
        ws.addEventListener('message', (d) => {
            const bytes = new Uint8Array(d.data);
            HEAPU8.set(bytes, $0 - 16);
            _on_msg($0, bytes.length);
        });
        ws.addEventListener('close', () => {
            alert("Web server closed. Please contact admins");
            _on_close($0 - 16);
        });
    }, my->space->data + 32);

    for (int i = 0; i < 11; ++i) {
        players_cache[i].skin = 0xFF;
    }
}

void conn_talk(game_conn_t* my, buffer_t* buffer) {
    crypto_encrypt(&my->crypto, buffer);

    add_and_clone_packet_to_district(10, buffer);
}

void conn_send(game_conn_t* my, buffer_t* buffer) {
    EM_ASM({
        ws.send(HEAPU8.subarray($0, $0 + $1));
    }, buffer->data, buffer->size);
}

void conn_ping(game_conn_t* my, uint32_t size) {
    qwriter_t w;
    qwriter_new(&w, 128 + size * 6);
    qwriter_vu32(&w, my->ops.ping);
    for (int i = 0; i < size; ++i) {
        qwriter_vu32(&w, rng_rand(&my->rng));
    }
    buffer_t* out = qwriter_done(&w);

    conn_talk(my, out);

    qwriter_destroy(&w);
}
bool acceptable_skins[16] = {
    false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false
};

void conn_on_close(game_conn_t* my) {
    my->ops.cookie = 0;
}

void conn_on_msg(game_conn_t* my, buffer_t* view) {
    qreader_t r;
    qreader_init(&r, view);
    crypto_decrypt(&my->crypto, view);

    // only for first packet
    if (my->rng.state == 0) {
        uint32_t cookie = qreader_vu32(&r);
        uint32_t seed = qreader_vu32(&r);

        rng_init(&my->rng, seed);
        ops_init(&my->ops, &my->rng);
    } else {
        uint32_t op = qreader_vu32(&r);

        if (op == my->ops.ping) {
            uint32_t size = 0;
            while (!qreader_oob(&r, 0)) {
                (void) qreader_vu32(&r);
                size += 1;
                rng_rand(&my->rng);
            }

            conn_ping(my, size);
        } else if (op == my->ops.texture) {
            uint32_t def_count = qreader_vu32(&r);
            texture_t** textures = (texture_t**) malloc(sizeof(texture_t*) * def_count);

            uint32_t i = 0;
            for (; i < def_count; ++i) {
                texture_t* texture = (texture_t*) malloc(sizeof(texture_t));
                textures[i] = texture;

                uint32_t path_len = qreader_vu32(&r);
                texture->path = (char*) malloc(path_len + 1);
                for (uint32_t i = 0; i < path_len; ++i) {
                    texture->path[i] = (char) qreader_vu32(&r);
                }
                texture->path[path_len] = '\0';

                bool hidden = qreader_vu32(&r) == 1;

                uint32_t name_len = qreader_vu32(&r);
                char* name = (char*) malloc(name_len + 1);
                for (uint32_t i = 0; i < name_len; ++i) {
                    char c = (char) qreader_vu32(&r);
                    if (!hidden) name[i] = c;
                }
                name[name_len] = '\0';
                if (!hidden) texture->name = name;
                else {
                    texture->name = NULL;
                    texture->path = NULL;
                }

                if (!hidden) {
                    acceptable_skins[i] = true;
                }
            }

            do {
                my->selected_skin = (rand() % def_count);
            } while (acceptable_skins[my->selected_skin] == false);

            set_textures(textures, def_count);
        } else if (op == my->ops.update) {
            uint32_t count = qreader_vu32(&r);

            uint32_t i = 0;
            for (; i < count; ++i) {
                players_cache[i].id = qreader_vu32(&r);
                players_cache[i].x = qreader_f32(&r);
                players_cache[i].y = qreader_f32(&r);
                players_cache[i].rot = qreader_f32(&r);
                players_cache[i].radius = qreader_vu32(&r);
                players_cache[i].skin = (uint8_t) qreader_vu32(&r);
            }
            while (i < 11) {
                players_cache[i].id = 0;
                players_cache[i].x = 0;
                players_cache[i].y = 0;
                players_cache[i].radius = 0;
                players_cache[i].rot = 0;
                players_cache[i].skin = 0xFF;
                i += 1;
            }
        }
    }
}

void conn_get_players(ball_t* list) {
    // shrug
    for (int i = 0; i < 11; ++i) {
        list[i].id = players_cache[i].id;
        list[i].x = players_cache[i].x;
        list[i].y = players_cache[i].y;
        list[i].radius = players_cache[i].radius;
        list[i].rot = players_cache[i].rot;
        list[i].skin = players_cache[i].skin;
    }
}

void conn_trysend_movement(game_conn_t* my, float x, float y) {
    if (my->ops.cookie == 0) return;
    if (my->selected_skin == 0xFF) return;

    qwriter_t w;
    qwriter_new(&w, 24);
    qwriter_vu32(&w, my->ops.update);
    qwriter_f32(&w, x);
    qwriter_vu32(&w, my->selected_skin);
    qwriter_f32(&w, y);
    buffer_t* out = qwriter_done(&w);

    conn_talk(my, out);

    qwriter_destroy(&w);   
}

void conn_flushing(game_conn_t* my) {
    // little maze 2
    if (district_buffer_size(0) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(0);
        add_and_clone_packet_to_district(2, new);
        free(new);
    }
    if (district_buffer_size(1) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(1);
        add_and_clone_packet_to_district(5, new);
        free(new);
    }
    if (district_buffer_size(2) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(2);
        add_and_clone_packet_to_district(8, new);
        free(new);
    }
    if (district_buffer_size(3) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(3);
        add_and_clone_packet_to_district(7, new);
        free(new);
    }
    if (district_buffer_size(4) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(4);
        add_and_clone_packet_to_district(3, new);
        free(new);
    }
    if (district_buffer_size(5) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(5);
        add_and_clone_packet_to_district(6, new);
        free(new);
    }
    if (district_buffer_size(6) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(6);
        add_and_clone_packet_to_district(4, new);
        free(new);
    }
    if (district_buffer_size(7) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(7);
        add_and_clone_packet_to_district(9, new);
        free(new);
    }
    if (district_buffer_size(8) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(8);
        add_and_clone_packet_to_district(1, new);
        free(new);
    }
    if (district_buffer_size(9) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(9);
        conn_on_msg(my, new);
        free(new);
    }

    // little maze
    if (district_buffer_size(10) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(10);
        add_and_clone_packet_to_district(12, new);
        free(new);
    }
    if (district_buffer_size(11) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(11);
        add_and_clone_packet_to_district(15, new);
        free(new);
    }
    if (district_buffer_size(12) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(12);
        add_and_clone_packet_to_district(18, new);
        free(new);
    }
    if (district_buffer_size(13) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(13);
        add_and_clone_packet_to_district(17, new);
        free(new);
    }
    if (district_buffer_size(14) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(14);
        add_and_clone_packet_to_district(13, new);
        free(new);
    }
    if (district_buffer_size(15) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(15);
        add_and_clone_packet_to_district(16, new);
        free(new);
    }
    if (district_buffer_size(16) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(16);
        add_and_clone_packet_to_district(14, new);
        free(new);
    }
    if (district_buffer_size(17) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(17);
        add_and_clone_packet_to_district(19, new);
        free(new);
    }
    if (district_buffer_size(18) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(18);
        add_and_clone_packet_to_district(11, new);
        free(new);
    }
    if (district_buffer_size(19) != 0) {
        buffer_t* new = pop_packet_from_district_into_new_buffer(19);
        conn_send(my, new);
        free(new);
    }
}

void EMSCRIPTEN_KEEPALIVE on_msg(uint8_t* space, uint32_t size) {
    game_conn_t* conn = (game_conn_t*) *((void**) (space - 32));


    buffer_t view = {
        .data = conn->space->data + 16,
        .size = size
    };
    add_and_clone_packet_to_district(0, &view);
}

void EMSCRIPTEN_KEEPALIVE on_close(uint8_t* space, uint32_t size) {
    game_conn_t* conn = (game_conn_t*) *((void**) (space - 16));

    conn_on_close(conn);
}
