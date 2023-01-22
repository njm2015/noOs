#include "text.h"

void draw_char(unsigned char c, uint32_t cursor_x, uint32_t cursor_y, uint32_t color) {

    for (size_t vert_idx = 0; vert_idx < CHAR_HEIGHT; ++vert_idx) {        // bitmap row
        for (size_t horiz_idx = 0; horiz_idx < CHAR_WIDTH; ++horiz_idx) {     // bitmap column

            if (font_map[c * CHAR_HEIGHT + vert_idx] & (1 << (CHAR_WIDTH - horiz_idx)))
                put_pixel(cursor_x + horiz_idx, cursor_y + vert_idx, color);

        }
    }

}

void redraw_char(char* buf, uint32_t idx, uint32_t row_width) {

    draw_char(buf[idx], (idx * CHAR_WIDTH) % (row_width * CHAR_WIDTH), (idx * CHAR_WIDTH) / (row_width * CHAR_WIDTH), COLOR_WHITE);

}
