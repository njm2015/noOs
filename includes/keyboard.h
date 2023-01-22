#include <stddef.h>
#include <stdint.h>

#include "idt.h"
#include "pic.h"
#include "io.h"
#include "display.h"

#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_SCANCODE_PORT 0x60

void keyboard_init();
//void keyboard_isr();

//void temp_keyboard_isr();

extern const char scancode_map[];

#endif
