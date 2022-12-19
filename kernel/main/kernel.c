#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "display.h"

extern uint32_t* fb;

void kernel_main(uint32_t magic_number, uint32_t mb_addr) {

    if (magic_number != MULTIBOOT_BOOTLOADER_MAGIC)
        return;

    multiboot_info_t* mbi = (multiboot_info_t*) mb_addr;
    fb = (uint32_t*) mbi->framebuffer_addr;

    puts("ABCDEFG");

}
