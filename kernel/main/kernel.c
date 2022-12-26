#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "gdt.h"
#include "display.h"
#include "pic.h"
#include "idt.h"
#include "keyboard.h"

extern uint32_t* fb;
extern void (test_irq)(void);

void kernel_main(uint32_t magic_number, uint32_t mb_addr) {

    if (magic_number != MULTIBOOT_BOOTLOADER_MAGIC)
        return;

    multiboot_info_t* mbi = (multiboot_info_t*) mb_addr;
    fb = (uint32_t*) mbi->framebuffer_addr;

    init_idt();
    PIC_remap(0x20, 0x28);
    clear_all_irqs();
    init_keyboard(); 
    enable_interrupts();

    for (size_t i = 0; i < 24; ++i)
        types("hello\n");

    for (size_t i = 0; i < 70; ++i)
        typec('a');

}
