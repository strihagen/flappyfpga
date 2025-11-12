#ifndef __SYSTEM_H__
#define __SYSTEM_H__


/*
 * System
 *
 * Author: Eric Strihagen
 * Date: 2025-11-12
 *
 * file: system.h
 *
 *
 */

#include <stdint.h>

void system_enable_irq(uint32_t irq_num);
void system_disable_irq(uint32_t irq_num);
void system_enable_mie_interrupts(void);
void system_disable_mie_interrupts(void);



#endif /* __SYSTEM_H__ */
