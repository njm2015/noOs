#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "font/ibm.h"

#ifndef DISPLAY_H
#define DISPLAY_H 

// TODO bring this config into a 
// global display context
#define WIDTH 640
#define HEIGHT 400
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16
#define CURSOR_HEIGHT 3
extern size_t cursor_pos;
extern uint32_t* fb;

#define COLOR_WHITE 0x00ffffff
#define COLOR_RED 0x00ff0000
#define COLOR_GREEN 0x0000ff00
#define COLOR_BLUE 0x000000ff
#define COLOR_BLACK 0x00000000

// TODO write documentation for these methods
void put_pixel(size_t x, size_t y, uint32_t color);
void put_pixel_in_cursor_block(size_t x, size_t y, uint32_t color);
void putc_color(unsigned char c, uint32_t color);
void putc(unsigned char c);
void puts(char* s);
void type(char* s);
void color_cursor(uint32_t color);
void draw_cursor();
void undraw_cursor();
void set_cursor(size_t pos);
void inc_cursor();

#endif
