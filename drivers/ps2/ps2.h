#include <stddef.h>
#include <stdint.h>

#include "idt.h"
#include "pic.h"
#include "io.h"

#ifndef PS2_H
#define PS2_H

#define PS2_SCANCODE_PORT 0x60

void init_ps2();
void ps2_isr();

#endif
