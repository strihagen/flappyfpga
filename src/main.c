/* main.c

    Author: Eric Strihagen
    Date: 2025-11-13

   For copyright and licensing, see file COPYING
*/



// IO
#include "drivers/button.h"
/*
#include "drivers/led.h"
#include "drivers/seg_display.h"
#include "drivers/switch.h"
#include "drivers/timer.h"
*/
#include "print.h"

// Game
#include "game/bird.h"
#include "game/game.h"
#include "game/pipe.h"
#include "graphics/renderer.h"

// Interrupts
#include "interrupts/isr.h"

// System
#include "system/system.h"
//#include "system/csr.h"
#include "system/profiler.h"

int main() {

    renderer_init();
    bird_init();
    pipe_bitmap_init();
    pipes_init();
    print("[FlappyFPGA] Initialized\n");

    //system_enable_irq(18);
    static int bird_logic_jump = 0;
    while (1) {
        /*
        PROFILE_BLOCK_CYCLES("bird_update", bird_update(1));
        PROFILE_BLOCK_CYCLES("pipes_update", pipes_update());
        PROFILE_BLOCK_CYCLES("game_draw", game_draw());
        */
        bird_update(2);
        pipes_update();
        game_draw();
        profiler_fps();
        if (bird_logic_jump == 0 && btn_get() == 1) {
            bird_logic_jump = 10;
            continue;
        }
        for (int i = 0; i < bird_logic_jump; i++) {
            bird_update(-2);
            bird_logic_jump--;
        }

    }
}
