//Blair z5351042
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *fpin = fopen(argv[1], "r");
    FILE *fpout = fopen(argv[2], "w");
    int min;
    while ((min = getc(fpin)) != EOF){
        if (min != 'a' && min != 'e' && min != 'i' && min != 'o' && min != 'u' && min != 'A' && min != 'E' && min != 'I' && min != 'O' && min != 'U')
            putc(min, fpout);
    }
    return 0;
}