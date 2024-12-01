#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]){
    FILE *f = fopen(argv[1], "wb+");
    uint c_a = atoi(argv[2]);
    uint c_b = atoi(argv[3]);
    if (c_b < 0 || c_b > 65535){
        perror(argv[3]);
        return 1;
    }
    if (c_a < 0 || c_a > 65535){
        perror(argv[2]);
        return 1;
    }
    int sum = c_b - c_a + 1;
    int i = 0;
    while (i < sum){
        uint ch1 = c_a >> 8;
        fputc(ch1, f);
        uint ch2 = c_a;
        ch2 <<= 24;
        ch2 >>= 24;
        fputc(ch2, f);
        c_a++;
        i++;
    }
    fclose(f);
    return 0;
}