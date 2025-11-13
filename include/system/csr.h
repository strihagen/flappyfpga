#ifndef __SYSTEM_CSR_H__
#define __SYSTEM_CSR_H__

/*
 * CSR Control and Status Register
 *
 * Author: Eric Strihagen
 * Date: 2025-11-13
 *
 */

#include "system/hwcounter.h"

#include <stdint.h>

extern void csr_set_mie_mask(uint32_t mie_mask);
extern void csr_clear_mie_mask(uint32_t mie_mask);
extern void csr_set_mstatus_mask(uint32_t mstatus_mask);
extern void csr_clear_mstatus_mask(uint32_t mstatus_mask);

extern uint32_t csr_get_mie(void);
extern uint32_t csr_get_mstatus(void);

extern void csr_read_all_hardware_counters(hwcounters_t *hwc);


void csr_set_mie_bit(uint32_t bit);
void csr_clear_mie_bit(uint32_t bit);
void csr_set_mstatus_bit(uint32_t bit);
void csr_clear_mstatus_bit(uint32_t bit);


#endif /* __SYSTEM_CSR_H__ */




