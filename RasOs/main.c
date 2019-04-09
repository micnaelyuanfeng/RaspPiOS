#include "../include/types.h"
#include "../include/process.h"
#include "../include/mm.h"
#include "../include/uart.h"
#include "../include/timer.h"
#include "../include/exception.h"
#include "../include/sysApi.h"
#include "../include/threads.h"
#include "../include/printf.h"
#include "../include/schedule.h"

extern uint64_t* pmm_start;
extern uint64_t* pmm_end;
extern uint64_t  pmm_size;

extern process_t* current_process;

int kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    // Declare as unused
	(void) r0;
	(void) r1;
	(void) atags;

	//Enable Printf Debug
	uart_init();
	init_printf(0, uart_printf_if);;

	uart_ttl_send_str((uint8_t*)"---------------------------------\r\n");
	uart_ttl_send_str((uint8_t*)"|         Hello, Kernel!        |\r\n");
	uart_ttl_send_str((uint8_t*)"---------------------------------\r\n");

	exception_tbl_init();
	//int el = get_el();
	//printf("Exception level: %d \r\n", el);
	timer_init();

	uart_ttl_send_str((uint8_t*)"---------------------------------\r\n");
	printf("|        Initilize Timer!       |\r\n");
	uart_ttl_send_str((uint8_t*)"---------------------------------\r\n");

	build_vtb();

	printf("---------------------------------\r\n");
	if(pmm_init())
	{
		printf("| Memory Starts at: 0x%x    |\n", (uint64_t)pmm_start);
		printf("| Memory Ends   at: 0x%x  |\n", (uint64_t)pmm_end);
		printf("---------------------------------\r\n");
	}

	if(!create_daemon_process())
	{
		printf("Create Daemon Process Failed\n");
	}

	enable_exception_ctr();
	uart_ttl_send_str((uint8_t*)"---------------------------------\r\n");
	printf("|  Enable Exception Hardware!   |\r\n");
	uart_ttl_send_str((uint8_t*)"---------------------------------\r\n");
	
	if(!create_process((uint64_t)&kernel_level_transition_process, (uint64_t)2))
	{
		printf("Create Process Failed\n");
	}

	enable_interrupt();

	while(1)
	{
		//enable_interrupt();

		//printf("0\r");
		//schedule();
	}

	return 0;
}