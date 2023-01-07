#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "gdt.h"
#include "display.h"
#include "pic.h"
#include "idt.h"
#include "keyboard.h"
#include "serial.h"

#if defined (SERIAL)
    #define PUTC(c) putc_serial(c)
#else
    #define PUTC(c) typec(c)
#endif

#if defined (SERIAL)
    #define PUTS(c) puts_serial(c)
#else
    #define PUTS(c) types(c)
#endif

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

#ifndef SERIAL 
    init_keyboard(); 
    init_ps2();
#endif

    enable_interrupts();

    PUTS("start the clock...");

    double arr[800];

    for (size_t iter = 0; iter < 100; ++iter) {
        for (size_t iter_j = 0; iter_j < 1000; ++iter_j) {
            arr[0] = 0.8 * iter_j;
            arr[1] = 0.2 * iter_j;

            for (size_t i = 2; i < 800; ++i) {
                arr[i] = arr[i-1] * arr[i] - arr[i-2];
                arr[2] = arr[i];
            }
        }
    }


    PUTS("hello user, enter some input");

#ifdef SERIAL
    while (1) {

        char serial_input = read_serial();
        if (serial_input > 32 && serial_input < 126)
            PUTC(serial_input);        

    }
#endif

}
