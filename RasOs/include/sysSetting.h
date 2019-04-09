#ifndef _SYS_SETTING_H_
#define _SYS_SETTING_H_

#define KERNEL_STACK_START                  0x10000

#define SCTLR_RESERVED                      (3 << 28) | (3 << 22) | ( 1 << 20) | ( 1 << 11)
#define SCTLR_LITTLE_ENDIAN_EL1             (0 << 25)
#define SCTLR_LITTLE_ENDIAN_EL0             (0 << 24)
#define SCTLR_I_CACHE_DISABLE               (0 << 12)
#define SCTLR_D_CACHE_DISABLE               (0 << 2)
#define SCTLR_MMU_DISABLE                   (0 << 0)
#define SCTLR_MMU_ENABLED                   (1 << 0)

#define SCTLR_CONTROL_VALUES                (SCTLR_RESERVED | SCTLR_LITTLE_ENDIAN_EL1 | SCTLR_I_CACHE_DISABLE | SCTLR_D_CACHE_DISABLE | SCTLR_MMU_DISABLE)

#define HCR_RW                              (1 << 31)
#define HCR_VALUE                           HCR_RW

#define SCR_RESERVED                        (3 << 4)
#define SCR_RW                              (1 << 10)
#define SCR_NS                              (1 << 0)
#define SCR_VALUE                           (SCR_RESERVED | SCR_RW | SCR_NS)

// Save Program Status Register(EL3) 
// Holds processor state = eret instruction restore value of this register
// Processor state = condition flags
// Condition Flags: Negative Flag (N), Zero Flag (A), Unsigned Overflow (C), Signed Overflow (V) affected by last instrucntion executed
// Interrupt disable bits
#define SPSR_MASK_ALL 			            (7 << 6)  //Switch to EL1 or Current State is EL1, all interrupts are need to be mask out
#define SPSR_EL1h			                (5 << 0)  //EL1 has dedicated Stack 
#define SPSR_VALUE			                (SPSR_MASK_ALL | SPSR_EL1h)

/**
 * Exception Registers
 * 4 Exception types
 *      1. Synchronous Exception = Instruction
 *      2. IRQ
 *      3. FIQ
 *      4. SError = External Hardware Error Interrupt
 * 
 * 4 * 4 = 16 handlers for each EL or PL 
**/ 
#define SYSTEM_TIMER_IRQ_0	                (1 << 0)
#define SYSTEM_TIMER_IRQ_1	                (1 << 1)
#define SYSTEM_TIMER_IRQ_2	                (1 << 2)
#define SYSTEM_TIMER_IRQ_3	                (1 << 3)

#define TIMER_CS_M0	                        (1 << 0)
#define TIMER_CS_M1	                        (1 << 1)
#define TIMER_CS_M2	                        (1 << 2)
#define TIMER_CS_M3	                        (1 << 3)

/**
 * CPU MODE BIT
**/
#define PSR_MODE_EL0t	                    0x00000000
#define PSR_MODE_EL1t	                    0x00000004
#define PSR_MODE_EL1h	                    0x00000005
#define PSR_MODE_EL2t	                    0x00000008
#define PSR_MODE_EL2h	                    0x00000009
#define PSR_MODE_EL3t	                    0x0000000c
#define PSR_MODE_EL3h	                    0x0000000d


#endif