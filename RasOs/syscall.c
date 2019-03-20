#include "Include\types.h"
#include "Include\api.h"

void* const syscall_table[] = {
    _sys_printf,
    _sys_fork,
    _sys_pmalloc,
    _sys_exit
};

void _sys_printf(uint8_t* str_buf)
{
    __sys_printf(str_buf);
}

enum RETURN_STATUS _sys_fork(uint64_t ustack)
{
    __sys_fork(ustack);
}

uint64_t _sys_pmalloc()
{
    __sys_pmalloc();
}

void _sys_exit()
{
    __sys_exit();
}