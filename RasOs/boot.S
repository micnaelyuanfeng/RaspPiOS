.section ".text.boot"

#include "include/sysSetting.h"

.global start
start:
    mrs x1, mpidr_el1
    and x1, x1, #3          //cpu core id = 0, 1, 2, 3
    cbz x1, el1_entry
    b   cpu_goes_idle

cpu_goes_idle:
    wfi
    b cpu_goes_idle         //should not go here

el1_entry:
     msr sctlr_el1, XZR
    ldr x0, =SCTLR_CONTROL_VALUES
    msr sctlr_el1, x0

    ldr x0, =HCR_VALUE
    msr hcr_el2, x0

    ldr x0, =SCR_VALUE
    msr scr_el3, x0

    ldr x0, =SPSR_VALUE
    msr spsr_el3, x0

    adr x0, kernel_start
    msr elr_el3, x0

    eret

kernel_start:
    ldr x0, =KERNEL_STACK_START
    mov sp, x0

    bl   kernel_main
