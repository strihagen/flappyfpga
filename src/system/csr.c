/* CSR Control Status Register
 *
 * File: csr.c
 * Author: Eric Strihagen
 * Date: 2025-11-12
 *
 * Declaration file: system/csr.h
*/

#include "system/csr.h"

/*
 * CSR Functions
*/


/*
 * CSR Set mie BIT
* @param: bit
* @brief: Sets a bit in the mie register
* @note: The mie register is 32-bits wide
*/
void csr_set_mie_bit(uint32_t bit) {
    csr_set_mie_mask(1 << bit);
}

/*
 * CSR Clear mie BIT
* @param: bit
* @brief: Clears a bit in the mie register
* @note: The mie register is 32-bits wide
*/
void csr_clear_mie_bit(uint32_t bit) {
    csr_clear_mie_mask(1 << bit);
}

/*
 * CSR Set mstatus BIT
* @param: bit
* @brief: Sets a bit in the mstatus register
* @note: The mstatus register is 32-bits wide
*/
void csr_set_mstatus_bit(uint32_t bit) {
    csr_set_mstatus_mask(1 << bit);
}

/*
 * CSR Clear mstatus BIT
* @param: bit
* @brief: Clears a bit in the mstatus register
* @note: The mstatus register is 32-bits wide
*/
void csr_clear_mstatus_bit(uint32_t bit) {
    csr_clear_mstatus_mask(1 << bit);
}
