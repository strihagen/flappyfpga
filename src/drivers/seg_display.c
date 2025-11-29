/* 7 Segment Display driver
 *
 * File: seg_display.c
 * Author: Eric Strihagen
 * Date: 2025-11-29
 *
 * Declaration file: drivers/seg_display.h
 */

#include "drivers/seg_display.h"

#include <stdint.h>

static volatile seg_part_t* SEG_DISPLAYS[_7SEGMENT_DISPLAY_COUNT];

void seg_display_init() {
    for (int i = 0; i < _7SEGMENT_DISPLAY_COUNT; i++) {
        // set address for each display
        SEG_DISPLAYS[i] = (seg_part_t*)(_7SEGMENT_DISPLAY_BASE + i * 0x10);
        seg_display_clear(i);
    }
}

/*
 * 7 segment display set
 *  Note: init before
 *  display_number is 0 to 5
 */
void seg_display_set(uint8_t display_number, uint8_t value) {
    if (display_number > 5 || display_number < 0)
        return;
    else if (value > 9 || value < 0)
        return;
    SEG_DISPLAYS[display_number]->byte = segments[value];
}

/*
 * 7 segment display clear
 *  Note: init before
 *  display_number is 0 to 5
 *  Hi-low, high signal is off. Low signal is on.
 */
void seg_display_clear(uint8_t display_number) {
    if (display_number > 5 || display_number < 0) return;
    SEG_DISPLAYS[display_number]->bot = 1;
    SEG_DISPLAYS[display_number]->bot_left = 1;
    SEG_DISPLAYS[display_number]->bot_right = 1;
    SEG_DISPLAYS[display_number]->mid = 1;
    SEG_DISPLAYS[display_number]->top = 1;
    SEG_DISPLAYS[display_number]->top_left = 1;
    SEG_DISPLAYS[display_number]->top_right = 1;
    SEG_DISPLAYS[display_number]->dot = 1;
}

void seg_display_set_number(uint32_t value) {
    // Limit value to 6 digits
    if (value > 999999)
        value = 999999;

    // Write each digit (right-aligned)
    for (int i = 0; i < _7SEGMENT_DISPLAY_COUNT; i++) {
        if (value > 0) {
            uint8_t digit = value % 10;
            seg_display_set(i, digit);
            value /= 10;
        } else {
            // Clear remaining upper displays
            seg_display_clear(i);
        }
    }
}
