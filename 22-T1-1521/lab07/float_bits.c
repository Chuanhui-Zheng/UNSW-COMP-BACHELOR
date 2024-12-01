// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    // PUT YOUR CODE HERE
    float_components_t bits;
    bits.sign = f >> 31;
    bits.exponent = (f << 1) >> 24;
    bits.fraction = (f << 9) >> 9;
    return bits;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    // PUT YOUR CODE HERE
    if (f.exponent ==255){
        if (f.fraction != 0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    if (f.sign != 0){
        return 0;
    }
    // PUT YOUR CODE HERE
    if ((f.exponent != 255) || (f.fraction != 0)){
            return 0;
    }
    return 1;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    if (f.sign == 0){
        return 0;
    }
    // PUT YOUR CODE HERE
    if ((f.exponent != 255) || (f.fraction != 0)){
            return 0;
    }
    return 1;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    // PUT YOUR CODE HERE
    if (f.exponent == 0){
        return 1;
    }
    else{
        return 0;
    }
}
