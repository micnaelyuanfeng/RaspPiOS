#ifndef _PROCESS_H_
#define _PROCESS_H_

#define NUM_PROCESS_MAX                 0x40    //64 process support

enum process_type
{
	DAEMON_PROCESS = 0x0,
	KERNEL_PROCESS = 0x1,
	USER_PROCESS   = 0x2,
	INVAILD_PROCESS 
};

enum process_state
{
    PROCESS_RUNNING  = 0x0,
    PROCESS_SUSPEND  = 0x1,
    PROCESS_WAITTING = 0x2,
    PROCESS_INVALID
};

typedef struct
{
    uint64_t x19;
	uint64_t x20;
	uint64_t x21;
	uint64_t x22;
	uint64_t x23;
	uint64_t x24;
	uint64_t x25;
	uint64_t x26;
	uint64_t x27;
	uint64_t x28;
	uint64_t fp;
	uint64_t sp;
	uint64_t pc;
}process_ctx_t;

typedef struct
{
    process_ctx_t       process_cpu_ctx;
    uint64_t            counter;
    uint64_t            prioirty;
    uint64_t            preempt_count;
	uint64_t            heap_start;
	uint64_t			process_id;
	uint64_t            valid;
	uint64_t            scheduled;
	enum process_state  state;
	enum process_type   type;
}process_t;

typedef struct 
{
	uint64_t regs[31];
	uint64_t sp;
	uint64_t pc;
	uint64_t pstate;
}cpu_context_t;

void copy_daemon_process(void);
void  process_init(process_t* this_process);
enum RETURN_STATUS  process_create(uint64_t fn, uint64_t arg);
enum RETURN_STATUS  process_add(void);
enum RETURN_STATUS  process_delete(void* this_process);
void  process_info(void* this_process);
void* process_search(void* this_process);

enum RETURN_STATUS _process_create(uint64_t fn, uint64_t arg);
void  _process_add(void);
void  _process_delete(void* this_process);
void  _process_info_display(void* this_process);
void* _process_search(void* this_process);

#endif