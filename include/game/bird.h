#ifndef __GAME_BIRD_H__
#define __GAME_BIRD_H__


/*  Bird
 *
 * File: bird.h
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
*/


#include "graphics/sprite.h"

void bird_init(void);

void bird_update(int velocity);

const sprite_t *bird_get(void);

#endif /* __GAME_BIRD_H__ */
