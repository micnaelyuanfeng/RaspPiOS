#include "../include/types.h"
#include "../include/process.h"
#include "../include/timer.h"
#include "../include/sysReg.h"
#include "../include/sysApi.h"
#include "../include/exception.h"
#include "../include/printf.h"

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};

/**
 *	Exception = Interrupt
 *  4 types of Interrupts
 *  1. Synchronous exception = current execution and software interrupt (e.g. svc)
 *  2. IRQ = Interrupt Request (Normal Interrupt and Asynchronous) from external hardware
 *  3. FIQ
 *  4. SError = System Error and generated by external hardware
 * 
 *  Vector Table
 *  Each exception level has 4 ES => 4 ES * 4 ET = 16 handler
 *  Each exception level has a register holding pointer to vector table
 *  
 *  Vector Table is a function array
 *  Each entry is 0x80 bytes maximum 
 *  If handler size is > 0x80 bytes, can use branch
 *  If workspace is at EL1, then use vbar_el0 to hold the pointer to vector table
 *  
 * .global vectors (label)
 * vectors:
 * 			.align 7
 * 				<function_body>
 * 			.align 7
 * 				<function_body>
 * 			.align 7
 * 				<function_boyd>
 * 			........
 * 			16 functions
 * 
 * 
**/

interrupt_handler_t int_handler[NUM_OF_INTR_SUPPORT];

void enable_exception_ctr(void)
{
    mmio_write(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1);
}

void exception_tbl_init(void)
{
	int_handler[0] = (void*)&sync_invalid_el1t;
	int_handler[1] = (void*)&irq_invalid_el1t;
	int_handler[2] = (void*)&fiq_invalid_el1t;
	int_handler[3] = (void*)&error_invalid_el1t;
	int_handler[4] = (void*)&sync_invalid_el1h;
	int_handler[5] = (void*)&fiq_invalid_el1h;
	int_handler[6] = (void*)&error_invalid_el1h;
	int_handler[7] = (void*)&fiq_invalid_el0_64;
	int_handler[8] = (void*)&error_invalid_el0_64;
	int_handler[9] = (void*)&sync_invalid_el0_32;
	int_handler[10] = (void*)&sync_invalid_el0_32;
	int_handler[11] = (void*)&irq_invalid_el0_32;
	int_handler[12] = (void*)&fiq_invalid_el0_32;
	int_handler[13] = (void*)&error_invalid_el0_32;
	int_handler[14] = (void*)&sync_invalid_el0t;
	int_handler[15] = NULL;
	int_handler[16] = NULL;
	int_handler[17] = NULL;
}

void debug_exception_msg(uint32_t type, uint64_t esr, uint64_t address)
{
    printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
}

void handle_exception(void)
{
    uint32_t pending_excep_idx =  mmio_read(IRQ_PENDING_1);

    switch(pending_excep_idx)
    {
        case (SYSTEM_TIMER_IRQ_1):
            timer_intr_handler();
            break;
        default:
            printf("Unknow pending IRQ: %x\r\n", pending_excep_idx);
            break;
    }
}