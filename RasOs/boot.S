// AArch64 mode
// To keep this in the first portion of the binary.
.section ".text.boot"
 
#include "Include\sysregs.h"

// Make _start global.
.globl _start
 
//.org 0x80000
// Entry point for the kernel. Registers are not defined as in AArch32.
_start:
    // read cpu id, stop slave cores
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, _el1_entry
    b       _halt_cpu
    // cpu id > 0, stop
_halt_cpu:  
	wfi
    b       _halt_cpu

_el1_entry:  // cpu id == 0
    // set stack before our code
    ldr x0, =SCTLR_CONTROL_VALUES
    msr sctlr_el1, x0

    ldr x0, =HCR_VALUE
    msr hcr_el2, x0

    ldr x0, =SCR_VALUE
    msr scr_el3, x0

    ldr x0, =SPSR_VALUE
    msr spsr_el3, x0

    adr x0, _kernel_start
    msr elr_el3, x0

    eret

 _kernel_start:
    // clear bss
    ldr     x0, =__bss_start
    ldr     x1, =__bss_size
	sub     x1, x1, x0
    bl      _memzero

    mov     sp, #0x10000
    // jump to C code, should not return
	bl      kernel_main
    