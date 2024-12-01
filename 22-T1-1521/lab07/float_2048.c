// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
    float_components_t bits;
    bits.exponent = (f << 1) >> 24;
    bits.fraction = (f << 9) >> 9;
    if ((f << 1) >> 24 == 0 || ((f << 1) >> 24 == 255 && (f << 9) >> 9 != 0)){
        return f;
    }
    bits.exponent += 11;
    if (bits.exponent > 255){
        bits.exponent = 255;
        bits.fraction = 0;
    }
    return ((f >> 31) << 31) + (bits.exponent << 23) + bits.fraction;
}
