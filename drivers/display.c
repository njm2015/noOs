/** @file display.c
 *  @brief Implementation of the noOs display driver
 *
 *  Functions only related to manipulating the bitmap framebuffer
 *
 *  @author Nathaniel Murphy
 *  @bug No known bugs.
 *
 */

#include "display.h"

void display_init(multiboot_info_t* mbi) {

    display_ctx.fb = (uint32_t*) mbi->framebuffer_addr;
    display_ctx.width = mbi->framebuffer_width;
    display_ctx.height = mbi->framebuffer_height;
    display_ctx.depth = mbi->framebuffer_bpp;

}

display_ctx_t* get_display_ctx() { return &display_ctx; }

uint32_t get_display_width() { return display_ctx.width; }

uint32_t get_display_height() { return display_ctx.height; }

void put_pixel(size_t x, size_t y, uint32_t color) {

    *(display_ctx.fb + (display_ctx.width * y) + x) = color;

}

void put_pixel_linear(uint32_t idx, uint32_t color) {

    *(display_ctx.fb + idx) = color;

}

uint32_t get_pixel(size_t x, size_t y) {
    
    return *(display_ctx.fb + (display_ctx.width * y) + x);

}

void copy_pixel(size_t x_src, size_t y_src, size_t x_dst, size_t y_dst) {

    put_pixel(x_dst, y_dst, get_pixel(x_src, y_src));

}
