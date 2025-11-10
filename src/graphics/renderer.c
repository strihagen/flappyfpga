/* Graphics renderer API
 *
 * File: renderer.c
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 * Declaration file: graphics/renderer.h
*/


#include "graphics/renderer.h"
#include "drivers/vga.h"

void renderer_init() {
    vga_init();
    renderer_clear(vga_color_new(0, 0, 0)); // black screen
    vga_swap_buffers();
}

void renderer_clear(color_t color) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            vga_set_pixel(x, y, color);
        }
    }
}

void renderer_fill_rect(int x, int y, int w, int h, color_t color) {
    for (int j = y; j < y + h; j++) {
        for (int i = x; i < x + w; i++) {
            if (i >= 0 && i < SCREEN_WIDTH && j >= 0 && j < SCREEN_HEIGHT)
                vga_set_pixel(i, j, color);
        }
    }
}

void renderer_draw_rect(int x, int y, int w, int h, color_t color) {
    for (int i = x; i < x + w; i++) {
        vga_set_pixel(i, y, color);
        vga_set_pixel(i, y + h - 1, color);
    }
    for (int j = y; j < y + h; j++) {
        vga_set_pixel(x, j, color);
        vga_set_pixel(x + w - 1, j, color);
    }
}

void renderer_draw_sprite(const sprite_t *sprite, color_t color) {
    if (!sprite || !sprite->bitmap)
        return;

    for (int y = 0; y < sprite->height; y++) {
        for (int x = 0; x < sprite->width; x++) {
            uint8_t pixel = sprite->bitmap[y * sprite->width + x];
            if (pixel) { // simple 1-bit alpha mask
                vga_set_pixel(sprite->x + x, sprite->y + y, color);
            }
        }
    }
}

void renderer_present() {
    vga_swap_buffers();
}

