ENTRY(start)
 
SECTIONS
{
    /* Starts at LOADER_ADDR. */
    /* For AArch64, use . = 0x80000; */
    /*. = 0x80000;*/
    start = .;
    text_start = .;
    .text :
    {
        KEEP(*(.text.boot))
        *(.text)
    }
    . = ALIGN(4096); /* align to page size */
    text_end = .;
 
    rodata_start = .;
    .rodata :
    {
        *(.rodata)
    }
    . = ALIGN(4096); /* align to page size */
    rodata_end = .;
 
    data_start = .;
    .data :
    {
        *(.data)
    }
    . = ALIGN(4096); /* align to page size */
    data_end = .;
 
    bss_start = .;
    .bss :
    {
        bss = .;
        *(.bss)
    }
    . = ALIGN(4096); /* align to page size */
    bss_end = .;
    bss_size = bss_end - bss_start + 1;
    end = .;
}