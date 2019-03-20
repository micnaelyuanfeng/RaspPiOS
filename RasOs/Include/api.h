#ifndef _API_H_
#define _API_H_

void 	 mmio_write(uint32_t reg_addr, uint32_t data);
uint32_t mmio_read(uint32_t reg_addr);
void 	 delay(uint32_t count);
int      get_el(void);
void     enable_interrupt(void);
void     disable_interrupt(void);
void     build_vtb(void);


#endif