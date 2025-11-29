/* main.c

    Author: Eric Strihagen
    Date: 2025-11-29

   For copyright and licensing, see file COPYING
*/



// IO
#include "drivers/button.h"
#include "print.h"

// Game
#include "game/bird.h"
#include "game/game.h"
#include "game/pipe.h"
#include "graphics/renderer.h"
#include "graphics/font.h"

// System
#include "system/profiler.h"

#include <stdbool.h>

int main() {

    renderer_init();
    game_init();

    game_state_t* GAME_STATE = game_state_get();

    print("[FlappyFPGA] Initialized\n");

    //system_enable_irq(18);
    static int bird_jump_counter = 0;

    while (1) {
        int btn = btn_get();

        switch (GAME_STATE->mode) {

            // ------------------------
            // Splash Screen
            // ------------------------
            case GAME_STATE_SPLASH:
                game_draw();  // draw splash
                font_render_string_float("FLAPPY FPGA", 100, 100, vga_color_new(7,7,4));
                renderer_present();

                if (btn) {
                    GAME_STATE->mode = GAME_STATE_PLAYING;
                    bird_init();
                    pipes_init();
                    GAME_STATE->score = 0;
                    GAME_STATE->is_running = true;
                }
                break;

            // ------------------------
            // Playing
            // ------------------------
            case GAME_STATE_PLAYING:
                // Update bird jump
                if (btn && bird_jump_counter == 0) {
                    bird_jump_counter = 10; // frames of jump
                }

                // Apply bird jump / gravity
                if (bird_jump_counter > 0) {
                    bird_update(-2);
                    bird_jump_counter--;
                } else {
                    bird_update(2); // gravity
                }

                pipes_update();

                // Check collisions + scoring
                game_check_collisions();

                // If bird died, switch to game over
                if (!GAME_STATE->is_running) {
                    GAME_STATE->mode = GAME_STATE_GAME_OVER;
                }

                game_draw();
                renderer_present();
                break;

            // ------------------------
            // Game Over
            // ------------------------
            case GAME_STATE_GAME_OVER:
                game_draw();
                font_render_string_wave("GAME OVER", 90, 100, vga_color_new(7,0,0));
                renderer_present();

                // Wait for button to reset
                if (btn) {
                    game_init();
                    GAME_STATE->mode = GAME_STATE_SPLASH;
                }
                break;
        }

        profiler_fps();
    }
}
