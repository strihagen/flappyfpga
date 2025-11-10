/*
 * led.c
 *
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 * Declaration inside drivers/led.h
 * This file contains the driver for the LEDs on the FPGA board.
 */

#include "drivers/led.h"

#include <stdint.h>

void led_set(const uint32_t led_mask) {
    volatile unsigned int *leds = (volatile unsigned int *)_LED_BASE;
    *leds = led_mask;
}

void led_increment() {
    volatile unsigned int *leds = (volatile unsigned int *)_LED_BASE;
    *leds = *leds + 1;
}

void led_init() { led_set(0); }



