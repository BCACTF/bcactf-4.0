#include <stdlib.h>
#include <stdint.h>
#include "texture.h"

uint32_t _count;
texture_t** _textures = NULL;

void set_textures(texture_t** textures, uint32_t count) {
    _count = count;
    _textures = textures;
}

texture_t** get_textures() {
    return _textures;
}


uint32_t get_texture_count() {
    return _count;
}
char* get_texture_path(uint32_t i) {
    return _textures[i]->path;
}