#ifndef _OFFSET_H_
#define _OFFSET_H_

#define PBASE               0x3F000000
// The GPIO registers base address.
#define GPIO_BASE           (PBASE + 0x200000) // for raspi2 & 3, 0x20200000 for raspi1
// Controls actuation of pull up/down to ALL GPIO pins.
#define GPPUD               (GPIO_BASE + 0x94)
// Controls actuation of pull up/down for specific GPIO pin.
#define GPPUDCLK(g)         (GPIO_BASE + 0x98 + (g) * 4)

// The base address for UART.
#define UART0_BASE          (PBASE + 0x201000) // for raspi2 & 3, 0x20201000 for raspi1

// The offsets for reach register for the UART.
#define UART0_DR            (UART0_BASE + 0x00)
#define UART0_RSRECR        (UART0_BASE + 0x04)
#define UART0_FR            (UART0_BASE + 0x18)
#define UART0_ILPR          (UART0_BASE + 0x20)
#define UART0_IBRD          (UART0_BASE + 0x24)
#define UART0_FBRD          (UART0_BASE + 0x28)
#define UART0_LCRH          (UART0_BASE + 0x2C)
#define UART0_CR            (UART0_BASE + 0x30)
#define UART0_IFLS          (UART0_BASE + 0x34)
#define UART0_IMSC          (UART0_BASE + 0x38)
#define UART0_RIS           (UART0_BASE + 0x3C)
#define UART0_MIS           (UART0_BASE + 0x40)
#define UART0_ICR           (UART0_BASE + 0x44)
#define UART0_DMACR         (UART0_BASE + 0x48)
#define UART0_ITCR          (UART0_BASE + 0x80)
#define UART0_ITIP          (UART0_BASE + 0x84)
#define UART0_ITOP          (UART0_BASE + 0x88)
#define UART0_TDR           (UART0_BASE + 0x8C)

// Interrupt Registers
#define IRQ_BASIC_PENDING	(PBASE + 0x0000B200)
#define IRQ_PENDING_1		(PBASE + 0x0000B204)
#define IRQ_PENDING_2		(PBASE + 0x0000B208)
#define FIQ_CONTROL		    (PBASE + 0x0000B20C)
#define ENABLE_IRQS_1		(PBASE + 0x0000B210)
#define ENABLE_IRQS_2		(PBASE + 0x0000B214)
#define ENABLE_BASIC_IRQS	(PBASE + 0x0000B218)
#define DISABLE_IRQS_1		(PBASE + 0x0000B21C)
#define DISABLE_IRQS_2		(PBASE + 0x0000B220)
#define DISABLE_BASIC_IRQS	(PBASE + 0x0000B224)

// Timer
#define TIMER_CS            (PBASE + 0x00003000)
#define TIMER_CLO           (PBASE + 0x00003004)
#define TIMER_CHI           (PBASE + 0x00003008)
#define TIMER_C0            (PBASE + 0x0000300C)
#define TIMER_C1            (PBASE + 0x00003010)
#define TIMER_C2            (PBASE + 0x00003014)
#define TIMER_C3            (PBASE + 0x00003018)

// Generic Timer 
#define GENERIC_TIME_CNTL   0x40000040
#define GENERIC_TIMER_SCR   0x40000060

#endif