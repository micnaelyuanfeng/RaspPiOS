#include "../include/types.h"
#include "../include/threads.h"
#include "../include/sysApi.h"
#include "../include/printf.h"


void kernel_level_transition_process(uint64_t process_id)
{
    uint64_t pid = process_id;
    
    //enable_interrupt();
    //disable_interrupt();
    while(1)
    {
    //    int i = get_el();
        //printf("---------------------\n");
        //printf("                %d \r", 1);
        //printf("---------------------\n");
    }
    //printf("Current User stack is 0x%x\n", current_process->process_cpu_ctx.sp);
    //trap_to_user((uint64_t)0, (uint64_t)&user_level_print_number, current_process->process_cpu_ctx.sp);
}