#pragma once

#include <stdint.h>
#include "bin.h"

typedef struct {

} crypto_t;

typedef struct {
    uint64_t seed;
    uint64_t state;
} rng_t;

void crypto_init(crypto_t* my);
void crypto_encrypt(crypto_t* my, buffer_t* buffer);
void crypto_decrypt(crypto_t* my, buffer_t* buffer);

void rng_init(rng_t* my, uint64_t seed);
uint32_t rng_rand(rng_t* my);
float rng_randf(rng_t* my);
