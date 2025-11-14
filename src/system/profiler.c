/* Profiler
 *
 * File: profiler.c
 * Author: Eric Strihagen
 * Date: 2025-11-14
 *
 * Declaration file: system/profiler.h
*/



#include "system/profiler.h"
#include "print.h"

#include <stdint.h>

// Store last cycle count and frame counter
static uint64_t last_cycle_count = 0;
static uint32_t frame_count = 0;

static ProfilerAvg profiler_avgs[PROFILER_MAX_BLOCKS];

/*
 * Profiler FPS
 * @brief: This prints the FPS every second
*/
void profiler_fps() {
    frame_count++;

    uint64_t now = profiler_read_mcycle();
    uint64_t elapsed_cycles = now - last_cycle_count;

    // If 1 second or more elapsed, compute FPS
    if (elapsed_cycles >= CPU_FREQ_HZ) {
        print("FPS: ");
        print_dec(frame_count);
        print("\n");

        // Reset counters
        last_cycle_count = now;
        frame_count = 0;
    }
}


/*
 * Profiler FPS Reset
 * @brief: Reset the FPS counter
 * @note: This is called every second in profiler_fps()
*/
void profiler_fps_reset() {
    last_cycle_count = profiler_read_mcycle();
    frame_count = 0;
}

/*
 * Profiler Accumulate
 * @param: name
 * @param: ticks uint32
 * @brief: This accumulates the number of cycles spent in a block
 * @note: The takes in a name and the number of cycles spent in the block
*/
void profiler_accumulate(const char *name, uint32_t ticks) {
    int i;
    for (i = 0; i < PROFILER_MAX_BLOCKS; i++) {
        if (profiler_avgs[i].name == NULL) {
            profiler_avgs[i].name = name;
            break;
        }
        if (profiler_avgs[i].name == name) break;
    }

    profiler_avgs[i].sum += ticks;
    profiler_avgs[i].count++;

    if (profiler_avgs[i].count >= PROFILER_AVG_COUNT) {
        print((char *)name);
        print(": avg ");
        print_dec(profiler_avgs[i].sum / profiler_avgs[i].count);
        print(" cycles\n");
        profiler_avgs[i].sum = 0;
        profiler_avgs[i].count = 0;
    }
}


/*
 * Profiler Print ProfilerBlockHWC
* @param: ProfilerBlockHWC
* @brief: This prints the difference between the start and end of a profiler block
* @note: The 64 bit hwc registers are truncated to 32 bits
*/
void profiler_hwc_diff_print(ProfilerBlockHWC *hwcb) {
    print("hwc mcycle: ");
    print_dec((uint32_t)(hwcb->end.mcycle - hwcb->start.mcycle));
    print("\n");

    print("hwc minstret: ");
    print_dec((uint32_t)(hwcb->end.minstret - hwcb->start.minstret));
    print("\n");

    print("hwc memory instructions: ");
    print_dec((uint32_t)(hwcb->end.mhpm3 - hwcb->start.mhpm3));
    print("\n");

    print("hwc I-cache misses: ");
    print_dec((uint32_t)(hwcb->end.mhpm4 - hwcb->start.mhpm4));
    print("\n");

    print("hwc D-cache misses: ");
    print_dec((uint32_t)(hwcb->end.mhpm5 - hwcb->start.mhpm5));
    print("\n");

    print("hwc I-cache stalls: ");
    print_dec((uint32_t)(hwcb->end.mhpm6 - hwcb->start.mhpm6));
    print("\n");

    print("hwc D-cache stalls: ");
    print_dec((uint32_t)(hwcb->end.mhpm7 - hwcb->start.mhpm7));
    print("\n");

    print("hwc data-hazard stalls: ");
    print_dec((uint32_t)(hwcb->end.mhpm8 - hwcb->start.mhpm8));
    print("\n");

    print("hwc ALU stalls: ");
    print_dec((uint32_t)(hwcb->end.mhpm9 - hwcb->start.mhpm9));
    print("\n");
}


