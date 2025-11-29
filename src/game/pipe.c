/* Pipes
 *
 * File: pipe.c
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 * Declaration file: game/pipe.h
*/


#include "game/game.h"
#include "game/pipe.h"
#include "drivers/vga.h"
#include "utils/random.h"

#include <stddef.h>

static uint8_t pipe_bitmap[PIPE_WIDTH * PIPE_HEIGHT];

// Fill bitmap with simple vertical pipe, optional caps
void pipe_bitmap_init() {
    for (int y = 0; y < PIPE_HEIGHT; y++) {
        for (int x = 0; x < PIPE_WIDTH; x++) {
                pipe_bitmap[y * PIPE_WIDTH + x] = 1; // body
        }
    }
}

static pipe_pair_t pipes[MAX_PIPES];


void pipes_init(void) {
    for (int i = 0; i < MAX_PIPES; i++) {
        // 0 to 159
        int gap_y = rand32() % (SCREEN_HEIGHT - PIPE_GAP - GROUND_HEIGHT);

        pipes[i].top.x = 320 + i * PIPE_SPACE;
        pipes[i].top.y = 0;
        pipes[i].top.width = PIPE_WIDTH;
        pipes[i].top.height = gap_y;
        pipes[i].top.bitmap = pipe_bitmap;

        pipes[i].bottom.x = 320 + i * PIPE_SPACE;
        // y = 60 to 219
        pipes[i].bottom.y = gap_y + PIPE_GAP;
        pipes[i].bottom.width = PIPE_WIDTH;
        pipes[i].bottom.height = SCREEN_HEIGHT - (gap_y + PIPE_GAP);
        pipes[i].bottom.bitmap = pipe_bitmap;

        pipes[i].gap_y = gap_y;
    }
}

static bool update = true;
void pipes_update(void) {
    // SLOW DOWN UPDATE
    if (update) {
        update = false;
        return;
    }
    update = true;
    for (int i = 0; i < MAX_PIPES; i++) {
        pipes[i].top.x -= 1;
        pipes[i].bottom.x -= 1;

        // Recycle pipe if it goes off screen
        if (pipes[i].top.x + PIPE_WIDTH < 0) {
            // Find the rightmost pipe to maintain spacing
            int max_x = 0;
            for (int j = 0; j < MAX_PIPES; j++) {
                if (pipes[j].top.x > max_x) max_x = pipes[j].top.x;
            }

            pipes[i].top.x = max_x + PIPE_WIDTH + PIPE_SPACE;
            pipes[i].bottom.x = pipes[i].top.x;

            int gap_y = rand32() % (SCREEN_HEIGHT - PIPE_GAP - GROUND_HEIGHT);
            pipes[i].top.height = gap_y;
            pipes[i].bottom.y = gap_y + PIPE_GAP;
            pipes[i].bottom.height = SCREEN_HEIGHT - (gap_y + PIPE_GAP);
            pipes[i].gap_y = gap_y;
        }
    }
}


pipe_pair_t* pipes_get(int index) {
    if (index < 0 || index >= MAX_PIPES) return NULL;
    return &pipes[index];
}

int pipes_count(void) {
    return MAX_PIPES;
}
