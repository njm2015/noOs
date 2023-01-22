MBALIGN equ 1 << 0
MEMINFO equ 1 << 1
FRAMEBUFFER equ 1 << 2
FLAGS equ MBALIGN | MEMINFO | FRAMEBUFFER
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

ADDR_SIZE equ 4     ; 4 bytes = 32 bit add

DISPLAY_WIDTH equ 640
DISPLAY_HEIGHT equ 400
CHAR_WIDTH equ 8
CHAR_HEIGHT equ 16

section .multiboot
bits 32
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    dd 0,0,0,0,0
    dd 0
    dd DISPLAY_WIDTH
    dd DISPLAY_HEIGHT
    dd 32

section .text
bits 32
global _start:function (_start.end - _start)
_start:

    extern gdt_addr
    lgdt [gdt_addr]

    jmp 0x8:.far_jmp 

.far_jmp:

    mov edx, 0x10
    mov ds, edx
    mov ss, edx
    mov es, edx
    mov fs, edx
    mov gs, edx

    mov esp, stack_top  ; small kernel stack
   
    push ebx            ; Multiboot Info Struct Address.
    push eax            ; Multiboot MAGIC number.

    extern idt_init
    call idt_init

    lidt [idt_addr]

    extern kernel_main
    call kernel_main    ; call kernel C entry point

.hang:  hlt
    jmp .hang
.end:

%include "boot/bss.asm"
