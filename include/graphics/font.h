#ifndef __GRAPHICS_FONT_H__
#define __GRAPHICS_FONT_H__


/*
 * Font
 *
 * Author: Eric Strihagen
 * Date: 2025-11-29
 *
 * file: font.h
 */

#include "graphics/sprite.h"
#include "drivers/vga.h"

void font_init();
const sprite_t *font_get_char(int c);
void font_render_string(const char *str, int x, int y, color_t color);


void font_render_string_float(const char *str, int x, int baseY, color_t color);
void font_render_string_wave(const char *str, int x, int baseY, color_t color);


#endif /* __GRAPHICS_FONT_H__ */
