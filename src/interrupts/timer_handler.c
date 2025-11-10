/* Timer Handler
 *
 * File: timer_handler.c
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 * Declaration file: interrupts/timer_handler.h
*/


#include "drivers/timer.h"

#include <stdint.h>

void timer_interrupt_handler() {
    timer_increment_ticks();
    timer_clear_time_out_flag();
}

