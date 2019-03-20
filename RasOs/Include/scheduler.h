#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

void copy_daemon_process(void);
void preempt_enable(void);
void preempt_disable(void);
void process_ctx_switch(process_t* prev_process, process_t* next_process);
void switch_process(process_t* next_process);
void switch_to_daemon(void);
void call_scheduler(void);
process_t* scheduler_algo(void);
void scheduling(void);

#endif