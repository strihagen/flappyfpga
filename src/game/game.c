/*  Game Engine
 *
 * File: game.c
 * Author: Eric Strihagen
 * Date: 2025-11-29
 *
 * Declaration file: game/game.h
*/

#include "game/game.h"
#include "graphics/renderer.h"
#include "game/bird.h"
#include "drivers/vga.h"
#include "game/pipe.h"
#include "system/profiler.h"

#include "graphics/font.h"

static game_state_t GAME_STATE;

game_state_t* game_state_get() {
    return &GAME_STATE;
}

void game_init() {
    GAME_STATE.is_running = true;
    GAME_STATE.score = 0;
    GAME_STATE.bird = bird_get();

    for (int pipe = 0; pipe < MAX_PIPES; pipe++) {
        GAME_STATE.pipes[pipe] = pipes_get(pipe);
    }

    GAME_STATE.frame = 0;
    GAME_STATE.mode = GAME_STATE_SPLASH;

    bird_init();

    pipe_bitmap_init();
    pipes_init();

    font_init();
}

static inline bool box_collision(
    int ax, int ay, int aw, int ah,
    int bx, int by, int bw, int bh
) {
    return !( ax + aw <= bx ||
              ax >= bx + bw ||
              ay + ah <= by ||
              ay >= by + bh );
}

// GAME CHECK COLLISIONS - required
void game_check_collisions() {
    // CHECK BIRD GROUND AND SKY COLLISION
    int bird_left   = GAME_STATE.bird->x;
    int bird_top    = GAME_STATE.bird->y;
    int bird_width  = GAME_STATE.bird->width;
    int bird_height = GAME_STATE.bird->height;

    // ---------------------------------------
    // 1. Sky collision
    // ---------------------------------------
    if (bird_top < 0) {
        GAME_STATE.is_running = false;
        return;
    }

    // ---------------------------------------
    // 2. Ground collision
    // ---------------------------------------
    if (bird_top + bird_height >= SCREEN_HEIGHT - GROUND_HEIGHT) {
        GAME_STATE.is_running = false;
        return;
    }

    // CHECK BIRD AND PIPE COLLISION
    // ---------------------------------------
    // 3. Pipe collisions & Scoring
    // ---------------------------------------
    for (int i = 0; i < MAX_PIPES; i++) {

        pipe_pair_t* pipe = GAME_STATE.pipes[i];

        // TOP PIPE
        if (box_collision(
                bird_left, bird_top, bird_width, bird_height,
                pipe->top.x, pipe->top.y, pipe->top.width, pipe->top.height)) {

            GAME_STATE.is_running = false;
            return;
        }

        // BOTTOM PIPE
        if (box_collision(
                bird_left, bird_top, bird_width, bird_height,
                pipe->bottom.x, pipe->bottom.y, pipe->bottom.width, pipe->bottom.height)) {

            GAME_STATE.is_running = false;
            return;
        }

        // --- Score detection ---
        int pipe_right_x = pipe->top.x + pipe->top.width;

        if (!pipe->scored && bird_left > pipe_right_x) {
            GAME_STATE.score++;
            pipe->scored = true;
            print("\n");
            print("SCORE: ");
            print_dec(GAME_STATE.score);
            print("\n");
        }
    }
}


// =============================
// DRAWING HELPER FUNCTIONS
// =============================

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

// =============================
// MAIN GAME DRAW FUNCTION
// =============================

void game_draw() {
    // clear the screen
    PROFILE_BLOCK_AVG("clear", draw_sky());

    // draw pipes
    PROFILE_BLOCK_AVG("pipes", draw_pipes());

    // draw the ground
    PROFILE_BLOCK_AVG("ground", draw_ground());

    PROFILE_BLOCK_AVG("bird", renderer_draw_sprite(bird_get(), vga_color_new(7, 7, 0)));

    GAME_STATE.frame++;
}

