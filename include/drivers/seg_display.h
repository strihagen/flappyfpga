#ifndef __DRIVERS_SEGMENT_DISPLAY_H_
#define __DRIVERS_SEGMENT_DISPLAY_H_

/*
 * 7-segment display driver
 *
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 */

#include <stdint.h>

#define _7SEGMENT_DISPLAY_BASE 0x4000050

// Segment encoding: 0 = on, 1 = off
static const uint32_t segments[10] = {
        0b11000000,  // 0
        0b11111001,  // 1
        0b10100100,  // 2
        0b10110000,  // 3
        0b10011001,  // 4
        0b10010010,  // 5
        0b10000010,  // 6
        0b11111000,  // 7
        0b10000000,  // 8
        0b10010000   // 9
};

void seg_display_init();
void seg_display_set(uint32_t display_number, uint32_t value);

#endif // __DRIVERS_SEGMENT_DISPLAY_H_
