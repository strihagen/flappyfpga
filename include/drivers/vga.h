#ifndef __DRIVERS_VGA_H__
#define __DRIVERS_VGA_H__

/*
 * VGA driver
 *
 * Author: Eric Strihagen
 * Date: 2025-11-28
 *
 */

#include <stdint.h>
#include <stdbool.h>


#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
#define SCREEN_SIZE   (SCREEN_WIDTH * SCREEN_HEIGHT)

#define FRONT_BUFFER_ADDR (0x08000000)
#define BACK_BUFFER_ADDR  (0x08000000 + SCREEN_SIZE)
#define DMA_ADDR          ((volatile uint32_t*)0x04000100)

typedef struct {
    volatile uint32_t swap_bit : 1;
    volatile uint32_t address_mode : 1;
    volatile uint32_t color_mode : 4;
    volatile uint32_t x_addr_cord_width : 16;
    volatile uint32_t y_addr_cord_width : 16;
} vga_dma_reg_status_t;


typedef struct __attribute__ ((packed)) __attribute__ ((aligned (4))){
    volatile uint32_t buffer;      // buffer address
    volatile uint32_t back_buffer; // back buffer address
    volatile uint16_t resolution_x;
    volatile uint16_t resolution_y;
    volatile vga_dma_reg_status_t status;
} vga_dma_reg_t;

static volatile vga_dma_reg_t* const VGA_DMA = (volatile vga_dma_reg_t*)DMA_ADDR;

/*  Color struct
 *   8 bits
    * Red: 3 bits MSB
    * Green: 3 bits
    * Blue: 2 bits LSB
*/
typedef struct {
    uint8_t value;
} color_t;

static inline uint32_t pack_color8(uint8_t c) {
    return (uint32_t)c * 0x01010101;
}

// Initialize VGA
void vga_init();

// Create a color (3 bits red, 3 bits green, 2 bits blue)
color_t vga_color_new(uint8_t r, uint8_t g, uint8_t b);

// Set pixel at (x, y) to color
void vga_set_pixel(uint16_t x, uint16_t y, const color_t color);

// Swap front and back buffers
void vga_swap_buffers();

void vga_fill_screen(const color_t color);

// Simple test: fill screen with a color gradient
void vga_test();

void vga_fill_row_fast(uint16_t y, const color_t color);

#endif
