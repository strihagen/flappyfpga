/* Switches
 *
 * File: switch.c
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 * Declaration file: drivers/switch.h
*/

#include "drivers/switch.h"

#include <stdint.h>

uint32_t sw_get(void) {
    const volatile uint32_t *sw = (const volatile uint32_t*)_SWITCH_BASE;
    return (*sw & 0x3FF);  // return 10 least significant bits
}


