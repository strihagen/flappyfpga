/*
 * led.c
 *
 * Author: Eric Strihagen
 * Date: 2025-10-25
 *
 * Declaration inside drivers/led.h
 * This file contains the driver for the LEDs on the FPGA board.
 */

#include "drivers/led.h"

void set_leds(int led_mask) {
    volatile unsigned int *leds = (volatile unsigned int *)_LED_BASE;
    *leds = led_mask;
}

void increment_leds() {
    volatile unsigned int *leds = (volatile unsigned int *)_LED_BASE;
    *leds = *leds + 1;
}

void init_leds() { set_leds(0); }



