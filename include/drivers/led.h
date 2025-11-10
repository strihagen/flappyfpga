#ifndef __DRIVERS_LED_H__
#define __DRIVERS_LED_H__


/*
 * LED driver
 *
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 * file: led.h
 *
 * Leds are active low
 */

#include <stdint.h>

#define _LED_BASE 0x04000000

void led_init();
void led_set(const uint32_t led_mask);
void led_increment();

#endif /* __DRIVERS_LED_H__ */
