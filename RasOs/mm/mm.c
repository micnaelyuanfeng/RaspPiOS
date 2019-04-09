#include "../include/types.h"
#include "../include/process.h"
#include "../include/mm.h"
#include "../include/printf.h"

uint64_t* process_csa_start = NULL;
uint64_t  process_csa_size = 0;
uint64_t* pmm_start = NULL;
uint64_t* pmm_end = NULL;
uint64_t  pmm_size = 0;
uint64_t  stack_idx = 0;

bool pmm_init(void)
{
    bool result = false;

    process_csa_start = (uint64_t*)LOW_MEMORY_START;
    process_csa_size = 4 * PAGE_SIZE;

    pmm_start = process_csa_start + 4 * PAGE_SIZE / 8;
    pmm_end = (uint64_t*)HIGH_MEMORY_START;
    
    result = ((uint64_t)pmm_start == HEAP_START) ? true : false;

    for(uint32_t i = 0; i < PROCESS_CTX_SIZE; i++)
    {
        ((process_t*)process_csa_start)[i].valid = 1;
        ((process_t*)process_csa_start)[i].scheduled = 0;
        ((process_t*)process_csa_start)[i].preempt_count = 0;
        ((process_t*)process_csa_start)[i].process_id = -1;
        ((process_t*)process_csa_start)[i].scheduled = 0;
        ((process_t*)process_csa_start)[i].state = PROCESS_INVALID;
        ((process_t*)process_csa_start)[i].type = INVAILD_PROCESS_TYPE;
    }
    printf("| -> Init Process CSAs Done     |\n");
    printf("| -> Init Process Pages Done    |\n");    
    /*
    for(uint32_t i = 0; i < PROCESS_CTX_SIZE; i++)
    {
        printf("-------%d\n", i);
        printf("%d\n", ((process_t*)process_csa_start)[i].valid);
        printf("%d\n",((process_t*)process_csa_start)[i].scheduled);
        printf("%d\n",((process_t*)process_csa_start)[i].preempt_count);
        printf("%d\n",((process_t*)process_csa_start)[i].process_id);
        printf("%d\n",((process_t*)process_csa_start)[i].scheduled);
        printf("%d\n",((process_t*)process_csa_start)[i].state);
        printf("%d\n",((process_t*)process_csa_start)[i].type);
    }
    */

    return result;
}

uint64_t* pmalloc(void)
{
    uint64_t* process_csa = (uint64_t*)&((process_t*)process_csa_start)[stack_idx];

    stack_idx++;

    return process_csa;
}

bool pfree(void* process)
{
    stack_idx--;

    return true;
}

