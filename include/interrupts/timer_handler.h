#ifndef __INTERRUPTS_TIMER_HANDLER_H__
#define __INTERRUPTS_TIMER_HANDLER_H__

/*
 * Timer handler
 *
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 */
#include <stdint.h>

#define TIMER_INTERRUPT_ID 16

void timer_interrupt_handler();


#endif /* __INTERRUPTS_TIMER_HANDLER_H__ */
