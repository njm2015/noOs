[bits 32]

gdt_start:

null_descriptor:
	dd 0x0
	dd 0x0

code_descriptor:
	dw 0xffff
	dw 0x0
	db 0x0
	db 0x9a
	db 11001111b
	db 0x0

data_descriptor:
	dw 0xffff
	dw 0x0
	db 0x0
	db 0x93
	db 11001111b
	db 0x0

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start

CODE_SEG equ code_descriptor - gdt_start
DATA_SEG equ data_descriptor - gdt_start
