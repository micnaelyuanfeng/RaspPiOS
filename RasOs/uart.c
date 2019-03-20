#include "Include\types.h"
#include "Include\offset.h"
#include "Include\api.h"
#include "Include\uart.h"

void uart_init()
{
	// Disable UART0.
	mmio_write(UART0_CR, ALL_BITS_MASK_32);
	// Setup the GPIO pin 14 && 15.
 
	// Disable pull up/down for all GPIO pins & delay for 150 cycles.
	mmio_write(GPPUD, ALL_BITS_MASK_32);
	delay(DELAY_CYCLES);
 
	// Disable pull up/down for pin 14,15 & delay for 150 cycles.
	mmio_write((uint32_t)GPPUDCLK(0), (1 << 14) | (1 << 15));
	delay(DELAY_CYCLES);
 
	// Write 0 to GPPUDCLK0 to make it take effect.
	mmio_write((uint32_t)GPPUDCLK(0), 0x00000000);
 
	// Clear pending interrupts.
	mmio_write(UART0_ICR, 0x7FF);
 
	// Set integer & fractional part of baud rate.
	// Divider = UART_CLOCK/(16 * Baud)
	// Fraction part register = (Fractional part * 64) + 0.5
	// UART_CLOCK = 3000000; Baud = 115200.
 
	// Divider = 3000000 / (16 * 115200) = 1.627 = ~1.
	mmio_write(UART0_IBRD, 1);
	// Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40.
	mmio_write(UART0_FBRD, BAUD_RATE_DIVIDER);
 
	// Enable FIFO & 8 bit data transmissio (1 stop bit, no parity).
	mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
 
	// Mask all interrupts.
	mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
	                       (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));
 
	// Enable UART0, receive & transfer part of UART.
	mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

void uart_ttl_send(uint8_t character)
{
    // Wait for UART to become ready to transmit.
	while ( mmio_read(UART0_FR) & (1 << 5) );
	mmio_write(UART0_DR, character);
}

uint8_t uart_ttl_receive(void)
{
    // Wait for UART to have received something.
    while ( mmio_read(UART0_FR) & (1 << 4) );

    return mmio_read(UART0_DR);
}

void uart_ttl_send_str(uint8_t* str)
{
    for (uint32_t i = 0; str[i] != '\0'; i ++)
	{
		uart_ttl_send((unsigned char)str[i]);
	}
}

void uart_printf_if(void*p, char c)
{
	uart_ttl_send(c);
}
