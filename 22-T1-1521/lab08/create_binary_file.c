#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *f = fopen(argv[1], "wb+");
    int i = 2;
    while (i < argc){
        int c = atoi(argv[i]);
        if (c < 0 || c > 255){
            perror(argv[i]);
            return 1;
        }
        fputc(c, f);
        i++;
    }

    fclose(f);
    
    return 0;
}