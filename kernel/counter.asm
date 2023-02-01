[bits 32]

global counter
counter:
    push ebp
    mov ebp, esp

    mov edx, 0x20
.outer:
    mov ecx, 0xffffffff
.count_start:
    xor eax, eax
    add eax, 2
    sub ecx, 1
    jnz .count_start
    sub edx, 1
    jnz .outer

    mov esp, ebp
    pop ebp
    ret
