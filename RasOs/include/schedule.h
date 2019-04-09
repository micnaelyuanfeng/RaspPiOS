#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

void preempt_enable(void);
void preempt_disable(void);
void process_ctx_switch(process_t* prev_process, process_t* next_process);
void switch_process(process_t* next_process);
void schedule(void);
void schedule_tail(void);
void* scheduler_algo(void);
void timer_tick(void);

#endif