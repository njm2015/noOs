#include "keyboard.h"

extern void keyboard_isr();

void keyboard_init() {

    IRQ_clear_mask(1);                              /* enable IRQ1 line */
    set_idt_entry(0x21, keyboard_isr);   /* set IDT entry */

}

const char scancode_map[] = {
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

/*
void keyboard_isr() {

    INTERRUPT_START;

    uint8_t scancode = inw(KEYBOARD_SCANCODE_PORT);
    if (scancode < 58) {

        char c = keymap[scancode];
        if (c > 0) {
        
            typec(c);

        } else {

            // do control char stuff here

        }

    }

    handle_interrupt(1);
    INTERRUPT_END;

}
*/
