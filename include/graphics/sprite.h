#ifndef __GAME_SPRITE_H__
#define __GAME_SPRITE_H__


/*
 * Game Sprites
 *
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 *
 * file: sprite.h
 *
 */

#include <stdint.h>

typedef struct {
    int x, y;
    int width, height;
    const uint8_t *bitmap; // optional sprite bitmap
} sprite_t;


#endif /* __GAME_SPRITE_H__ */

