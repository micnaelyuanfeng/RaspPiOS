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
 *          |                              |
 *          | ---------------------------- | Low 2MB for kernel8
 *          |                              |
 *          |                              |
 *          |                              |
 *          |                              |
 *          |                              |
 *          --------------------------------
 * 
*************************************************/

#define PAGE_SIZE                   4096 //4k page
#define HIGH_MEMORY_START           0x3F000000
#define LOW_MEMORY_START            (1 << 21)
#define HEAP_NUM_PAGES              (HEAP_SIZE / PAGE_SIZE)

#define PROCESS_CTX_SIZE            sizeof(process_t)
#define NUM_OF_CSA_MAX              (4 * PAGE_SIZE / PROCESS_CSA_SIZE)
#define NUM_OF_PROCESS_MAX          0x4

#define HEAP_START                  0x204000
#define HEAP_SIZE                   ((HIGH_MEMORY_START - HEAP_START) / PAGE_SIZE)

#define KERNEL_STACK_START          0x10000

#ifndef __ASSEMBLER__

bool      pmm_init(void);
uint64_t* pmalloc(void);

bool      pfree(void* process);

#endif

#endif