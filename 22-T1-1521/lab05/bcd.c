//Blair z5351042
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value){
    // PUT CODE HERE
    int w1 = 0;
    int w2 = 0;
    int bar = 32768;
    int i = 15;

    while (i >= 8){
        int aq = bcd_value & bar;
        w1 <<= 1;
        if (aq == bar){
            w1 |= 1;
        }
        i--;
        bar >>= 1;
    }
    while (i >= 0){
        int aq = bcd_value & bar;
        w2 <<= 1;
        if (aq == bar){
            w2 |= 1;
        }
        i--;
        bar >>= 1;
    }

    return w1 * 10 + w2;
}