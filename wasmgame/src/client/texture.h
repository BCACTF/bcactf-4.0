#pragma once

#include <stdint.h>

typedef struct {
    char* name;
    char* path;
} texture_t;

void set_textures(texture_t** textures, uint32_t count);
texture_t** get_textures();
uint32_t get_texture_count();
char* get_texture_path(uint32_t i);