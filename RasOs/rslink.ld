ENTRY(__start)

SECTIONS
{
	.text.boot:
	{
		*(.text.boot)
	}

	.rodata:
	{
		*(.rodata)
	}

	.data:
	{
		*(.data)
	}

	_bss_start = .;
	.bss:
	{
		*(.bss)
	}
	_bss_end = .;
}
