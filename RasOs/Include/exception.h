#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

void enable_exception_ctr(void);
void debug_exception_msg(uint32_t type, uint64_t esr, uint64_t address);
void handle_exception(void);

#endif