/*
    * csr_asm.S
    *
    * Author: Eric Strihagen
    * Date: 2025-11-13
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
    csrs mstatus, a0
    jr ra

.globl csr_clear_mstatus_mask
csr_clear_mstatus_mask:
    csrc mstatus, a0
    jr ra

.globl csr_get_mie
csr_get_mie:
    # Read MIE into a0
    csrr a0, mie
    # Return to caller
    jr ra

.globl csr_get_mstatus
csr_get_mstatus:
    # Read MSTATUS into a0
    csrr a0, mstatus
    # Return to caller
    jr ra



/*
    Hardware Counters
    The loops required to safely read 64-bit counters on 32-bit riscv
*/
.globl csr_read_all_hardware_counters
csr_read_all_hardware_counters:
    # a0 = pointer to struct hwcounters_t

    # --- mcycle (64-bit safe) ----
1:
    csrr  t1, mcycleh
    csrr  t0, mcycle
    csrr  t2, mcycleh
    bne   t1, t2, 1b
    sw    t0, 0(a0)
    sw    t1, 4(a0)

    # --- minstret (64-bit safe) ----
2:
    csrr  t1, minstreth
    csrr  t0, minstret
    csrr  t2, minstreth
    bne   t1, t2, 2b
    sw    t0, 8(a0)
    sw    t1, 12(a0)

    # --- mhpmcounter3 ----
3:
    csrr  t1, mhpmcounter3h
    csrr  t0, mhpmcounter3
    csrr  t2, mhpmcounter3h
    bne   t1, t2, 3b
    sw    t0, 16(a0)
    sw    t1, 20(a0)

    # --- mhpmcounter4 ----
4:
    csrr  t1, mhpmcounter4h
    csrr  t0, mhpmcounter4
    csrr  t2, mhpmcounter4h
    bne   t1, t2, 4b
    sw    t0, 24(a0)
    sw    t1, 28(a0)

    # --- mhpmcounter5 ----
5:
    csrr  t1, mhpmcounter5h
    csrr  t0, mhpmcounter5
    csrr  t2, mhpmcounter5h
    bne   t1, t2, 5b
    sw    t0, 32(a0)
    sw    t1, 36(a0)

    # --- mhpmcounter6 ----
6:
    csrr  t1, mhpmcounter6h
    csrr  t0, mhpmcounter6
    csrr  t2, mhpmcounter6h
    bne   t1, t2, 6b
    sw    t0, 40(a0)
    sw    t1, 44(a0)

    # --- mhpmcounter7 ----
7:
    csrr  t1, mhpmcounter7h
    csrr  t0, mhpmcounter7
    csrr  t2, mhpmcounter7h
    bne   t1, t2, 7b
    sw    t0, 48(a0)
    sw    t1, 52(a0)

    # --- mhpmcounter8 ----
8:
    csrr  t1, mhpmcounter8h
    csrr  t0, mhpmcounter8
    csrr  t2, mhpmcounter8h
    bne   t1, t2, 8b
    sw    t0, 56(a0)
    sw    t1, 60(a0)

    # --- mhpmcounter9 ----
9:
    csrr  t1, mhpmcounter9h
    csrr  t0, mhpmcounter9
    csrr  t2, mhpmcounter9h
    bne   t1, t2, 9b
    sw    t0, 64(a0)
    sw    t1, 68(a0)

    jr ra
