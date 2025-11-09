/* main.c

    Author: Eric Strihagen
    Date: 2025-10-25

   For copyright and licensing, see file COPYING */

#include "drivers/led.h"
#include "drivers/segDisplay.h"
#include "drivers/switch.h"
#include "drivers/button.h"
#include "drivers/vga.h"

int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";

int main() {
    // Call test_vga()
    test_vga();

    volatile unsigned int *leds = (volatile unsigned int *)_LED_BASE;

    // Call init_leds()
    init_leds();
    set_displays(1, 0);
    set_displays(2, 3);
    set_displays(3, 6);
    set_displays(4, 7);
    set_displays(5, 8);
    set_displays(6, 9);

    // Enter a forever loop
    while (*leds != 0xF) {
        increment_leds();
    }

    while (1) {
        if (get_btn() == 1) {
            int switch_value = get_sw();
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
        set_displays(1, (mytime >> 0) & 0xF);   // seconds ones
        set_displays(2, (mytime >> 4) & 0xF);   // seconds tens
        set_displays(3, (mytime >> 8) & 0xF);   // minutes ones
        set_displays(4, (mytime >> 12) & 0xF);  // minutes tens
        set_displays(5, (mytime >> 16) & 0xF);  // hours ones (if extended)
        set_displays(6, (mytime >> 20) & 0xF);  // hours tens (if extended)
    }
}
