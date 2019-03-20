#ifndef _F_POOLS_
#define _F_POOLS_

void kernel_level_print_number(uint64_t process_id);

void kernel_level_transition_process(uint64_t process_id);
void user_level_print_number(uint64_t process_id);

#endif