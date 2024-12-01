//Blair z5351042

#include <stdint.h>

/**
 * Return `1` if `value` *is* "balanced"
 * Return `0` if `value` *is not* "balanced"
 *
 * a number is said to be balanced iff it has the same number of bits set
 * set in its upper 16 bits as it does in its lower 16 bits.
 *
 * 0x10500c04 in binary, is 0b00010000010100000000110000000100
 * 0x10500c04 is balanced because there are 3 bits set in the upper 16 bits
 * and 3 bits set in the lower 16 bits
 * given 0x10500c04 final_q3 should return 1.
 *
 * 0x04300090 in binary, is 0b00000100001100000000000010010000
 * 0x04300090 is not balanced because there are 3 bits set in upper 16 bits
 * and 2 bits set in the second 16 bits.
 * given 0x04300090 final_q3 should return 0.
**/

int final_q3(uint32_t value) {
    uint32_t upper = 0xFFFF0000;
    uint32_t lower = 0x0000FFFF;
    uint32_t upper_bits = value & upper;
    uint32_t lower_bits = value & lower;
    int upper_return = 0;
    int lower_return = 0;

    while (upper_bits != 0) {
        if (upper_bits & 0x1) {
            upper_return++;
        }
        upper_bits = upper_bits >> 1;
    }

    while (lower_bits != 0) {
        if (lower_bits & 0x1) {
            lower_return++;
        }
        lower_bits = lower_bits >> 1;
    }

    return upper_return == lower_return;
}