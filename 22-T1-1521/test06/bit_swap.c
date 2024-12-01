//Blair z5351042

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t bit_swap(uint64_t value)
{
    return ((value & 0xAAAAAAAAAAAAAAAA) >> 1) | ((value & 0x5555555555555555) << 1);
}
