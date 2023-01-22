#include "ps2.h"

void ps2_init() {

    IRQ_clear_mask(12);         /* enable IRQ 12 (ps2) */
    IRQ_clear_mask(2);          /* enable Slave PIC */
    set_idt_entry(0x2c, (uint32_t) ps2_isr);

}
