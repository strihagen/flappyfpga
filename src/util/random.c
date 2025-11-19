/*
 * Random number utilities
 *
 * Provides lightweight xorshift32-based pseudo-random values and a randint helper.
 */

#include "util.h"

#include <limits.h>

static uint32_t rand_state = 0xACED1234u;

static inline uint32_t rand_xorshift32(void) {
    uint32_t x = rand_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rand_state = x;
    return x;
}

void rand_seed(uint32_t seed) {
    if (seed == 0) {
        seed = 0xACED1234u;
    }
    rand_state = seed;
}

uint32_t randint(uint32_t min, uint32_t max) {
    if (min == max) {
        return min;
    }

    if (min > max) {
        uint32_t tmp = min;
        min = max;
        max = tmp;
    }

    const uint32_t range = max - min + 1;
    const uint32_t limit = UINT32_MAX - (UINT32_MAX % range);

    uint32_t sample;
    do {
        sample = rand_xorshift32();
    } while (sample >= limit);

    return min + (sample % range);
}
