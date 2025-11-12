/* System
 *
 * File: system.c
 * Author: Eric Strihagen
 * Date: 2025-11-12
 *
 * Declaration file: system/system.h
*/


#include "system/csr.h"


/* IRQ enable
* @param irq_num: irq number
* @returns: void
* @brief: enable irq number 0-31
* */
void system_enable_irq(uint32_t irq_num) {
    csr_set_mie_bit(irq_num);
}

/* IRQ disable
* @param irq_num: irq number
* @returns: void
* @brief: disable irq number 0-31
* */
void system_disable_irq(uint32_t irq_num) {
    csr_clear_mie_bit(irq_num);
}

/* Enable MIE interrupts */
void system_enable_mie_interrupts() {
    csr_set_mstatus_bit(3);
}

/* Disable MIE interrupts */
void system_disable_mie_interrupts() {
    csr_clear_mstatus_bit(3);
}

