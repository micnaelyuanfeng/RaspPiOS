#ifndef _PROCESS_H_
#define _PROCESS_H_

enum process_type
{
	DAEMON_PROCESS = 0x0,
	KERNEL_PROCESS = 0x1,
	USER_PROCESS   = 0x2,
	INVAILD_PROCESS_TYPE 
};

enum process_state
{
    PROCESS_RUNNING  = 0x0,
    PROCESS_SUSPEND  = 0x1,
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
}cpu_context_t;

typedef struct
{
	cpu_context_t		process_ctx;
	uint64_t            counter;
	uint64_t            priority;
    uint64_t            preempt_count;
	uint64_t			process_id;
	uint64_t            process_pa;
	uint64_t            valid;
	uint64_t            scheduled;
	enum process_state  state;
	enum process_type   type;
}process_t;

bool create_daemon_process(void);
bool create_process(uint64_t fn, uint64_t arg);

#endif