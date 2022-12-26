#include <stddef.h>
#include <stdint.h>

#include "idt.h"
#include "pic.h"
#include "io.h"
#include "display.h"

#ifndef KEYBOARD_H
#define KEYBOARD_H

#define SCANCODE_PORT 0x60

void init_keyboard();
void keyboard_isr();

static const char keymap[] = {
    0x0,    /* no value */
    0x1b,   /* ESC */
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    0x0,    /* control (backspace) */
    0x9,    /* tab */
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    0xa,    /* enter (newline) */
    0x0,    /* control (CTRL) */
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    '\'',
    '`',
    0x0,    /* control (lshift) */
    '\\',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    0x0,    /* control (rshift) */
    0x0,    /* control (prtsc) */
    0x0,    /* control (alt) */
    ' ',
    0x0    /* control (caps lock) */
};


#endif
