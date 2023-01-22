#ifndef TEXT_H
#define TEXT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "display.h"
#include "font/ibm.h"
#include "color.h"

// TODO write documentation for these methods
void draw_char(unsigned char c, uint32_t cursor_x, uint32_t cursor_y, uint32_t color);
void redraw_char(char* buf, uint32_t idx, uint32_t row_width);

#endif
