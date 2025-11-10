#ifndef __DRIVERS_VGA_H__
#define __DRIVERS_VGA_H__

/*
 * VGA driver
 *
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 */

#include <stdint.h>
#include <stdbool.h>


#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#define FRONT_BUFFER_ADDR ((volatile uint8_t*)0x08000000)
#define BACK_BUFFER_ADDR  ((volatile uint8_t*)(0x08000000 + SCREEN_WIDTH * SCREEN_HEIGHT))
#define DMA_ADDR          ((volatile uint32_t*)0x04000100)


/*  Color struct
 *   8 bits
    * Red: 3 bits MSB
    * Green: 3 bits
    * Blue: 2 bits LSB
*/
typedef struct {
    uint8_t value;
} color_t;


// Initialize VGA
void vga_init();

// Create a color (3 bits red, 3 bits green, 2 bits blue)
color_t vga_color_new(uint8_t r, uint8_t g, uint8_t b);

// Set pixel at (x, y) to color
void vga_set_pixel(uint16_t x, uint16_t y, const color_t color);

// Swap front and back buffers
void vga_swap_buffers();

// Simple test: fill screen with a color gradient
void vga_test();

#endif
