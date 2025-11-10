#ifndef __ISR_H__
#define __ISR_H__

/*
 * Interrupt Service Routines
 *
 * Author: Eric Strihagen
 * Date: 2025-11-10
 *
 */



extern void enable_interrupts(void);

void handle_exception ( unsigned arg0, unsigned arg1, unsigned arg2, unsigned arg3, unsigned arg4, unsigned arg5, unsigned mcause, unsigned syscall_num );
void handle_interrupt(unsigned cause);



#endif // __ISR_H__




