#include "../include/types.h"
#include "../include/process.h"
#include "../include/schedule.h"
#include "../include/sysApi.h"
#include "../include/printf.h"

extern void enable_interrupt(void);
extern void disable_interrupt(void);
extern void context_switch(uint64_t prev_process, uint64_t next_process);

extern uint64_t* process_csa_start;
extern process_t* current_process;
extern uint64_t process_num_cntl;

void preempt_enable()
{
    current_process->preempt_count = 0;
}

void preempt_disable()
{
    current_process->preempt_count = 1;
}

void switch_process(process_t* next_process)
{

        //printf("Process ID %d is scheduled\n", next_process->process_id);
        //printf("Current Process Type %d\n", current_process->type);
        //printf("Next Process Type is %d\n", next_process->type);
        //Update Process Status    
        process_t* prev_process = current_process;
        prev_process->state = PROCESS_SUSPEND; 
        prev_process->scheduled = 0;
        //printf("sizeof of context 0x%x\n", sizeof(cpu_context_t));
        //printf("Current stack 0x%x\n", read_stack);
        //printf("Current stack shift 0x%x\n", stack_addr);
        //printf("Current pstate: %d\n", ((cpu_context_t*)stack_addr)->pstate);

        current_process = next_process;
        current_process->scheduled = 1;   
        current_process->state = PROCESS_RUNNING;
        
        //printf("Context Switch\n");
        context_switch((uint64_t)&prev_process->process_ctx, (uint64_t)&current_process->process_ctx);
}

void _schedule()
{
    preempt_disable();
	
    int next;
    int c;
	//process_t * p;
    process_t* candidate_process = NULL;
    process_t* target_process = NULL;
    /*
	while (1) 
    {
		c = -1;
		
        next = 0;
		
        for (int i = 0; i < process_num_cntl; i++)
        {
			p = &((process_t*)process_csa_start)[i];
            //printf("0x%x, p counter =  %d p state = %d  \n",p, p->counter, p->state);
			//if (p && p->state == TASK_RUNNING && p->counter > c) 
            if((int)p->counter > c)
            {    
                //printf("Hit\n"); 
				c = p->counter;
				next = i;
			}
		}

        //printf("choose next =  %d\n", next);

		if (c) 
        {
			break;
		}
        
		for (int i = 0; i < process_num_cntl; i++) 
        {
			p = &((process_t*)process_csa_start)[i];

			if (p) 
            {
				p->counter = (p->counter >> 1) + p->priority;
			}
		}
	}
    */

    for (int i = 0; i < process_num_cntl; i++)
        {
			candidate_process = &((process_t*)process_csa_start)[i];
            //printf("0x%x, p counter =  %d p state = %d  \n",p, p->counter, p->state);
			//if (p && p->state == TASK_RUNNING && p->counter > c) 
            if(candidate_process != NULL && 
                candidate_process->state == PROCESS_SUSPEND &&
                candidate_process->scheduled == 0)
            {
                target_process = candidate_process;
            }
		}

    if (current_process == target_process)
    {
        return;
    }

	process_t* prev_process = current_process;
    prev_process->state = PROCESS_SUSPEND; 
    prev_process->scheduled = 0;
	
    current_process = target_process;
    current_process->scheduled = 1;
    current_process->state = PROCESS_RUNNING;

    context_switch((uint64_t)prev_process, (uint64_t)current_process);
	
    preempt_enable();
}

void schedule_tail(void) 
{
	preempt_enable();
}

void* scheduler_algo()
{
    
    void* target_process = NULL;

    for(uint32_t i = 0; i < process_num_cntl; i++)
    {
        /*
        printf("%d\n", ((process_t*)process_csa_start)[i].state);
        printf("%d\n", ((process_t*)process_csa_start)[i].scheduled);
        printf("0x%x\n",&((process_t*)process_csa_start)[i]);
        */
        if(((process_t*)process_csa_start)[i].state == PROCESS_SUSPEND &&
            ((process_t*)process_csa_start)[i].scheduled == 0)
            {
                target_process = (void*)&((process_t*)process_csa_start)[i];
            
                //printf("Choose process is (0x%x)\n", target_process);
               
                break;
            }
    }

    return target_process;
}

void schedule()
{
    current_process->counter = 0;
    _schedule();
}

void timer_tick()
{
    //--current_process->counter;

	//if (current_process->counter > 0 || current_process->preempt_count > 0) 
    //{
	//	return;
	//}

	//current_process->counter = 0;
	
    enable_interrupt();
	_schedule();
	disable_interrupt();
}