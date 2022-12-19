ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
	
	. = 1M;


	.text : 
	{
        . = ALIGN(8);
        KEEP(*(.multiboot))
        *(.text)
        *(.rodata)
	}
    
    . = ALIGN(4K);
	.data :
	{
		*(.data)
	}
    
    . = ALIGN(4K);
	.bss :
	{
		*(COMMON)
		*(.bss)
	}

    /DISCARD/ : { *(.fini_array*) *(.comment) }
}
