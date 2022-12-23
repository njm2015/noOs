#include "display.h"

void put_pixel(size_t x, size_t y, uint32_t color) {

    *(fb + (WIDTH * y) + x) = color;

}

void put_pixel_in_cursor_block(size_t x, size_t y, uint32_t color) {

    size_t cursor_x = cursor_pos % WIDTH;
    size_t cursor_y = cursor_pos / WIDTH;
    put_pixel(cursor_x + x, cursor_y + y, color);

}

void putc_color(unsigned char c, uint32_t color) {

    // char wraparound
    if ((cursor_pos % WIDTH) + CHAR_WIDTH >= WIDTH)
        cursor_pos = ((cursor_pos / WIDTH) + CHAR_HEIGHT) * WIDTH;

    // newline
    if (c == 0xa) {
        cursor_pos = ((cursor_pos / WIDTH) + CHAR_HEIGHT) * WIDTH;
        return;
    }

    for (size_t i = 0; i < CHAR_HEIGHT; ++i) {        // bitmap row
        for (size_t j = 0; j < CHAR_WIDTH; ++j) {     // bitmap column

            if (font_map[c * CHAR_HEIGHT + i] & (1 << (CHAR_WIDTH-j)))
                put_pixel_in_cursor_block(j, i, color);

        }
    }

    inc_cursor();

}

void putc(unsigned char c) {

    putc_color(c, COLOR_WHITE);

}

void puts(char* s) {

    for (size_t pos = 0; s[pos] != 0; ++pos)
        putc(s[pos]);

}

void type(char* s) {

    undraw_cursor();
    puts(s);
    draw_cursor();

}

void color_cursor(uint32_t color) {

    for (size_t i = CHAR_HEIGHT; i > CHAR_HEIGHT - CURSOR_HEIGHT; --i)
        for (size_t j = 0; j < CHAR_WIDTH; ++j)
            put_pixel_in_cursor_block(j, i, color);

}

void draw_cursor() { color_cursor(COLOR_WHITE); }
void undraw_cursor() { color_cursor(COLOR_BLACK); } 
void inc_cursor() { cursor_pos += CHAR_WIDTH; }

