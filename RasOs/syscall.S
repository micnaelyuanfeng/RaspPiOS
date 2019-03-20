#include "syscall.h"

.global uprintf
uprintf:
    mov x8, #SYS_WRITE_NUMBER
    svc #0

    ret


.global upmalloc
upmalloc:
    mov x8, #SYS_MALLOC_NUMBER
    svc #0

    ret

    