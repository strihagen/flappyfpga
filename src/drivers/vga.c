/*
 * VGA driver
 *
 * File: vga.c
 * Author: Eric Strihagen
 * Date: 2025-11-09
 *
 * Declaration file: drivers/vga.h
 *
 * This file handles the internal API for the VGA driver
 * using the Pixel Buffer DMA
 */

#include "drivers/vga.h"
#include "print.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

volatile uint8_t* CURRENT_BACK_BUFFER = NULL;

/* Check if VGA DMA is swapping
 * Returns true if swapping, false if not
 * local function
*/
static bool _check_buffer_swapping() {
    volatile uint32_t* status_addr = DMA_ADDR + 3; // status register
    return (*status_addr & 0x1) != 0;
}

/* Swap front and back buffers
 * local function
*/
static void _swap_buffers() {
    while (_check_buffer_swapping()) {
        // busy wait // Possibly change to clock check or interrupt
    }

    // write to DMA register to trigger swap
    *DMA_ADDR = 0x0;

    if (CURRENT_BACK_BUFFER == BACK_BUFFER_ADDR) {
        CURRENT_BACK_BUFFER = FRONT_BUFFER_ADDR;
    } else {
        CURRENT_BACK_BUFFER = BACK_BUFFER_ADDR;
    }
}

// Initialize VGA buffers
void init_vga() {
    *(DMA_ADDR + 1) = (uint32_t)BACK_BUFFER_ADDR; // Write back buffer address
    CURRENT_BACK_BUFFER = BACK_BUFFER_ADDR;
}

// Create a color (3 bits red, 3 bits green, 2 bits blue)
Color color_new(uint8_t r, uint8_t g, uint8_t b) {
    Color c;
    c.value = ((r & 0x7) << 5) | ((g & 0x7) << 2) | (b & 0x3);
    return c;
}

// Set pixel at (x, y) to color
void set_pixel(int x, int y, Color color) {
    if (CURRENT_BACK_BUFFER == NULL) {
        print("VGA not initialized\n");
        return;
    }

    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        //print("Pixel out of bounds: %d,%d\n", x, y); // NEW PRINT REQUIRED
        print("Pixel out of bounds\n");
        return;
    }

    CURRENT_BACK_BUFFER[y * SCREEN_WIDTH + x] = color.value;
}

// Simple test: fill screen with a color gradient
void test_vga() {
    init_vga();

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            Color c = color_new(x % 8, y % 8, (x+y) % 4);
            set_pixel(x, y, c);
        }
    }

    _swap_buffers();
}


#
