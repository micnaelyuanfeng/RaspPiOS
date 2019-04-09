#ifndef _UART_H_
#define _UART_H_

#define ALL_BITS_MASK_32                0x00000000
#define BAUD_RATE_DIVIDER               40
#define DELAY_CYCLES                    150

void    uart_init(void);
void    uart_ttl_send(uint8_t character);
uint8_t uart_ttl_receive(void);
void    uart_ttl_send_str(uint8_t* str);
void    uart_printf_if(void*p, char c);

#endif