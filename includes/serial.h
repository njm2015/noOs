#include <stddef.h>
#include <stdint.h>

#include "io.h"

#ifndef SERIAL_H
#define SERIAL_H

#define SERIAL_PORT 0x3f8

void init_serial();
int serial_received();
char read_serial();
int is_transmit_empty();
void write_serial(char a);

/* serial display functions */
void putc_serial(char c);
void puts_serial(char* s);

#endif
