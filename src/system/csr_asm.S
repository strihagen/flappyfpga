/*
    * csr_asm.S
    *
    * Author: Eric Strihagen
    * Date: 2025-11-12
    * Description: Assembly code for setting and getting CSRs
*/



.section .text
.align 2

.globl csr_set_mie_mask
csr_set_mie_mask:
    csrs mie, a0 // Enable interrupt
    jr ra

.globl csr_clear_mie_mask
csr_clear_mie_mask:
    csrc mie, a0 // Disable interrupt
    jr ra

.globl csr_set_mstatus_mask
csr_set_mstatus_mask:
    csrsi mstatus, 3 // Enable interrupts, enable MIE
    jr ra

.globl csr_clear_mstatus_mask
csr_clear_mstatus_mask:
    csrci mstatus, 3 // Disable interrupts
    jr ra


.globl csr_get_mie
csr_get_mie:
    # Save caller-saved registers if needed (optional for simple cases)
    # Read MIE into a0
    csrr a0, mie

    # Return to caller
    jr ra

.globl csr_get_mstatus
csr_get_mstatus:
    # Save caller-saved registers if needed (optional for simple cases)
    # Read MSTATUS into a0
    csrr a0, mstatus

    # Return to caller
    jr ra
