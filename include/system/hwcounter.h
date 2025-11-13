#ifndef __SYSTEM_HWCOUNTER_H__
#define __SYSTEM_HWCOUNTER_H__

/*
 * Hardware Counters
 *
 * Author: Eric Strihagen
 * Date: 2025-11-13
 *
 */



#include <stdint.h>

typedef struct {
    uint64_t mcycle;
    uint64_t minstret;
    uint64_t mhpm3;
    uint64_t mhpm4;
    uint64_t mhpm5;
    uint64_t mhpm6;
    uint64_t mhpm7;
    uint64_t mhpm8;
    uint64_t mhpm9;
} hwcounters_t;


#endif /* __SYSTEM_HWCOUNTER_H__ */
