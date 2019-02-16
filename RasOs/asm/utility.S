.section ".text"
.global _mem_zero
_mem_zero:
	;x0 is memory reference
	str xzr, [x0], #8
	subs x1, x1, #8 ;need to add s
	b.gt __mem_zero
	ret

.section ".text"
.global _get_cur_el
_get_cur_el:
	/*
		Current EL Register
		
		Last 2 bits are reserved
		value << 2 to get galue
	*/
	
	mrs x0, CurrentEl
	lsr x0, x0, #2    
	
	ret

.section ".text"
.global _put_32
_put_32:
	/*
		w1 is 32 bit form of 
	*/
	str w1, [x0]
	ret

.section ".text"
.global __get_32
_get_32:
	ldr w0, [x0]
	ret

.section ".text"
.global __delay
_delay:
	subs x0, x0, #1
	bne delay

	ret