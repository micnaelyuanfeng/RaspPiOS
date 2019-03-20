#include "Include\types.h"
#include "Include\printf.h"
#include "Include\offset.h"
#include "Include\api.h"
#include "Include\uart.h"
#include "Include\exception.h"
#include "Include\mm.h"
#include "Include\process.h"
#include "Include\timer.h"
#include "Include\fpools.h"

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

extern uint64_t* vectors;
extern process_t* daemon_process;

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	// Declare as unused
	(void) r0;
	(void) r1;
	(void) atags;
	
	//Enable Printf Debug
	uart_init();
	init_printf(0, uart_printf_if);

	uart_ttl_send_str((uint8_t*)"-----------------------------\r\n");
	uart_ttl_send_str((uint8_t*)"|       Hello, Kernel!      |\r\n");
	uart_ttl_send_str((uint8_t*)"-----------------------------\r\n");

	if(!pmm_init() == RETURN_SUCCESS)
	{
		printf("PMM Init Falied\n");
	}

	//int el = get_el();
	//printf("Exception level: %d \r\n", el);
	timer_init();
	//generic_timer_init();
	uart_ttl_send_str((uint8_t*)"-----------------------------\r\n");
	printf("|      Initilize Timer!     |\r\n");
	uart_ttl_send_str((uint8_t*)"-----------------------------\r\n");

	build_vtb();

	copy_daemon_process();

	enable_exception_ctr();
	uart_ttl_send_str((uint8_t*)"------------------------------\r\n");
	printf("| Enable Exception Hardware! |\r\n");
	uart_ttl_send_str((uint8_t*)"------------------------------\r\n");

	enum RETURN_STATUS result;
	
	result = process_create((uint64_t)&kernel_level_transition_process, (uint64_t)1);

	//result = process_create((uint64_t)&print_number, (uint64_t)2);

	enable_interrupt();

	while (1)
	{
		//uart_ttl_send(uart_ttl_receive());
		//int i = get_el();
        printf("%d  \r", 0);
	}
}