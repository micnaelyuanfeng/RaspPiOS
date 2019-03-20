#ifndef _E_ENTRY_H_
#define _E_ENTRY_H_

#define STACK_FRAME_SIZE                    256 //31 * 8 bytes = 248 bytes

/**
 * 4 PL and each PL has 4 types and 4 ES
 * ES = Execution State
 * PL = Privillege Level
 * EL = Execption Level 
**/

#define SYNC_INVALID_EL1t		            0 
#define IRQ_INVALID_EL1t		            1 
#define FIQ_INVALID_EL1t		            2 
#define ERROR_INVALID_EL1t		            3 

#define SYNC_INVALID_EL1h		            4 
#define IRQ_INVALID_EL1h		            5 
#define FIQ_INVALID_EL1h		            6 
#define ERROR_INVALID_EL1h		            7 

#define SYNC_INVALID_EL0_64	    	        8 
#define IRQ_INVALID_EL0_64	    	        9 
#define FIQ_INVALID_EL0_64		            10 
#define ERROR_INVALID_EL0_64		        11 

#define SYNC_INVALID_EL0_32		            12 
#define IRQ_INVALID_EL0_32		            13 
#define FIQ_INVALID_EL0_32		            14 
#define ERROR_INVALID_EL0_32		        15 

#endif