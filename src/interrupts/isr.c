/*
 * Interrupt Service Routines
 *
 * File: isr.c
 * Author: Eric Strihagen
 * Date: 2025-11-12
 *
 * Declaration file: interrupts/isr.h
*/


#include "interrupts/isr.h"
#include "interrupts/timer_handler.h"

#include "print.h"


/* function: handle_exception
   Description: This code handles an exception. */
void handle_exception ( unsigned arg0, unsigned arg1, unsigned arg2, unsigned arg3, unsigned arg4, unsigned arg5, unsigned mcause, unsigned syscall_num )
{
  switch (mcause)
    {
    case 0:
      print("\n[EXCEPTION] Instruction address misalignment. ");
      break;
    case 2:
      print("\n[EXCEPTION] Illegal instruction. ");
      break;
    case 11:
      if (syscall_num == 4)
	print((char*) arg0);
      if (syscall_num == 11)
	printc(arg0);
      return ;
      break;
    default:
      print("\n[EXCEPTION] Unknown error. ");
      break;
    }

  print("Exception Address: ");
  print_hex32(arg0); printc('\n');
  while (1);
}


/* Interrupt Handler
 * Description: This code handles an interrupt.
 * Param cause: The interrupt cause.
*/
void handle_interrupt(unsigned cause) {
    switch (cause) {
        case INTERRUPT_TIMER_IRQ:
            timer_interrupt_handler();
            break;
        default:
            print("\n[INTERRUPT] Unknown interrupt. ");
            break;
    }
}

