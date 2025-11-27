#ifndef __GRAPHICS_RENDERER_H__
#define __GRAPHICS_RENDERER_H__

/*
 * Renderer API
 *
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 * file: renderer.h
 *
 * This file contains the Higher-level graphics API
 */

#include "drivers/vga.h"
#include "graphics/sprite.h"

// Initialize renderer (sets up VGA and clears screen)
void renderer_init();

// Clear entire screen with a single color
void renderer_clear(color_t color);

// Draw filled rectangle (used for pipes, ground, etc.)
void renderer_fill_rect(int x, int y, int w, int h, color_t color);

// Draw outline rectangle (for debugging / hitboxes)
void renderer_draw_rect(int x, int y, int w, int h, color_t color);

// Draw sprite bitmap (1-bit alpha or 8-bit indexed)
void renderer_draw_sprite(const sprite_t *sprite, color_t color);

// Present the current frame (swap buffers)
void renderer_present();




#endif /* __GRAPHICS_RENDERER_H__ */
