#include "Include\types.h"
#include "Include\api.h"
#include "Include\offset.h"
#include "Include\sysregs.h"
#include "Include\timer.h"
#include "Include\process.h"
#include "Include\scheduler.h"
#include "Include\api.h"
#include "Include\mm.h"
#include "Include\printf.h"

/**
 *  Timer Introduction
 *  Timer has 4 interrupt lines connected to interrupt controller
 *  Each interrupt line as an timer compare register
 * 
 *  To make timer interrupt works:
 *      1. Initialize Timer
 *          1. Get current time stamp from Timer CLO register
 *          2. Set one of timer compare register
 *      2. Timer Interrupt Handler
 *          1. Get current value and update compare register with +time_interval
 *          2. Clear timer interrupt bit by setting Control/Status register corresponding bit [0:3]
 * 
**/

const uint64_t interval_value = 300000;
uint32_t current_value = 0;

extern process_t* current_process;
extern uint64_t process_num_cntl;
extern uint64_t process_num_scheduled;
extern heap_status_t* process_table;

void timer_init(void)
{
    current_value = mmio_read(TIMER_CLO);
    current_value = current_value + interval_value;
    //Choose Compare Regsiter 1 = Timer interrupt line 1
    mmio_write(TIMER_C1, current_value);
}

void timer_intr_handler(void)
{
    current_value += interval_value;
    
    //printf("\nTimer interrupt received, %d\n", current_value);
    //printf("Timer interrupt received\n");

    //printf("Current EL: %d\n", current_process->process_cpu_ctx.pstate);

    if(process_num_scheduled == (process_num_cntl - 1))
    {

        //printf("All Scheduled\n");

        for(uint32_t i = 0; i < process_num_cntl; i++)
        {
            ((process_t*)process_table[i].process_pa)->scheduled = 0;
            ((process_t*)process_table[i].process_pa)->state = PROCESS_SUSPEND;
        }

        process_num_scheduled = 0;
    }
   
    mmio_write(TIMER_C1, current_value);
  
	mmio_write(TIMER_CS, TIMER_CS_M1);

    call_scheduler();
}

void generic_timer_init(void)
{
    mmio_write(GENERIC_TIME_CNTL, 0x8);
}