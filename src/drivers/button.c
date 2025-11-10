/* Button
 *
 * File: button.c
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 * Declaration file: drivers/button.h
*/

#include "drivers/button.h"

#include <stdint.h>

uint32_t btn_get(void) {
    volatile uint32_t *btn = (volatile uint32_t*)_BUTTON_BASE;
    return (*btn & 0x1);  // return 1 least significant bit
}


