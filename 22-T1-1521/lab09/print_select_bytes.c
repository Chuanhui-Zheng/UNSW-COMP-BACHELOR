//Blair z5351042
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    FILE *fp = fopen(argv[1], "r");
    int i = 2;
    while (i < argc){
        fseek(fp, atoi(argv[i]), SEEK_SET);
        int charac = fgetc(fp);
        printf("%d - 0x%02X - '%c'\n", charac, charac, charac);
        i++;
    }
    fclose(fp);
    return 0;
}