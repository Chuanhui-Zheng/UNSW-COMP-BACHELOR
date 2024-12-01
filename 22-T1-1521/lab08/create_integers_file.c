#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]){
    char target[100];
    strcpy(target, argv[1]);
    int argv2 = atoi(argv[2]);
    int argv3 = atoi(argv[3]);
    FILE *integers_file = fopen(target, "w");
    int i = 0;
    int a = argv3 - argv2 + 1;
    while (i < a){
        fprintf(integers_file, "%d\n", argv2);
        argv2++;
        i++;
    }
}