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
#include "cr.h"
#include "console.h"
#include "ps2.h"

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

extern void* console_char_buf;

void kernel_main(uint32_t magic_number, uint32_t mb_addr) {

    if (magic_number != MULTIBOOT_BOOTLOADER_MAGIC)
        return;

    multiboot_info_t* mbi = (multiboot_info_t*) mb_addr;
    display_init(mbi);
    console_init(get_display_width() / CHAR_WIDTH, get_display_height() / CHAR_HEIGHT, (char**) &console_char_buf);

    PIC_remap(0x20, 0x28);
    clear_all_irqs();

#ifndef SERIAL 
    keyboard_init(); 
    ps2_init();
#endif

    enable_interrupts();

#ifdef SERIAL
    while (1) {

        char serial_input = read_serial();
        if (serial_input > 32 && serial_input < 126)
            PUTC(serial_input);        

    }
#endif

    /*
    typec('a');
    typec('b');
    typec('c');
    typec('\n');
    types("hello-hello-hello\n");

    console_clear();
    console_sync();    
    */

}
