#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#define NUM_OF_INTR_SUPPORT             17

void exception_tbl_init(void);
void enable_exception_ctr(void);
void debug_exception_msg(uint32_t type, uint64_t esr, uint64_t address);
void handle_exception(void);

extern void sync_invalid_el1t(void);
extern void irq_invalid_el1t(void);
extern void fiq_invalid_el1t(void);
extern void error_invalid_el1t(void);
extern void sync_invalid_el1h(void);
extern void fiq_invalid_el1h(void);
extern void error_invalid_el1h(void);
extern void fiq_invalid_el0_64(void);

extern void error_invalid_el0_64(void);

extern void sync_invalid_el0_32(void);

extern void irq_invalid_el0_32(void);
extern void fiq_invalid_el0_32(void);

extern void error_invalid_el0_32(void);
extern void sync_invalid_el0t(void);
extern void el1_irq(process_t* process);
extern void el0_irq(process_t* process); 

typedef void (*interrupt_handler_t)(process_t* process_ctx);

#endif