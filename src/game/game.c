/*  Game Engine
 *
 * File: game.c
 * Author: Eric Strihagen
 * Date: 2025-11-28
 *
 * Declaration file: game/game.h
*/

#include "game/game.h"
#include "graphics/renderer.h"
#include "game/bird.h"
#include "drivers/vga.h"
#include "game/pipe.h"
#include "system/profiler.h"

static inline void draw_sky() {
    for (int i = 0; i < SCREEN_HEIGHT - GROUND_HEIGHT; i++) {
        vga_fill_row_fast(i, vga_color_new(2, 5, 3));
    }
}

static inline void draw_ground() {
    for (int i = SCREEN_HEIGHT - GROUND_HEIGHT; i < SCREEN_HEIGHT; i++) {
        vga_fill_row_fast(i, vga_color_new(0, 3, 0));
    }
}

static inline void draw_pipes() {
    for (int i = 0; i < pipes_count(); i++) {
        renderer_draw_sprite(&pipes_get(i)->top, vga_color_new(0,7,0));
        renderer_draw_sprite(&pipes_get(i)->bottom, vga_color_new(0,7,0));
    }
}

void game_draw() {
    // clear the screen
    //PROFILE_BLOCK_AVG("clear", renderer_clear(vga_color_new(2, 5, 3)));
    PROFILE_BLOCK_AVG("clear", draw_sky());
    //renderer_clear(vga_color_new(2, 5, 3)); // sky blue

    // draw the bird
    //PROFILE_BLOCK_AVG("bird", renderer_draw_sprite(bird_get(), vga_color_new(7, 7, 0)));
    //renderer_draw_sprite(bird_get(), vga_color_new(7, 7, 0)); // bright yellow

    // draw pipes
    PROFILE_BLOCK_AVG("pipes", draw_pipes());

    // draw the ground
    //renderer_fill_rect(0, SCREEN_HEIGHT - GROUND_HEIGHT, SCREEN_WIDTH, GROUND_HEIGHT, vga_color_new(0, 3, 0));
    PROFILE_BLOCK_AVG("ground", draw_ground());
    //

    PROFILE_BLOCK_AVG("bird", renderer_draw_sprite(bird_get(), vga_color_new(7, 7, 0)));

    renderer_present();
}

