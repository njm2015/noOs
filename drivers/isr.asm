SCANCODE_PORT equ 0x60

global default_isr
default_isr:
    pushad                  ; save current working regs - only needed since we're calling handle_interrupt
    mov ebx, 0x8
    jmp interrupt_end

;
;
;
;

global keyboard_isr
keyboard_isr:
    pushad                  ; save all current registers

    mov ebx, 0x1            ; argument for interrupt_end - DO NOT CLOBBER

    xor edx, edx            ; only really need to clear dh
    in eax, SCANCODE_PORT   ; read scancode (4 bytes, but we don't care about scancode sequences)
    mov dl, al

    cmp dl, 57              ; we only care about scancodes less than 58
    ja interrupt_end        ; unsigned comparison

    xor eax, eax            ; clear edx since we'll push it to the stack for the typec call

    extern scancode_map
    mov al, [scancode_map + edx]     ; grab char from scancode map
    
    test al, al             ; 
    jz .control_char        ; we've mapped control chars to 0x0

    mov eax, 0x61           ; TEMP DELETE
    extern typec
    push eax                ;
    call typec              ; type character to the console
    add esp, 0x4            ; ~ pop nowhere

    jmp interrupt_end

.control_char:
    jmp interrupt_end

;
;
;
;

global ps2_isr
ps2_isr:
    pushad

    mov ebx, 0xb

    in eax, SCANCODE_PORT
    jmp interrupt_end

;
;
;
;

handle_interrupt:
    mov al, 0x20
    cmp bl, 0x8
    jb .clear_lower
    out 0xa0, al
.clear_lower
    out 0x20, al
    ret

;
;
;
;

; expects interrupt # to handle in ebx
interrupt_end:
    call handle_interrupt   ; reset interrupt mask - mark this as handled

    popad               ; restore pre-interrupt registers
    iret                ; return from interrupt


