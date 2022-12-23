MBALIGN equ 1 << 0
MEMINFO equ 1 << 1
FRAMEBUFFER equ 1 << 2
FLAGS equ MBALIGN | MEMINFO | FRAMEBUFFER
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
bits 32
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    dd 0,0,0,0,0
    dd 0
    dd 640
    dd 400
    dd 32

section .text
bits 32
global _start:function (_start.end - _start)
_start:

    sgdt [tgdt]
        
    lgdt [gdt_descriptor]
    jmp CODE_SEG:.far_jmp 

.far_jmp:

    mov edx, DATA_SEG
    mov ds, edx
    mov ss, edx
    mov es, edx
    mov fs, edx
    mov gs, edx

    mov esp, stack_top  ; small kernel stack
   
    push ebx            ; Multiboot Info Struct Address.
    push eax            ; Multiboot MAGIC number.

    sgdt [tgdt]

    extern kernel_main
    call kernel_main    ; call kernel C entry point

    cli
.hang:  hlt
    jmp .hang
.end:

%include 'gdt.asm'

section .bss
bits 32
align 16
    stack_bottom:
    resb 16384          ; 16 KB stack.
    stack_top:

global cursor_pos
cursor_pos: dw 0

global fb
fb: dw 0
tgdt: times 6 db 0
