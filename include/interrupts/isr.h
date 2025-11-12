#ifndef __INTERRUPTS_ISR_H__
#define __INTERRUPTS_ISR_H__

/*
 * Interrupt Service Routines
 *
 * Author: Eric Strihagen
 * Date: 2025-11-12
 *
 */

#define INTERRUPT_TIMER_IRQ 16

#include <stdint.h>

void handle_exception ( unsigned arg0, unsigned arg1, unsigned arg2, unsigned arg3, unsigned arg4, unsigned arg5, unsigned mcause, unsigned syscall_num );
void handle_interrupt(unsigned cause);



#endif // __INTERRUPTS_ISR_H__




