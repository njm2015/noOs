#include <stdint.h>

#ifndef RANDOM_H
#define RANDOM_H

#define RDSEED_FAIL 0xfffffffe
#define RDRAND_FAIL 0xfffffffd

static uint32_t seed = 64297531;
static const uint32_t a = 37769685;
static const uint32_t c = 12345;
static const uint32_t m = 2e31;
uint32_t rand();

//extern uint32_t rdseed32_guard();
//extern uint8_t rdseed8();

#endif
