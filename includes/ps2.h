#include <stddef.h>
#include <stdint.h>

#include "idt.h"
#include "pic.h"
#include "io.h"

#ifndef PS2_H
#define PS2_H

#define PS2_SCANCODE_PORT 0x60

extern void ps2_isr();

void ps2_init();

#endif
