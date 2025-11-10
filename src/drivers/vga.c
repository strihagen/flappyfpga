/*
 * VGA driver
 *
 * File: vga.c
 * Author: Eric Strihagen
 * Date: 2025-11-10
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
 * inlined to remove unnecessary function calls
*/
static inline bool vga_is_swapping() {
    const volatile uint32_t* status_addr = DMA_ADDR + 3; // status register
    return (*status_addr & 0x1) != 0;
}

/* Swap front and back buffers
*/
void vga_swap_buffers() {
    while (vga_is_swapping()) {
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
void vga_init() {
    *(DMA_ADDR + 1) = (uint32_t)BACK_BUFFER_ADDR; // Write back buffer address
    CURRENT_BACK_BUFFER = BACK_BUFFER_ADDR;
}

// Create a color (3 bits red, 3 bits green, 2 bits blue)
color_t vga_color_new(uint8_t r, uint8_t g, uint8_t b) {
    color_t c;
    c.value = ((r & 0x7) << 5) | ((g & 0x7) << 2) | (b & 0x3);
    return c;
}

// Set pixel at (x, y) to color
void vga_set_pixel(uint16_t x, uint16_t y, const color_t color) {
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
void vga_test() {
    vga_init();

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            color_t c = vga_color_new(x % 8, y % 8, (x+y) % 4);
            vga_set_pixel(x, y, c);
        }
    }

    vga_swap_buffers();
}

