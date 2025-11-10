/* 7 Segment Display driver
 *
 * File: seg_display.c
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 * Declaration file: drivers/seg_display.h
*/

#include <drivers/seg_display.h>

#include <stdint.h>

void seg_display_init() {
    volatile uint32_t *display = (volatile uint32_t*)_7SEGMENT_DISPLAY_BASE;
    for (int i = 0; i < 6; i++) {
        display[i] = 0xFF;
    }
}


void seg_display_set(uint32_t display_number, uint32_t value) {
    if (display_number > 6 || display_number < 1)
        return;
    else if (value > 9 || value < 0)
        return;
    volatile uint32_t *display =
        (volatile uint32_t*)(_7SEGMENT_DISPLAY_BASE + (display_number - 1) * 0x10);

    *display = segments[value];
}

