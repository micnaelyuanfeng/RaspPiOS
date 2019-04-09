.globl _memzero
_memzero:
	str xzr, [x0], #8
	subs x1, x1, #8
	b.gt _memzero

	ret


.globl _put32
_put32:
	str w1,[x0]
	
    ret


.globl _get32
_get32:
	ldr w0,[x0]
	
    ret


.globl _delay
_delay:
	subs x0, x0, #1
	bne _delay

	ret

.global _get_el
_get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2

    ret


.global _enable_interrupt
_enable_interrupt:
	msr daifclr, #2

	ret


.global _disable_interrupt
_disable_interrupt:
	msr daifset, #2

	ret


.global _build_vtb
_build_vtb:
	adr x0, vbar_tbl
	msr vbar_el1, x0

	ret

.global _read_current_stack
_read_current_stack:
	mov x0, sp

	ret

.global _update_user_stack
_update_user_stack:
	msr sp_el0, x0

	ret

