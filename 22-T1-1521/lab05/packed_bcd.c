#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value){

    // PUT YOUR CODE HERE
    int i = 32;
    long result = 0;
    long x = 2147483648;
    long pow = 10000000;
    int d = 0;
    while (i > 0){
        d = 0;
        for(int j = 0; j < 4; j++){
            int temp = packed_bcd_value & x;
            if (temp == 0){
                d <<= 1;
            }
            else{
                d <<= 1;
                d |= 1;
            }
            x >>= 1;
            i--;
        }
    result += d * pow;
    pow /= 10;
    }
return result;
}