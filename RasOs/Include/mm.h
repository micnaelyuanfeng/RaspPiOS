#ifndef _MM_H_
#define _MM_H_

/*************************************************
 *            Memory Layout
 * -----------------------------------------------
 * Bootloader GPU
 *  read config.txt and find boot config
 *  MBR and Load to target PM area based on cofig
 * 
 * config.txt settings from Raspberry Pi.Org
 * 
 * if(kernel_old = 1)
 *  load kernel_img to PA = 0x0
 * else
 * if(ARCH = raspi2)
 *  load kernel_img to PA = 0x8000
 * if(ARCH = raspi3)
 *  load kernel_img to PA = 0x80000
 * -----------------------------------------------
 * if(kernel_old = 1)
 *  load kernel image to 0x0
 *  set PC = 0x0
 * 
 *          --------------------------------
 *          |                              |
 *          |                              |
 *          |                              |
 *          |                              |
 *          |                              |
 *          | ---------------------------- | -> High Memory for MMIO Register for Devices
 *          |                              |
 *          |                              |
 *          |                              |
 *          |                              |
 *          | ---------------------------- | Process N
 *          |                              | 
 *          | ---------------------------- | Process Heap
 *          |                              |
 *          |                              |
 *          |                              | 
 *          | ---------------------------- | Process Stack
 *          |                              |
 *          |                              |
 *          |                              |
 *          |                              |
 *          |                              | 
 *          |                              |
 *          |                              |
 *          |                              |
 *          |                              |
 *          |                              |
 *          | ---------------------------- | Process Table = 4KB (4KB / 16 bytes = 256 Process) 
 *          | ---------------------------- | Low 2MB for kernel8
 *          |                              |
 *          |                              |
 *          |                              |
 *          |                              |
 *          |                              |
 *          --------------------------------
 * 
*************************************************/

typedef struct heap_status
{
    struct 
    {
        uint64_t alloc: 1;
        uint64_t free:  1;
        uint64_t index: 32;
        uint64_t reserved: 32;
    }status;
    
    void*        process_pa;
}heap_status_t;

#define PAGE_SIZE                   0x1000 //4k page
#define MMIO_MEMORY_START_PA        0x3F000000
#define K_MEMORY_START_PA           (1 << 21)
#define PAGE_ALIGN_MASK             0x00000FFF
#define HEAP_SIZE                   ((MMIO_MEMORY_START_PA - PAGE_SIZE - K_MEMORY_START_PA) & ~PAGE_ALIGN_MASK)
#define HEAP_NUM_PAGES              (HEAP_SIZE / PAGE_SIZE)

#define PROCESS_NUM_MAX             PAGE_SIZE / 16

enum RETURN_STATUS  pmm_init(void);
void*               kmalloc(uint64_t size);
void*               pmalloc(void);
enum RETURN_STATUS  kfree(void* pAddr, uint64_t size);
enum RETURN_STATUS  pfree(void* process);
void  km_info(void);

void free_memory_info(void);
void total_memory_info(void);

void _free_memory_info(void);
void _total_memory_info(void);

#endif