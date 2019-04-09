#include "../include/types.h"
#include "../include/timer.h"
#include "../include/process.h"
#include "../include/schedule.h"
#include "../include/sysReg.h"
#include "../include/sysApi.h"
#include "../include/printf.h"

const uint64_t interval_value = 20000;
uint32_t current_value = 0;

extern uint64_t   process_num_cntl;
extern uint64_t*  process_csa_start;

void timer_init(void)
{
    current_value = mmio_read(TIMER_CLO);
    current_value = current_value + interval_value;
    //Choose Compare Regsiter 1 = Timer interrupt line 1
    mmio_write(TIMER_C1, current_value);
}

void timer_intr_handler(void)
{
    bool all_scheduled = true;

    current_value += interval_value;
    
    printf("Timer interrupt received, %d\r", current_value);
    //printf("Timer interrupt received\n");

    for(uint32_t i = 0; i < process_num_cntl; i++)
    {
        if(((process_t*)process_csa_start)[i].scheduled == 0)
        {
            all_scheduled = false;
        }
    }

    if(all_scheduled == true)
    {
 
        printf("All Scheduled\n");

        for(uint32_t i = 0; i < process_num_cntl; i++)
        {
            ((process_t*)process_csa_start)[i].scheduled = 0;
            ((process_t*)process_csa_start)[i].state = PROCESS_SUSPEND;
        }
    }
   
    mmio_write(TIMER_C1, current_value);
  
	mmio_write(TIMER_CS, TIMER_CS_M1);

    timer_tick();
}

void generic_timer_init(void)
{
    mmio_write(GENERIC_TIME_CNTL, 0x8);
}