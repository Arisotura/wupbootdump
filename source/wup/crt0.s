.arch armv5te
.cpu arm926ej-s

.section ".crt0","ax"

.arm
.align 2

.global _start
_start:
	msr cpsr_c, #0xD0
	ldr sp, =__sp_usr

	ldr r0, =__bss_start__
	ldr r1, =__bss_end__
	bl clear_mem

	ldr r3, =WUP_Init
    blx r3

	ldr r3, =main
	blx r3
	b halt_loop

halt_loop:
	b halt_loop


clear_mem:
    add r0, r0, #3
    bic r0, r0, #3
    mov r2, #0
    mov r3, #0
    mov r4, #0
    mov r5, #0
_clear_loop:
    stmia r0!, {r2-r5}
    cmp r0, r1
    blt _clear_loop
    bx lr
