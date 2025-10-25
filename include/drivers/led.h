#ifndef __DRIVERS_LED_H__
#define __DRIVERS_LED_H__

/* led.h */
#define _LED_BASE 0x04000000

void set_leds(int led_mask);
void increment_leds();
void init_leds();

#endif /* __DRIVERS_LED_H__ */
