/** @file display.h
 *  @brief Definition of the noOs display driver
 *
 *  Fucntions only related to manipulating the bitmap framebuffer
 *
 *  @author Nathaniel Murphy
 *  @bug No known bugs
 *
 */
#ifndef DISPLAY_H
#define DISPLAY_H 

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"

/** @brief holds information on the size and characteristrics of the framebuffer
 *
 *  Although this could be implemented using uint16_t and uint8_t, this matches
 *  the definition of the parameters in multiboot.h (except the framebuffer addr
 *  which is 64 bits in the multiboot definition).
 * 
 */
typedef struct {
    uint32_t* fb; 
    uint32_t width;
    uint32_t height;
    uint32_t depth;
} display_ctx_t;

/** @brief address for global display context
 *  
 *  extern since we expect the space to be allocated in a .bss declaration
 *
 */
static display_ctx_t display_ctx;

/** @brief function to initialize the display context
 *
 *  @param mbi Address of the multiboot_info struct
 */
void display_init(multiboot_info_t* mbi);

/** @brief function to share display context pointer
 *
 *  @return pointer to the global display ctx
 */
display_ctx_t* get_display_ctx();

/** @brief function to get the width of the display
 *
 *  @return ctx->width
 */
uint32_t get_display_width();

/** @brief function to get the height of the display
 *
 *  @return ctx->height
 */
uint32_t get_display_height();

/** @brief Changes the color of a pixel to the specified color
 *
 *  @param x X coordinate ([0,0] top left corner)
 *  @param y Y coordinate ([0,0] top left corner)
 *  @param color Color of changed pixel
 *
 */
void put_pixel(size_t x, size_t y, uint32_t color);

/** @brief Changes the color of a pixel to the specified color using linear fb addressing
 *
 * @param idx Linear index of the framebuffer to change
 * @param color Color of changed pixel
 *
 */
void put_pixel_linear(size_t idx, uint32_t color);

/** @brief Gets color of a pixel from the framebuffer
 *
 *  @param x X coordinate ([0,0] top left corner)
 *  @param y Y coordinate ([0,0] top left corner)
 *  @return Value of the pixel at the specified coordinates
 */
uint32_t get_pixel(size_t x, size_t y);

/** @brief Copies the value of one pixel to another
 *
 *  @param x_src Source X coordinate ([0,0] top left corner)
 *  @param y_src Source Y coordinate ([0,0] top left corner)
 *  @param x_dst Destination X coordinate ([0,0] top left corner)
 *  @param y_dst Destination Y coordinate ([0,0] top left corner)
 *
 */
void copy_pixel(size_t x_src, size_t y_src, size_t x_dst, size_t y_dst);

#endif
