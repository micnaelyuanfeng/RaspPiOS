#include "Include\types.h"
#include "Include\eentry.h"
#include "Include\process.h"
#include "Include\sysregs.h"
#include "Include\mm.h"
#include "Include\printf.h"

process_t* ready_process_list = NULL;
process_t* daemon_process = NULL;
process_t* current_process = NULL;

extern void trap_to_process(void);
extern heap_status_t* process_table;
extern uint64_t curr_num_scheduler;
/**
 *  Primitive Design
**/
uint32_t  process_num_cntl = 0;

void copy_daemon_process()
{
    //Set up Process Stack
    process_t* new_process = NULL;

    new_process = (process_t*)pmalloc();
    
    if(new_process == NULL)
    {
        printf("There is no Physical Memory\n");
    }
    else
    {
        new_process->prioirty = 0;
        new_process->state = PROCESS_RUNNING;
        new_process->counter = new_process->prioirty;
        new_process->preempt_count = 0;
        new_process->process_id = process_num_cntl;
        new_process->type = DAEMON_PROCESS;
        new_process->process_cpu_ctx.sp = (uint64_t)0x10000; //change to inline ASM later
        new_process->scheduled = 1;

        process_table[process_num_cntl].status.free = 0;
        process_table[process_num_cntl].status.alloc = 1;
        //printf("0x%x %d\n", process_table[process_num_cntl]->process_pa, process_num_cntl);
        
        process_num_cntl++;
    }

    daemon_process = new_process;

    current_process = daemon_process;

    //printf("preemption is %d\n", current_process->preempt_count);
    //printf("process is 0x%x\n", current_process);
    //printf("process Id is %d\n", current_process->process_id);
}

void process_init(process_t* this_process)
{
    this_process->prioirty = -1;
    this_process->state = PROCESS_SUSPEND;
    this_process->counter = -1;
    this_process->preempt_count = -1;
    this_process->process_id = -1;
    
    this_process->process_cpu_ctx.pc = -1;
    this_process->process_cpu_ctx.sp = -1;
}

enum RETURN_STATUS process_create(uint64_t fn, uint64_t arg)
{
    enum RETURN_STATUS result;

    if(fn == 0 || arg == 9)
    {
        printf("Create Process Failed\n");
    
        result = RETURN_FAILED;
    }
    else
    {
        result = _process_create(fn, arg);
    }

    return result;
}

enum RETURN_STATUS process_add(void)
{
    enum RETURN_STATUS result = RETURN_FAILED;

    return result;
}

enum RETURN_STATUS process_delete(void* this_process)
{
    enum RETURN_STATUS result = RETURN_FAILED;

    return result;
}

void process_info(void* this_process)
{
    if(this_process == NULL)
    {
        printf("Process Info Failed\n");
    }
    else
    {
        _process_info_display(this_process);
    }
}

void* process_search(void* this_process)
{
    return NULL;
}

void  _process_add(void)
{
    ;
}

void  _process_delete(void* this_process)
{
    ;
}

void  _process_info_display(void* this_process)
{
    /*
    printf(this_process->prioirty);
    this_process->state;
    this_process->counter;
    this_process->preempt_count;
    this_process->process_id;
    
    this_process->process_cpu_ctx.pc;
    this_process->process_cpu_ctx.sp;
    */
}

void* _process_search(void* this_process)
{
    return NULL;
}

enum RETURN_STATUS _process_create(uint64_t fn, uint64_t arg)
{
    enum RETURN_STATUS result = RETURN_SUCCESS;

    //Set up Process Stack
    process_t* new_process = NULL;

    new_process = (process_t*)pmalloc();

    if(new_process == NULL)
    {
        printf("There is no Physical Memory\n");
        
        result = RETURN_FAILED;
    }
    else
    {
        new_process->prioirty = daemon_process->prioirty;
        new_process->state = PROCESS_SUSPEND;
        new_process->counter = new_process->prioirty;
        new_process->preempt_count = 0;
        new_process->process_id = process_num_cntl;
        new_process->type = USER_PROCESS;
        new_process->scheduled = 0;

        new_process->process_cpu_ctx.x19 = fn;
        new_process->process_cpu_ctx.x20 = arg;
        new_process->process_cpu_ctx.pc = (uint64_t)trap_to_process;
        new_process->process_cpu_ctx.sp = (uint64_t)((uint64_t*)new_process + PAGE_SIZE / 8);
        new_process->valid = 1;
      
        process_table[process_num_cntl].status.free = 0;
        process_table[process_num_cntl].status.alloc = 1;

        //printf("preemption is %d\n", new_process->preempt_count);
        //printf("process is 0x%x\n", new_process);
        //printf("process Id is %d\n", new_process->process_id);
        //printf("Free or not %d\n", process_table[process_num_cntl].status.free);
        //printf("Stack Address is 0x%x\n", new_process->process_cpu_ctx.sp);

        process_num_cntl++;

        printf("Current process num is %d\n", process_num_cntl);
    }
    
    return result;
}