/*  Bird
 *
 * File: bird.c
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 * Declaration file: game/bird.h
*/

#include "game/game.h"
#include "drivers/vga.h"
#include "graphics/sprite.h"

#define BIRD_WIDTH  8
#define BIRD_HEIGHT 8


// bird sprite
static sprite_t bird;


// 1-bit mask (1 = pixel on, 0 = transparent)
static const uint8_t bird_bitmap[BIRD_WIDTH * BIRD_HEIGHT] = {
    0,0,0,1,0,0,0,0,   // head
    0,0,1,1,1,0,0,0,   // upper body
    0,1,1,1,1,1,0,0,   // body
    1,1,1,1,1,1,1,0,   // wings / tail
    0,1,1,1,1,1,0,0,   // lower body
    0,0,1,1,1,0,0,0,   // lower tail
    0,0,0,1,0,0,0,0,   // tail tip
    0,0,0,0,0,0,0,0    // padding
};



void bird_init() {
    bird.x = 50;
    bird.y = 100;
    bird.width = BIRD_WIDTH;
    bird.height = BIRD_HEIGHT;
    bird.bitmap = bird_bitmap;
}


void bird_update(int velocity) {
    bird.y += velocity;

    // keep bird on screen
    if (bird.y > SCREEN_HEIGHT - GROUND_HEIGHT - bird.height) {
        bird.y = SCREEN_HEIGHT - GROUND_HEIGHT - bird.height;
    }

    if (bird.y + bird.height >= SCREEN_HEIGHT)
        bird.y = SCREEN_HEIGHT - bird.height;
}

const sprite_t *bird_get() {
    return &bird;
}

