/* main.c

    Author: Eric Strihagen
    Date: 2025-11-10

   For copyright and licensing, see file COPYING
*/

#include "drivers/led.h"
#include "drivers/seg_display.h"
#include "drivers/switch.h"
#include "drivers/button.h"
#include "drivers/vga.h"

int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";

int main() {
    // Call vga_test()
    vga_test();

    volatile unsigned int *leds = (volatile unsigned int *)_LED_BASE;

    // Call led_init()
    led_init();
    seg_display_set(1, 0);
    seg_display_set(2, 3);
    seg_display_set(3, 6);
    seg_display_set(4, 7);
    seg_display_set(5, 8);
    seg_display_set(6, 9);

    // Enter a forever loop
    while (*leds != 0xF) {
        led_increment();
    }

    while (1) {
        if (btn_get() == 1) {
            int switch_value = sw_get();
            int switch_time_number =
                (switch_value & 0x3F);  // 6 least significant bits
            int tens = switch_time_number / 10;
            int ones = switch_time_number % 10;
            int corrected_value = (tens << 4) | ones;
            int state =
                (switch_value & 0x300) >> 8;  // Get the state of the switch
            switch (state) {
                case 1:
                    mytime = (mytime & 0xFFFFFF00) | corrected_value;
                    break;
                case 2:
                    mytime = (mytime & 0xFFFF00FF) | (corrected_value << 8);
                    break;
                case 3:
                    mytime = (mytime & 0xFF00FFFF) | (corrected_value << 16);
                    break;
            }
        }
        seg_display_set(1, (mytime >> 0) & 0xF);   // seconds ones
        seg_display_set(2, (mytime >> 4) & 0xF);   // seconds tens
        seg_display_set(3, (mytime >> 8) & 0xF);   // minutes ones
        seg_display_set(4, (mytime >> 12) & 0xF);  // minutes tens
        seg_display_set(5, (mytime >> 16) & 0xF);  // hours ones (if extended)
        seg_display_set(6, (mytime >> 20) & 0xF);  // hours tens (if extended)
    }
}
