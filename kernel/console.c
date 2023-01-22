#include "console.h"

void console_init(uint32_t console_width, uint32_t console_height, char** char_buf) {

    console_ctx.cursor_pos = 0;
    console_ctx.width = console_width;
    console_ctx.height = console_height;
    console_ctx.cursor_height = 3;

    console_ctx.char_buf = char_buf;
    for (size_t i = 0; i < console_height; ++i)
        console_ctx.char_buf[i] = ((char*) (char_buf + console_height)) + (i * console_width);

    for (size_t i = 0; i < console_height * console_width; ++i)
        console_ctx.char_buf[0][i] = 0;

    draw_cursor();

}

console_ctx_t* get_console_ctx() { return &console_ctx; }

void color_cursor(uint32_t color) {

    for (size_t vert_idx = CHAR_HEIGHT; vert_idx > CHAR_HEIGHT - console_ctx.cursor_height; --vert_idx) {
        for (size_t horiz_idx = 0; horiz_idx < CHAR_WIDTH; ++horiz_idx) {
            size_t cursor_x = console_ctx.cursor_pos % (console_ctx.width * CHAR_WIDTH);
            size_t cursor_y = console_ctx.cursor_pos / (console_ctx.width * CHAR_WIDTH);
            put_pixel(cursor_x + horiz_idx, cursor_y + vert_idx, color);
        }
    }

}

void draw_cursor() { color_cursor(COLOR_WHITE); }
void undraw_cursor() { color_cursor(COLOR_BLACK); }
static inline void inc_cursor() { console_ctx.cursor_pos += CHAR_WIDTH; }

void scroll() {

    for (size_t vert_idx = CHAR_HEIGHT; vert_idx < console_ctx.height * CHAR_HEIGHT; ++vert_idx) {
        for (size_t horiz_idx = 0; horiz_idx < console_ctx.width * CHAR_WIDTH; ++horiz_idx) {
            copy_pixel(horiz_idx, vert_idx, horiz_idx, vert_idx-CHAR_HEIGHT);
        }
    }

    for (size_t vert_idx = (console_ctx.height * CHAR_HEIGHT - CHAR_HEIGHT); vert_idx < console_ctx.height * CHAR_HEIGHT; ++vert_idx) {
        for (size_t horiz_idx = 0; horiz_idx < console_ctx.width * CHAR_WIDTH; ++horiz_idx) {
            put_pixel(horiz_idx, vert_idx, COLOR_BLACK);
        }
    }

}

void putc(unsigned char c) {

    uint32_t curs = console_ctx.cursor_pos;
    uint32_t disp_width = get_display_width();

    if (c == 0xa) {

        curs = ((curs / disp_width)+ CHAR_HEIGHT) * disp_width;

    } else {

        console_ctx.char_buf[0][curs / CHAR_WIDTH] = c;
        draw_char(c, curs % disp_width, curs / disp_width, COLOR_WHITE);
        curs += CHAR_WIDTH;

        // wraparound
        if ((curs % disp_width) < CHAR_WIDTH)
            curs = ((curs / disp_width - 1) + CHAR_HEIGHT) * disp_width;

    }

    if (curs + CHAR_WIDTH >= disp_width * get_display_height()) {
        scroll();
        curs -= (disp_width * CHAR_HEIGHT);
    }

    console_ctx.cursor_pos = curs;

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
    for (size_t pos = 0; s[pos] != 0; ++pos)
        putc(s[pos]);
    draw_cursor();

}

void console_reinit() {

    console_clear();
    console_init(console_ctx.width, console_ctx.height, console_ctx.char_buf);

}

void console_clear() {

    for (size_t i = 0; i < get_display_width() * get_display_height(); ++i)
        put_pixel_linear(i, COLOR_BLACK);

}

void console_sync() {

    console_clear();
    for (uint32_t i = 0; i < console_ctx.width * console_ctx.height; ++i)
        redraw_char(console_ctx.char_buf[0], i, console_ctx.width);    

}
