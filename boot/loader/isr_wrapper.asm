;global void_wrapper
;void_wrapper:
;    pushad
;    mov al, 0x20
;    mov dx, 0x20
;    out dx, al
;    popad 
;    iret

;global irq1_wrapper
;irq1_wrapper:
;    pushad
;    in al, 0x60
;    push 0x61
;    mov al, 0x20
;    mov dx, 0x20
;    out dx, al
;    extern typec
;    call typec
;    pop eax
;    extern irq1
;    call irq1
;    popad
;    iret

;global test_irq
;test_irq:

;    extern tidt
;    sidt [tidt]
;    int 0x31
;    ret
