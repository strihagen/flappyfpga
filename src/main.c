/* main.c

   This file written 2024 by Artur Podobas and Pedro Antunes

   For copyright and licensing, see file COPYING */

/* Below functions are external and found in other files. */

int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";

void set_leds(int led_mask) {
    volatile unsigned int *leds = (volatile unsigned int *)0x04000000;
    *leds = led_mask;
}

void increment_leds() {
    volatile unsigned int *leds = (volatile unsigned int *)0x04000000;
    *leds = *leds + 1;
}

void init_leds() { set_leds(0); }

void set_displays(int display_number, int value) {
    if (display_number > 6 || display_number < 1)
        return;
    else if (value > 9 || value < 0)
        return;
    volatile unsigned int *display =
        (volatile unsigned int *)(0x4000050 + (display_number - 1) * 0x10);

    // Segment encoding: 0 = on, 1 = off
    static const unsigned int segments[10] = {
        0b11000000,  // 0
        0b11111001,  // 1
        0b10100100,  // 2
        0b10110000,  // 3
        0b10011001,  // 4
        0b10010010,  // 5
        0b10000010,  // 6
        0b11111000,  // 7
        0b10000000,  // 8
        0b10010000   // 9
    };

    *display = segments[value];
}

void init_displays() {
    volatile unsigned int *display = (volatile unsigned int *)0x04000050;
    for (int i = 0; i < 6; i++) {
        display[i] = 0xFF;
    }
}

int get_sw(void) {
    volatile unsigned int *sw = (volatile unsigned int *)0x04000010;
    return (*sw & 0x3FF);  // return 10 least significant bits
}

int get_btn(void) {
    volatile unsigned int *btn = (volatile unsigned int *)0x040000d0;
    return (*btn & 0x1);  // return 1 least significant bit
}

void init_vga(void) {
    volatile unsigned int *vga = (volatile unsigned int *)0x04000050;
    for (int i = 0; i < 6; i++) {
        vga[i] = 0xFF;
    }
}

/* Add your code here for initializing interrupts. */
void labinit(void) {}

/* Your code goes into main as well as any needed functions. */
int main() {
    // Call labinit()
    init_vga();
    labinit();
    volatile unsigned int *leds = (volatile unsigned int *)0x04000000;

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
