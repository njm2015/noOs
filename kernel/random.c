#include "random.h"

uint32_t rand() {

    seed = (a * seed + c) % m;
    
    uint32_t mask = 0x3;
    uint32_t lowest_2_bits = seed & mask;
    
    if (lowest_2_bits == 1)
        lowest_2_bits = 2;
    else if (lowest_2_bits == 2)
        lowest_2_bits = 1;

    uint32_t swapped = (seed & (~mask)) | lowest_2_bits;
    return swapped;

}
