#ifndef __DRIVERS_SEGMENT_DISPLAY_H_
#define __DRIVERS_SEGMENT_DISPLAY_H_

/*
 * 7-segment display driver
 *
 * Author: Eric Strihagen
 * Date: 2025-11-29
 *
 */

#include <stdint.h>

#define _7SEGMENT_DISPLAY_COUNT 6
#define _7SEGMENT_DISPLAY_BASE 0x4000050

typedef union {
    struct {
        uint8_t top : 1;
        uint8_t top_right : 1;
        uint8_t bot_right : 1;
        uint8_t bot : 1;
        uint8_t bot_left : 1;
        uint8_t top_left : 1;
        uint8_t mid : 1;
        uint8_t dot : 1;
    };
    uint8_t byte;
} seg_part_t;


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
void seg_display_set(uint8_t display_number, uint8_t value);
void seg_display_clear(uint8_t display_number);

#endif  // __DRIVERS_SEGMENT_DISPLAY_H_
