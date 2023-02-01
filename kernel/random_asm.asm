global rdseed32_guard
rdseed32_guard:
    push ebp
    mov ebp, esp
    push ebx

    mov eax, 7
    mov ecx, 0
    cpuid
    shr ebx, 18
    and ebx, 1
    jz .not_avail
    mov ecx, 100

.retry:
    rdseed eax
    jc .done
    loop .retry

.not_avail:
    mov eax, 0xfffffffe

.done:
    pop ebx
    mov esp, ebp
    pop ebp
    ret

global rdrand32_guard
rdrand32_guard:
    push ebp
    mov ebp,esp
    push ebx 

    mov eax, 1
    mov ecx, 0
    cpuid
    shr ecx, 30
    and ecx, 1
    jz .not_avail

    mov ecx, 100
.retry:
    rdrand eax
    jc .done
    loop .retry

.not_avail:
    mov eax, 0xfffffffd

.done:
    pop ebx
    mov esp, ebp
    pop ebp
    ret
