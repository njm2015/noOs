#include <stddef.h>
#include <stdint.h>

#include "idt.h"

void init_idt() {

    for (size_t i = 0; i < 256; ++i) {

        interrupt_descriptor_32_t d = { .selector = 0x8, .zero = 0, .type_attributes = 0x8e };
        void (**temp_ptr)() = &default_isr;
        //void (**temp_ptr)() = (i == 7 || i == 15) ? &spurious_isr : &default_isr;
        d.offset1 = (uint16_t) temp_ptr;
        d.offset2 = (uint16_t) (((uint32_t) temp_ptr) >> 16);
        interrupts[i] = d;

    }

    idt_addr = (idt_t) { .size = sizeof(interrupt_descriptor_32_t) * 256 - 1, .start = (uint32_t) &interrupts };

}

void set_idt_entry(uint8_t index, uint32_t callback) {

    interrupts[index].offset1 = (uint16_t) callback;
    interrupts[index].offset2 = (uint16_t) (callback >> 16);

}

void handle_interrupt(uint8_t i) {

    if (i > 7)
        outb(0xa0, 0x20);

    outb(0x20, 0x20);

}

void  spurious_isr() {}

void default_isr() {

    INTERRUPT_START;
    handle_interrupt(8);
    INTERRUPT_END;

}
