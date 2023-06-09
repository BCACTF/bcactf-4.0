#include "crypto.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void crypto_init(crypto_t* my) {
    my->seed = 0xFFaaCCee;
    my->seed2 = 0xAAbbCC99;
}

void crypto_encrypt(crypto_t* my, buffer_t* buffer) {
    srand(my->seed);
    for (int i = 0; i < buffer->size; ++i) my->seed += buffer->data[i];
    (void) rand();
    for (int i = 0; i < buffer->size; ++i) {
        my->xorors[i] = (uint32_t) rand() ^ buffer->data[i];
    }
    
    for (int i = 0; i < buffer->size; ++i) {
        buffer->data[i] = my->xorors[i] & 0xFF;
    }
}

void crypto_decrypt(crypto_t* my, buffer_t* buffer) {
    srand(my->seed2);
    (void) rand();
    for (int i = 0; i < buffer->size; ++i) {
        my->xorors[i] = (uint32_t) rand() ^ buffer->data[i];
    }
    
    for (int i = 0; i < buffer->size; ++i) {
        buffer->data[i] = my->xorors[i] & 0xFF;
    }
    for (int i = 0; i < buffer->size; ++i) my->seed2 += buffer->data[i] + 7;
}

void rng_init(rng_t* my, uint64_t seed) {
    my->seed = seed;
    my->state = seed;
}

uint32_t rng_rand(rng_t* my) {
    const uint64_t MOD = 0x7FFFFFFF;
    const uint64_t MUL = 16807;
    const uint64_t INC = 0x998 + (my->seed % 0x293);

    my->state = (my->state * MUL + INC) % MOD;

    return (uint32_t) my->state;
}

float rng_randf(rng_t* my) {
    return ((float) rng_rand(my)) / (float) 0x7FFFFFFF;
}
