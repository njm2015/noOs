#include "display.h"

void put_pixel(size_t x, size_t y, uint32_t color) {

    *(fb + (WIDTH * y) + x) = color;

}

uint32_t get_pixel(size_t x, size_t y) {
    
    return *(fb + (WIDTH * y) + x);

}

void copy_pixel(size_t x_src, size_t y_src, size_t x_dst, size_t y_dst) {

    put_pixel(x_dst, y_dst, get_pixel(x_src, y_src));

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

    if (cursor_pos >= WIDTH * HEIGHT)
        scroll();

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

void typec(unsigned char c) {

    undraw_cursor();
    putc(c);
    draw_cursor(); 

}

void types(char* s) {

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

void scroll() {

    for (size_t i = CHAR_HEIGHT; i < HEIGHT; ++i) {
        for (size_t j = 0; j < WIDTH; ++j) {
            copy_pixel(j, i, j, i-CHAR_HEIGHT);
        }
    }

    for (size_t i = (HEIGHT-CHAR_HEIGHT); i < HEIGHT; ++i) {
        for (size_t j = 0; j < WIDTH; ++j) {
            put_pixel(j, i, COLOR_BLACK);
        }
    }

    //undraw_cursor();
    cursor_pos -= (WIDTH * CHAR_HEIGHT);
    //draw_cursor();

}
