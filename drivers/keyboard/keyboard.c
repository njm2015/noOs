#include "keyboard.h"

void init_keyboard() {

    IRQ_clear_mask(1);                              /* enable IRQ1 line */
    set_idt_entry(0x21, (uint32_t) keyboard_isr);   /* set IDT entry */

}

void keyboard_isr() {

    INTERRUPT_START;

    uint8_t scancode = inw(KEYBOARD_SCANCODE_PORT);
    if (scancode < 58) {

        char c = keymap[scancode];
        if (c > 0) {
        
            typec(c);

        } else {

            // do control char stuff here

        }

    }

    handle_interrupt(1);
    INTERRUPT_END;

}
