/* Switches
 *
 * File: switch.c
 * Author: Eric Strihagen
 * Date: 2025-10-25
 *
 * Declaration file: drivers/switch.h
*/

#include "drivers/switch.h"


int get_sw(void) {
    volatile unsigned int *sw = (volatile unsigned int *)_SWITCH_BASE;
    return (*sw & 0x3FF);  // return 10 least significant bits
}


