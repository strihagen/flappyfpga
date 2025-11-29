#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__


/*
 * Game Engine
 *
 * Author: Eric Strihagen
 * Date: 2025-11-29
 *
 * file: game.h
 *
 */

#include "graphics/sprite.h"
#include "game/pipe.h"

#include <stdbool.h>

#define GROUND_HEIGHT 20

typedef enum {
    GAME_STATE_SPLASH,
    GAME_STATE_PLAYING,
    GAME_STATE_GAME_OVER
} game_mode_t;


typedef struct {
    bool is_running;
    int score;
    const sprite_t* bird;
    pipe_pair_t* pipes[MAX_PIPES];
    uint32_t frame;
    game_mode_t mode;
} game_state_t;

game_state_t* game_state_get();
void game_init();
void game_reset();
void game_check_collisions();
void game_draw();


#endif /* __GAME_ENGINE_H__ */
