// Convert a 16-bit signed integer to a string of binary digits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value){
    char *name;
    name = (char *)malloc(17 * sizeof(char));
    name[16] = '\0';
    int i = 15;
    int x = 1;
    while (i >= 0){
        int res = value & x;
        if (res != x){
            name[i] = '0';
        }
        else{
            name[i] = '1';
        }
        i--;
        x <<= 1;
    }
    return name;
}