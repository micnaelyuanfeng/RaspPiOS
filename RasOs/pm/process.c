#include "../include/types.h"
#include "../include/process.h"
#include "../include/mm.h"
#include "../include/sysApi.h"
#include "../include/printf.h"

extern uint64_t stack_idx;
extern uint64_t* pmm_start;

extern void trap_to_process(void);

process_t* current_process = NULL;
process_t* daemon_process = NULL;

uint64_t process_num_cntl = 0;

bool create_daemon_process(void)
{
    bool result = true;

    process_t* new_process = NULL;

    new_process = (process_t*)pmalloc();

    new_process->valid = 1;
    new_process->process_id = process_num_cntl;
    new_process->type = KERNEL_PROCESS;
    new_process->process_pa = (uint64_t)(pmm_start + process_num_cntl * PAGE_SIZE / 8);

    new_process->preempt_count = 0;
    new_process->state = PROCESS_RUNNING;
    new_process->counter = 0;
    new_process->priority = 1;
    new_process->scheduled = 1;

    printf("---------------------------------\r\n");
    printf("| Create Process Page at 0x%x\r\n", new_process->process_pa);
    printf("| Create Process CSA at  0x%x\r\n", new_process);
    printf("---------------------------------\r\n");
    /*
    printf("%d\n", new_process->valid);
    printf("%d\n", new_process->scheduled);
    printf("%d\n", new_process->preempt_count);
    printf("%d\n", new_process->process_id);
    printf("%d\n", new_process->scheduled);
    printf("%d\n", new_process->state);
    printf("%d\n", new_process->type);
    printf("0x%x\n", new_process->process_csa_pa);
    */

    daemon_process = new_process;
    current_process = new_process;

    result = new_process != NULL ? true : false;

    if(result)
    {
        process_num_cntl++;
    }

    return result;
}

bool create_process(uint64_t fn, uint64_t arg)
{
    bool result = true;

    if(fn == 0 || arg == 9)
    {
        printf("Create Process Failed\n");
    
        result = false;
    }
    else
    {
        process_t* new_process = NULL;

        new_process = (process_t*)pmalloc();

        new_process->priority = current_process->priority;
        new_process->preempt_count = 1;
        new_process->state = PROCESS_SUSPEND;
        new_process->counter = new_process->priority;

        new_process->valid = 1;
        new_process->type = KERNEL_PROCESS;
        new_process->process_pa = (uint64_t)(pmm_start + process_num_cntl * PAGE_SIZE / 8);
        new_process->scheduled = 0;
        new_process->process_id = process_num_cntl;

        new_process->process_ctx.x19 = fn;
        new_process->process_ctx.x20 = arg;
        new_process->process_ctx.pc = (uint64_t)trap_to_process;
        new_process->process_ctx.sp = new_process->process_pa;

        process_num_cntl++;

        printf("---------------------------------\r\n");
        printf("| Create Process Page at 0x%x\r\n", new_process->process_pa);
        printf("| Create Process CSA at  0x%x\r\n", new_process);
        printf("---------------------------------\r\n");

    }
    
    return result;
}
