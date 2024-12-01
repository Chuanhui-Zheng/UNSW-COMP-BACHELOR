//Blair z5351042

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

int bit_count(uint64_t value){
    unsigned int res = 0;
    while (value){
        res += value & 1;
        value >>= 1;
    }
    return res;
}