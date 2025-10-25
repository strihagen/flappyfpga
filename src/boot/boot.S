.data
.align 2
welcome_msg: .asciz "================================================\n===== RISC-V Boot-Up Process Now Complete ======\n================================================\n"

.section .text
.align 2
.globl _start

/* This is where the application starts */
_start:
	// Set the stack point to somewhere free in the main memory
	csrw mie, x0
	la sp, _stack_end
	la gp, __global_pointer
	la a0, welcome_msg
	li a7,4
	ecall
	// Jump to main
	jal main

loop:	j loop
