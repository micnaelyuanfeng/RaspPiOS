#ifndef _SYS_API_H_
#define _SYS_API_H_

void 	 mmio_write(uint32_t reg_addr, uint32_t data);
uint32_t mmio_read(uint32_t reg_addr);
void 	 delay(uint32_t count);
int      get_el(void);
void     enable_interrupt(void);
void     disable_interrupt(void);
void     build_vtb(void);
uint32_t read_stack(void);
void     update_ustack(uint64_t sp);

#endif 