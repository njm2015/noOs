; reserved bss memory
section .bss
bits 32
align 16
    stack_bottom:
    resb 1048576        ; 1 MB stack.
    stack_top:

global cursor_pos
cursor_pos: resd 1

global interrupts
interrupts: resq 256

global idt_addr
idt_addr: resb 6

global console_char_buf
console_char_buf: resb DISPLAY_HEIGHT * ADDR_SIZE + (DISPLAY_WIDTH / CHAR_WIDTH) * (DISPLAY_HEIGHT / CHAR_HEIGHT)

