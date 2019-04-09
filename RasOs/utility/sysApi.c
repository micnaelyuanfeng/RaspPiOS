#include "../include/types.h"
#include "../include/sysApi.h"
#include "../include/printf.h"

/**
 *  assembler will but 1st argument into x0, 2nd argument into x2, and upto 4 arguments
 *  If there are more than 4 arguments, then use stack to pass arguments. 
**/
extern void     _delay(uint64_t wait_length);
extern void     _put32(uint64_t reg_addr, uint32_t character);
extern uint32_t _get32(uint64_t reg_addr);
extern void     _memzero(uint64_t mem_addr, uint64_t size);
extern int      _get_el(void);
extern uint64_t _read_current_stack(void);
extern void     _update_user_stack(uint64_t sp);

//All arguments are not visible to outsiders
extern void     _enable_interrupt(void);
extern void     _disable_interrupt(void);
extern void     _build_vtb(void);

// Memory-Mapped I/O output
void mmio_write(uint32_t reg_addr, uint32_t data)
{
	_put32(reg_addr, data);
}
 
// Memory-Mapped I/O input
uint32_t mmio_read(uint32_t reg_addr)
{
	return _get32(reg_addr);
}
 
void delay(uint32_t count)
{
	_delay(count);
}

int get_el(void)
{
	return _get_el();
}

void enable_interrupt(void)
{
	_enable_interrupt();
}

void disable_interrupt(void)
{
	_disable_interrupt();
}

void build_vtb(void)
{
	_build_vtb();
}

uint32_t read_stack(void)
{
	return _read_current_stack();
}

void update_ustack(uint64_t sp)
{
	_update_user_stack(sp);
}