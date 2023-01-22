#include <stddef.h>
#include <stdint.h>

#include "color.h"
#include "text.h"

typedef struct {
    uint32_t cursor_pos;
    char** char_buf;
    uint32_t width;
    uint32_t height;
    uint8_t cursor_height;
} console_ctx_t;

static console_ctx_t console_ctx;

void console_init(uint32_t console_width, uint32_t console_height, char** char_buf);
console_ctx_t* get_console_ctx();
void color_cursor(uint32_t color);      // refactor this method out
void draw_cursor();
void undraw_cursor();
static inline void inc_cursor();
void scroll();
void putc(unsigned char c);
void typec(unsigned char c);
void types(char* s);
void console_reinit();
void console_clear();
void console_sync();
