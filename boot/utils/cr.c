#include "cr.h"

uint32_t get_cr0() {

    uint32_t res;
    __asm__(
        "movl %%cr0, %%eax  \n"
        "movl %%eax, %0     \n"
        : "=r" (res)
        :
        : "%eax"
    );

    return res;

}
