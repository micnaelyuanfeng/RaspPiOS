#include "Include\types.h"
#include "Include\api.h"
#include "Include\process.h"
#include "Include\fpools.h"
#include "Include\printf.h"

extern process_t* current_process;
extern void trap_to_user(uint64_t el_leve, uint64_t pc, uint64_t sp);

void kernel_level_print_number(uint64_t process_id)
{
    uint64_t pid = process_id;

    enable_interrupt();

    while(1)
    {
        int i = get_el();
        //printf("---------------------\n");
        printf("        %d \r", i);
        //printf("---------------------\n");
    }
}

void kernel_level_transition_process(uint64_t process_id)
{
    uint64_t pid = process_id;

    int i = get_el();

    enable_interrupt();

    printf("EL Level is :%d \n", i);
    
    //printf("call here\n");

    trap_to_user((uint64_t)0, (uint64_t)&user_level_print_number, current_process->process_cpu_ctx.sp);
}

void user_level_print_number(uint64_t process_id)
{
    uint64_t pid = process_id;

    while(1)
    {
        ;
    }
}