ENTRY(__start)

SECTIONS
{
    . = 0x80000;

    .text :
    {
        *(.text.boot)
        *(.text)
    }

    .data :
    {
    
    }

    .bss :
    {
    
    }
}