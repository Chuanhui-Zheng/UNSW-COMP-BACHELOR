//Blair z5351042

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");
    unsigned long length;
    int min1, min2;
    for (length = 0;; length++){
        min1 = getc(fp1);
        min2 = getc(fp2);
        if (min1 != min2 || min1 == EOF)
            break;
    }
    if (min1 == min2)
        printf("Files are identical\n");
    else if (min1 == EOF)
        printf("EOF on %s\n", argv[1]);
    else if (min2 == EOF)
        printf("EOF on %s\n", argv[2]);
    else
        printf("Files differ at byte %lu\n", length);
    return 0;
}