#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
//#include "jetbrains_mono.h"
#include "ibm.h"
//#include "font.h"

#define WIDTH 640
#define HEIGHT 400
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

#define COLOR_WHITE 0x00ffffff
#define COLOR_RED 0x00ff0000
#define COLOR_GREEN 0x0000ff00
#define COLOR_BLUE 0x000000ff

size_t cursor_pos;     // (j * WIDTH) + i
uint32_t* fb;

void put_pixel(size_t x, size_t y, uint32_t color) {

    *(fb + (WIDTH * y) + x) = color;

}

void put_pixel_in_cursor_block(size_t x, size_t y, uint32_t color) {

    size_t cursor_x = cursor_pos % WIDTH;
    size_t cursor_y = cursor_pos / WIDTH;
    put_pixel(cursor_x + x, cursor_y + y, color);

}

void putc_color(unsigned char c, uint32_t color) {

    for (size_t i = 0; i < CHAR_HEIGHT; ++i) {        // bitmap row
        for (size_t j = 0; j < CHAR_WIDTH; ++j) {    // bitmap column

            if (font_map[c * CHAR_HEIGHT + i] & (1 << (CHAR_WIDTH-j)))
                put_pixel_in_cursor_block(j, i, color);

        }
    }

    cursor_pos += CHAR_WIDTH;

}

void putc(unsigned char c) {

    putc_color(c, COLOR_WHITE);

}

void puts(char* s) {

    for (size_t pos = 0; s[pos] != 0; ++pos)
        putc(s[pos]);

}

void kernel_main(uint32_t magic_number, uint32_t mb_addr) {

    if (magic_number != MULTIBOOT_BOOTLOADER_MAGIC)
        return;

    multiboot_info_t* mbi = (multiboot_info_t*) mb_addr;
    fb = (uint32_t*) mbi->framebuffer_addr;

    puts("ABCDEFG");

}
