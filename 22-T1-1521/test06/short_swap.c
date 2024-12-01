//Blair z5351042

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

uint16_t short_swap(uint16_t value)
{
    return ((value << 8) & 0xff00) | ((value >> 8) & 0x00ff);
}