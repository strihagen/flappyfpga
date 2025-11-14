#ifndef __SYSTEM_PROFILER_H__
#define __SYSTEM_PROFILER_H__

/*
 * Profiler
 *
 * Author: Eric Strihagen
 * Date: 2025-11-14
 *
 */

#include "system/hwcounter.h"
#include "system/csr.h"
#include "print.h" // Required for macros

#include <stdint.h>
#include <stddef.h>

// CPU frequency in Hz
#define CPU_FREQ_HZ 30000000ULL  // 30 MHz for example

// Used inside Accumulator for allowed blocks and average
#define PROFILER_MAX_BLOCKS 16
#define PROFILER_AVG_COUNT 100  // average every 100 runs






/* =================================
 * Profiler Block Structs
 * =================================
 */
typedef struct {
    hwcounters_t start;
    hwcounters_t end;
} ProfilerBlockHWC;

typedef struct {
    uint64_t start;
    uint64_t end;
} ProfilerBlock;

typedef struct {
    const char *name;
    uint32_t sum;      // accumulated cycles
    uint32_t count;    // number of times profiled
} ProfilerAvg;






/* =================================
 * Profiler Macros
 * =================================
 */

/*
 * Normal profiling
 * Uses 64bit part of mcycle counter
 * And then truncates to 32bits
 * Safe for multiple interrupts running at the same time
*/
#define PROFILE_BLOCK_CYCLES(name, code) \
    do { \
        ProfilerBlock __pb; \
        profiler_block_start(&__pb); \
        code; \
        profiler_block_end(&__pb); \
        print(name ": "); \
        print_dec((uint32_t)profiler_block_cycles(&__pb)); \
        print("\n"); \
    } while(0)


/*
 * Fast profiling
 * Uses only 32bit part of mcycle counter.
 * Only use for short functions.
 * Safe for multiple interrupts running at the same time
*/
#define PROFILE_BLOCK_CYCLES_FAST(name, code) \
    do { \
        ProfilerBlock __pb; \
        profiler_block_start_fast(&__pb); \
        code; \
        profiler_block_end_fast(&__pb); \
        print(name ": "); \
        print_dec((uint32_t)profiler_block_cycles(&__pb)); \
        print("\n"); \
    } while(0)


/*
 * Average profiling
 * @Usage:
 *     PROFILE_BLOCK_AVG("name", function());
 *  Truncates ticks to 32bits
*/
#define PROFILE_BLOCK_AVG(name, code) \
    do { \
        ProfilerBlock __pb; \
        profiler_block_start(&__pb); \
        code; \
        profiler_block_end(&__pb); \
        profiler_accumulate(name, (uint32_t)profiler_block_cycles(&__pb)); \
    } while(0)


/*
 * Hardware counter profiling
 * Expect higher overhead, since you need to read all hardware counters
 * twice and check for validity. This is because each register is 64 bits.
 * and on 32bit system we need to read low and high separately.
 */
#define PROFILE_BLOCK_HWC(name, code) \
    do { \
        ProfilerBlockHWC __pb; \
        profiler_block_hwc_start(&__pb); \
        code; \
        profiler_block_hwc_end(&__pb); \
        print(name "\n"); \
        profiler_hwc_diff_print(&__pb); \
        print("\n"); \
    } while(0)






/* =================================
 * Profiler Functions
 * =================================
 * Main functions defined in system/profiler.c
*/
void profiler_fps();
void profiler_fps_reset();
void profiler_accumulate(const char *name, uint32_t ticks);
void profiler_hwc_diff_print(ProfilerBlockHWC *hwcb);






/* =================================
 * Profiler mcycle register READ
 * =================================
*/
// Read the 64-bit mcycle counter
static inline uint64_t profiler_read_mcycle() {
    uint32_t lo, hi, hi2;
    do {
        __asm__ volatile ("csrr %0, mcycleh" : "=r"(hi));
        __asm__ volatile ("csrr %0, mcycle"  : "=r"(lo));
        __asm__ volatile ("csrr %0, mcycleh" : "=r"(hi2));
    } while (hi != hi2);
    return ((uint64_t)hi << 32) | lo;
}


/* Read the 32-bit mcycle counter
 * Used for getting more accurate results for short/fast functions.
 * if mcycle becomes larger than 32bits, use profiler_read_mcycle()
 */
static inline uint32_t profiler_read_mcycle_lo(void) {
    uint32_t lo;
    __asm__ volatile ("csrr %0, mcycle" : "=r"(lo));
    return lo;
}






/* =================================
 * Profiler Block Helpers
 * =================================
 * Short helper functions
 * Performance critical
 * Therefore these are inlined
 */


/*
 * Profiler Block Start
 * @brief: This starts a profile block using 64bit mcycle
*/
static inline void profiler_block_start(ProfilerBlock *pb) {
    pb->start = profiler_read_mcycle();
}

/*
 * Profiler Block Start Fast
 * @brief: This starts a profile block only using 32bit mcycle
*/
static inline void profiler_block_start_fast(ProfilerBlock *pb) {
    pb->start = profiler_read_mcycle_lo();
}

/*
 * Profiler Block End
 * @brief: This ends a profile block using 64bit mcycle
*/
static inline void profiler_block_end(ProfilerBlock *pb) {
    pb->end = profiler_read_mcycle();
}

/*
 * Profiler Block End Fast
 * @brief: This ends a profile block only using 32bit mcycle
*/
static inline void profiler_block_end_fast(ProfilerBlock *pb) {
    pb->end = profiler_read_mcycle_lo();
}

/*
 * Profiler Block Get Cycles
 * @return: cycles (uint64) between profiler_start() and profiler_end()
 * @brief: This returns the number of cycles spent in a block
*/
static inline uint64_t profiler_block_cycles(ProfilerBlock *pb) {
    return pb->end - pb->start;
}

/*
 * Hardware counter profiling
 * @param: ProfilerBlockHWC
 * @brief: This starts a profile block using 64bit hardware counters
 * Expect higher overhead, since you need to read all hardware counters
 * twice and check for validity. This is because each register is 64 bits.
 * and on 32bit system we need to read low and high separately.
*/
static inline void profiler_block_hwc_start(ProfilerBlockHWC *pb) {
    csr_read_all_hardware_counters(&pb->start);
}

/*
 * Hardware counter profiling
 * @param: ProfilerBlockHWC
 * @brief: This ends a profile block using 64bit hardware counters
 * Expect higher overhead, since you need to read all hardware counters
 * twice and check for validity. This is because each register is 64 bits.
 * and on 32bit system we need to read low and high separately.
*/
static inline void profiler_block_hwc_end(ProfilerBlockHWC *pb) {
    csr_read_all_hardware_counters(&pb->end);
}


#endif /* __SYSTEM_PROFILER_H__ */

