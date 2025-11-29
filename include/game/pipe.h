#ifndef __GAME_PIPE_H__
#define __GAME_PIPE_H__

/*
 * Pipe sprite
 *
 * Author: Eric Strihagen
 * Date: 2025-11-29
 *
 */


#include "graphics/sprite.h"
#include "game/game.h"

#include <stdbool.h>

#define MAX_PIPES 4
#define PIPE_WIDTH  20
#define PIPE_HEIGHT 240 - GROUND_HEIGHT
#define PIPE_GAP    60
#define PIPE_SPACE  100

typedef struct {
    sprite_t top;    // top pipe sprite
    sprite_t bottom; // bottom pipe sprite
    int gap_y;       // vertical position of the gap
    bool scored;
} pipe_pair_t;

void pipes_init(void);
void pipe_bitmap_init(void);
void pipes_update(void);
pipe_pair_t* pipes_get(int index);
int pipes_count(void);  // how many active pipes

#endif /* __GAME_PIPE_H__ */

