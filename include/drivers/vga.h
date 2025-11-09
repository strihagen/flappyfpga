#ifndef __DRIVERS_VGA_H__
#define __DRIVERS_VGA_H__

/*
 * VGA driver
 *
 * Author: Eric Strihagen
 * Date: 2025-11-08
 *
 */

#include <stdint.h>
#include <stdbool.h>


#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#define FRONT_BUFFER_ADDR ((volatile uint8_t*)0x08000000)
#define BACK_BUFFER_ADDR  ((volatile uint8_t*)(0x08000000 + SCREEN_WIDTH * SCREEN_HEIGHT))
#define DMA_ADDR          ((volatile uint32_t*)0x04000100)


// Color
typedef struct {
    uint8_t value;
} Color;


// Initialize VGA
void init_vga();

// Create a color (3 bits red, 3 bits green, 2 bits blue)
Color color_new(uint8_t r, uint8_t g, uint8_t b);

// Set pixel at (x, y) to color
void set_pixel(int x, int y, Color color);

// Simple test: fill screen with a color gradient
void test_vga();

#endif
