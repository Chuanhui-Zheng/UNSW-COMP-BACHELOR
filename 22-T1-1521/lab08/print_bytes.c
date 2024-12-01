#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    FILE *f = fopen(argv[1], "r");
    int ca;
    long i = 0;
    while ((ca = fgetc(f)) != EOF){
        printf("byte %4ld: %3d 0x%02x", i, ca, ca);
        if (isprint(ca) == 0){
            printf("\n");
        }
        else{
            printf(" '%c'\n", ca);
        }
        i++;
    }

    fclose(f);
    return 0;
}

