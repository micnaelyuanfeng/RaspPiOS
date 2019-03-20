#include "Include\types.h"
#include "Include\mm.h"
#include "Include\list.h"
#include "Include\printf.h"

heap_status_t* process_table;
uint64_t*      heap;
uint64_t       heap_size;
uint64_t       heap_pages;
uint64_t       num_of_process;

enum RETURN_STATUS pmm_init(void)
{
    enum RETURN_STATUS result = RETURN_FAILED;

    process_table = (heap_status_t*)K_MEMORY_START_PA;

    heap = (uint64_t*)K_MEMORY_START_PA + PAGE_SIZE / 8;

    num_of_process = PAGE_SIZE / 16;

    for(uint32_t i = 0; i < PROCESS_NUM_MAX; i++)
    {
        process_table[i].status.alloc = 0;
        process_table[i].status.free = 1;
        process_table[i].status.index = i;
        process_table[i].status.reserved = 0;
        process_table[i].process_pa = (void*)(heap + i * PAGE_SIZE / 4);
    }

    result = RETURN_SUCCESS;

    return result;
}

void* pmalloc(void)
{
    uint32_t i = 0;

    for(; i < HEAP_NUM_PAGES; i++)
    {
        if(process_table[i].status.free == 1)
        {
            process_table[i].status.free = 0;
            process_table[i].status.alloc = 1;
            break;
        }
    }

    return process_table[i].process_pa;
}

enum RETURN_STATUS pfree(void* process)
{
    enum RETURN_STATUS result = RETURN_FAILED;

    uint32_t i = 0;

    for(; i < HEAP_NUM_PAGES; i++)
    {
        if(process_table[i].process_pa == process)
        {
            process_table[i].status.free = 1;
            process_table[i].status.alloc = 0;
            process_table[i].process_pa = NULL;
        
            result = RETURN_SUCCESS;
        }
    }

    return result;
}

void* kmalloc(uint64_t size)
{
    return NULL;
}

enum RETURN_STATUS kfree(void* pAddr, uint64_t size)
{
    return RETURN_SUCCESS;
}

void km_info(void)
{
    total_memory_info();
    free_memory_info();
}

void free_memory_info(void)
{
    _free_memory_info();
}

void total_memory_info(void)
{
    _total_memory_info();
}

void _free_memory_info(void)
{
    ;
}

void _total_memory_info(void)
{
    printf("Heap Starting Address is 0x%x\n", heap);
    printf("Heap Total Size is 0x%x\n", heap_size);
    printf("Max Process support is %d\n", num_of_process);
    printf("process_table Address is 0x%x\n", process_table);

    for(uint32_t i = 0; i < num_of_process; i++)
    {
        if(process_table[i].status.free == 1)
        {
            printf("Heap PA is 0x%x\n",  process_table[i].process_pa);
        }
    }
}