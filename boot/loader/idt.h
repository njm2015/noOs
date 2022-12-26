#include <stddef.h>
#include <stdint.h>

#include "io.h"

#ifndef IDT_H
#define IDT_H

#define INTERRUPT_START asm volatile("pushal");
#define INTERRUPT_END asm volatile("popal"); \
                      asm volatile("leave");    /* pop so we can use C calling convention */ \
                      asm volatile("iret");

typedef struct interrupt_descriptor_32_t {
    uint16_t offset1;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type_attributes;
    uint16_t offset2;
} __attribute__((packed)) interrupt_descriptor_32_t;

typedef struct idt_t {
    uint16_t size;
    uint32_t start;
} __attribute__((packed)) idt_t;

extern interrupt_descriptor_32_t interrupts[256];
extern idt_t idt_addr;

void init_idt();
void set_idt_entry(uint8_t index, uint32_t callback);
void handle_interrupt(uint8_t i);
void default_isr();

#endif
