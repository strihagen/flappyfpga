#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdint.h>

int nextprime(int inval);

void rand_seed(uint32_t seed);
uint32_t randint(uint32_t min, uint32_t max);

#endif // __UTIL_H__



