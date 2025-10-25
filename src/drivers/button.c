/* Button
 *
 * File: button.c
 * Author: Eric Strihagen
 * Date: 2025-10-25
 *
 * Declaration file: drivers/button.h
*/

#include "drivers/button.h"

int get_btn(void) {
    volatile unsigned int *btn = (volatile unsigned int *)_BUTTON_BASE;
    return (*btn & 0x1);  // return 1 least significant bit
}


