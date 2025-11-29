/* Random Utils
 *
 * File: random.c
 * Author: Eric Strihagen
 * Date: 2025-11-28
 *
 * Declaration file: utils/random.h
*/



#include "system/csr.h"

#include <stdint.h>

static uint32_t state = 0xECAEBAD4;
/*
    * Random generator
    * Not cryptic safe
    * XORSHIFT
    * Random unsigned integer 0 to MAX_INT
*/
uint32_t rand32() {
    uint32_t x = csr_get_mcycle_low() ^ state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state = x;
    return x;
}
