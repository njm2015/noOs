#include <stddef.h>
#include <stdint.h>

struct segment_descriptor_32_t {
    uint16_t limit1; 
    uint16_t base1;
    uint8_t  base2;
    uint8_t  access;
    uint8_t  limit_flags;
    uint8_t  base3;
} __attribute__((packed)) segment_descriptor_32_t;

struct gdt_t {
    uint16_t size;
    uint32_t start;
} __attribute__((packed)) gdt_t;

struct segment_descriptor_32_t segments[] = {

    { 0, 0, 0, 0, 0, 0 },
    { .limit1 = 0xffff, .base1 = 0, .base2 = 0, .access = 0x9a, .limit_flags = 0xcf, .base3 = 0 },
    { .limit1 = 0xffff, .base1 = 0, .base2 = 0, .access = 0x93, .limit_flags = 0xcf, .base3 = 0 }

};

struct gdt_t gdt_addr = { .size = sizeof(segment_descriptor_32_t) * sizeof(segments) - 1, .start = (uint32_t) &segments };

const uint32_t _code_seg = 1 * sizeof(segment_descriptor_32_t);
const uint32_t _data_seg = 2 * sizeof(segment_descriptor_32_t);
