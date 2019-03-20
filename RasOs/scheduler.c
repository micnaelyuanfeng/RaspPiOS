#include "Include\types.h"
#include "Include\api.h"
#include "Include\mm.h"
#include "Include\process.h"
#include "Include\scheduler.h"
#include "Include\api.h"
#include "Include\printf.h"

uint64_t process_num_scheduled = 1;

extern void enable_interrupt(void);
extern void disable_interrupt(void);

extern heap_status_t* process_table;
extern process_t* daemon_process;
extern process_t* current_process;
extern uint64_t process_num_cntl;

extern void ctx_switch(process_t* prev_process, process_t* next_process);


void preempt_enable()
{
    current_process->preempt_count = 0;
}

void preempt_disable()
{
    current_process->preempt_count = 1;
}

void process_ctx_switch(process_t* prev_process, process_t* next_process)
{
    //disable_interrupt();
    ctx_switch(prev_process, next_process);
    //enable_interrupt();
}

void switch_process(process_t* next_process)
{
    if(current_process == next_process)
    {
        current_process->scheduled = 1;
        //prev_process->state = PROCESS_SUSPEND;    
        current_process->state = PROCESS_RUNNING;
        //printf("Process ID is scheduled again %d\n", current_process->process_id);
        preempt_enable();
    }
    else
    {
        //printf("Process ID %d is scheduled\n", next_process->process_id);
        //printf("Current Process Type %d\n", current_process->type);
        //printf("Next Process Type is %d\n", next_process->type);
        //Update Process Status    
        process_t* prev_process = current_process;

        current_process = next_process;
        
        prev_process->scheduled = 1;
        //prev_process->state = PROCESS_SUSPEND;    
        next_process->state = PROCESS_RUNNING;
        //printf("Choose process is 0x%x\n", next_process);
        //printf("Choose process is %d\n", next_process->process_id);
        preempt_enable();

        process_num_scheduled++;

        process_ctx_switch(prev_process, next_process);
    }
}

process_t* scheduler_algo(void)
{
    process_t* target_process = NULL;
    //printf("Total number of Process is %d\n", process_num_cntl);
    for(uint32_t i = 0; i < process_num_cntl; i++)
    {
        //printf("%d ");

        //if(i == 0)
        //{
            //printf("Process alloc: %d ", process_table[i].status.alloc);
            //printf("Process sched: (%d) ", ((process_t*)process_table[i].process_pa)->scheduled );
            //printf("Process state: (%d) ", ((process_t*)process_table[i].process_pa)->state );
        //}
        //printf("Search\n");
        if(process_table[i].status.alloc == 1)
        {
            if(((process_t*)process_table[i].process_pa)->state == PROCESS_SUSPEND &&
               ((process_t*)process_table[i].process_pa)->scheduled == 0)
            {
                target_process = (process_t*)process_table[i].process_pa;
                //if(i == 0)
                //    printf("Hit 0");
                printf("Choose process is (0x%x)\n", target_process);
                //printf("Process state is %d\n", target_process->state);
                //printf("Process preemption count is %d\n", target_process->preempt_count);
                break;
            }
        }
    }
    //printf("curretn number of process scheduled %d\n", curr_num_scheduler);
    //printf("curretn number of process %d\n", process_num_cntl)

    return target_process;
}

void scheduling(void)
{
    preempt_disable();

    process_t* next_process = NULL;

    if((next_process = scheduler_algo()) != NULL)
    {
        switch_process(next_process);
    }
    else
    {
        //printf("Scheduling Failed and Next Process is NULL\n");

        preempt_enable();
    }
}

void switch_to_daemon()
{
    printf("Swtich to Dameon Start\n");

    process_t* prev_process = current_process;

    current_process = daemon_process;
    
    //process_ctx_switch_dameon(prev_process, daemon_process);

    printf("Swtich to Dameon End\n");
}

void call_scheduler()
{
    if(current_process->preempt_count > 0)
    {
        printf("Current Process Disable Preemption\n");
    }
    else
    {
       scheduling();
    }     
}