#include <stddef.h>
#include <stdint.h>

struct SegmentDescriptor32 {
    uint16_t limit1 {};
    uint16_t base1  {};
    uint8_t  base2  {};
    uint8_t  access {};
    uint8_t  limit_flags {};
    uint8_t  base3  {};
};

struct gdt {
    uint16_t size;
    uint32_t start;
};

SegmentDescriptor32 segments[] = {

    { },
    { .limit1 = 0xffff, .access = 0x9a, .limit_flags = 0xcf },
    { .limit1 = 0xffff, .access = 0x93, .limit_flags = 0xcf }

};

gdt global_gdt = { .size = sizeof(SegmentDescriptor32) * sizeof(segments), .start = &segments };

const code_seg = 1 * sizeof(SegmentDescriptor32);
const data_seg = 2 * sizeof(SegmentDescriptor32);
