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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

volatile uint8_t* CURRENT_BACK_BUFFER = NULL;

/* Check if VGA DMA is swapping
 * Returns true if swapping, false if not
 * local function
 * inlined to remove unnecessary function calls
 */
static inline bool vga_is_swapping() {
    return VGA_DMA->status.swap_bit != 0;
}

/* Swap front and back buffers
 */
void vga_swap_buffers() {
    // SWAP Buffer
    if (VGA_DMA->buffer == FRONT_BUFFER_ADDR) {
        CURRENT_BACK_BUFFER = (volatile uint8_t*)BACK_BUFFER_ADDR;
    } else {
        CURRENT_BACK_BUFFER = (volatile uint8_t*)FRONT_BUFFER_ADDR;
    }

    // 3. Tell the hardware "this is the buffer to show next"
    VGA_DMA->back_buffer = (uint32_t)CURRENT_BACK_BUFFER;

    // 4. Request swap: write ANY value to Buffer register
    VGA_DMA->buffer = 0;
    //*DMA_ADDR = 0x0;

    while (vga_is_swapping()) {
        asm volatile("nop");
    }

   if (VGA_DMA->buffer == FRONT_BUFFER_ADDR) {
        CURRENT_BACK_BUFFER = (volatile uint8_t*)BACK_BUFFER_ADDR;
    } else {
        CURRENT_BACK_BUFFER = (volatile uint8_t*)FRONT_BUFFER_ADDR;
    }
}

// Initialize VGA buffers
void vga_init() {
    VGA_DMA->back_buffer = BACK_BUFFER_ADDR;
    CURRENT_BACK_BUFFER = (volatile uint8_t*)BACK_BUFFER_ADDR;
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
        // print("Pixel out of bounds: %d,%d\n", x, y); // NEW PRINT REQUIRED
        print("Pixel out of bounds\n");
        return;
    }

    CURRENT_BACK_BUFFER[y * SCREEN_WIDTH + x] = color.value;
}

void vga_set_pixel_fast(uint16_t x, uint16_t y, const color_t color) {
    CURRENT_BACK_BUFFER[y * SCREEN_WIDTH + x] = color.value;
}

void vga_fill_row_fast(uint16_t y, const color_t color) {
    uint32_t packed = pack_color8(color.value);

    volatile uint32_t*row = (volatile uint32_t*)&CURRENT_BACK_BUFFER[y * SCREEN_WIDTH];

    for (int i = 0; i < (SCREEN_WIDTH / 4); i += 4) {
        row[i] = packed;
        row[i+1] = packed;
        row[i+2] = packed;
        row[i+3] = packed;

    }
}

void vga_fill_screen(const color_t color) {
    uint32_t packed = pack_color8(color.value);

    volatile uint32_t* p32 = (volatile uint32_t*)CURRENT_BACK_BUFFER;

    // Write 4 pixels at a time
    for (size_t i = 0; i < (SCREEN_SIZE / 4); i += 4) {
        p32[i] = packed;
        p32[i + 1] = packed;
        p32[i + 2] = packed;
        p32[i + 3] = packed;
    }
}

// Simple test: fill screen with a color gradient
void vga_test() {
    vga_init();

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            color_t c = vga_color_new(x % 8, y % 8, (x + y) % 4);
            vga_set_pixel(x, y, c);
        }
    }

    vga_swap_buffers();
}
