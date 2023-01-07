#include "ps2.h"

void init_ps2() {

    IRQ_clear_mask(12);         /* enable IRQ 12 (ps2) */
    IRQ_clear_mask(2);          /* enable Slave PIC */
    set_idt_entry(0x2c, (uint32_t) ps2_isr);

}

void ps2_isr() {

    INTERRUPT_START;
    
    inw(PS2_SCANCODE_PORT);      /* clear port in case we use the same port for keyboard */ 
    handle_interrupt(12);
    
    INTERRUPT_END;

}
