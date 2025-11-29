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
    renderer_clear(vga_color_new(0, 0, 0));
}

/*
void renderer_clear(color_t color) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            vga_set_pixel(x, y, color);
        }
    }
}
*/

void renderer_clear(color_t color) {
    vga_fill_screen(color);
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

/*
void renderer_draw_sprite(const sprite_t *sprite, color_t color) {
    // Disabled for temporary performance increase
    if (!sprite || !sprite->bitmap)
        return;

    for (int y = 0; y < sprite->height; y++) {
        int screen_y = sprite->y + y;
        if (screen_y < 0 || screen_y >= SCREEN_HEIGHT)
            continue; // skip rows offscreen

        for (int x = 0; x < sprite->width; x++) {
            int screen_x = sprite->x + x;
            if (screen_x < 0 || screen_x >= SCREEN_WIDTH)
                continue; // skip columns offscreen

            if (sprite->bitmap[y * sprite->width + x]) { // 1-bit alpha mask
                vga_set_pixel(screen_x, screen_y, color);
            }
        }
    }
}
*/

extern volatile uint8_t* CURRENT_BACK_BUFFER;
void renderer_draw_sprite(const sprite_t *sprite, color_t color) {
    int sw = sprite->width;
    int sh = sprite->height;

    const uint8_t *bitmap = sprite->bitmap;
    uint8_t c = color.value;

    int start_x = sprite->x;
    int start_y = sprite->y;

    // Clip vertically first (cheap)
    int y0 = 0;
    int y1 = sh;

    if (start_y < 0) {
        y0 = -start_y;
    }
    if (start_y + sh > SCREEN_HEIGHT) {
        y1 = SCREEN_HEIGHT - start_y;
    }

    for (int y = y0; y < y1; y++) {
        int screen_y = start_y + y;

        volatile uint8_t *dst = &CURRENT_BACK_BUFFER[screen_y * SCREEN_WIDTH + start_x];
        const uint8_t *src = &bitmap[y * sw];

        int x0 = 0;
        int x1 = sw;

        if (start_x < 0) x0 = -start_x;
        if (start_x + sw > SCREEN_WIDTH) x1 = SCREEN_WIDTH - start_x;

        // Write pixels without calling a function
        for (int x = x0; x < x1; x++) {
            if (src[x]) { // alpha mask: 1 = pixel on
                dst[x] = c;
            }
        }
    }
}

void renderer_present() {
    vga_swap_buffers();
}

