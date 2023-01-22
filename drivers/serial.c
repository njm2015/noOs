#include "serial.h"

void init_serial() {
    
    outb(SERIAL_PORT + 1, 0x00);        // Disable all interrupts
    outb(SERIAL_PORT + 3, 0x80);        // Enable DLAB (set baut rate divisor)
    outb(SERIAL_PORT + 0, 0x03);        // set divisor to 3 (lo byte) 38400 baud
    outb(SERIAL_PORT + 1, 0x00);        //                  (hi byte)
    outb(SERIAL_PORT + 3, 0x03);        // 8 bits, no parity, one stop bit
    outb(SERIAL_PORT + 2, 0xc7);        // enable fifo, clear them, with 14 byte threshold
    outb(SERIAL_PORT + 4, 0x0b);        // IRQs enabled, RTS/DSR set
    outb(SERIAL_PORT + 4, 0x1e);        // set in loopback mode, test the serial chip
    outb(SERIAL_PORT + 4, 0xae);        // test serial chip (send byte 0xae and check if serial returns same byte

    // Check if serial is faulty (i.e: not same byte as sent)
    if (inb(SERIAL_PORT + 0) != 0xae)
        return;

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(SERIAL_PORT + 4, 0x0f);

}

int serial_received() {
    return inb(SERIAL_PORT + 5) & 1;
}

char read_serial() {
    while (serial_received() == 0);

    return inb(SERIAL_PORT);
}

int is_transmit_empty() {
    return inb(SERIAL_PORT + 5) & 0x20;
}

void write_serial(char a) {
    while (is_transmit_empty() == 0);
    
    outb(SERIAL_PORT, a);
}

void putc_serial(char c) {

    write_serial(c);

}

void puts_serial(char* s) {

    for (size_t pos = 0; s[pos] != 0; ++pos)
        putc_serial(s[pos]);

}
