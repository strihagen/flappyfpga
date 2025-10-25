/* 7 Segment Display driver
 *
 * File: segDisplay.c
 * Author: Eric Strihagen
 * Date: 2025-10-25
 *
 * Declaration file: drivers/segDisplay.h
*/

#include <drivers/segDisplay.h>

void set_displays(int display_number, int value) {
    if (display_number > 6 || display_number < 1)
        return;
    else if (value > 9 || value < 0)
        return;
    volatile unsigned int *display =
        (volatile unsigned int *)(_7SEGMENT_DISPLAY_BASE + (display_number - 1) * 0x10);

    *display = segments[value];
}

void init_displays() {
    volatile unsigned int *display = (volatile unsigned int *)_7SEGMENT_DISPLAY_BASE;
    for (int i = 0; i < 6; i++) {
        display[i] = 0xFF;
    }
}
