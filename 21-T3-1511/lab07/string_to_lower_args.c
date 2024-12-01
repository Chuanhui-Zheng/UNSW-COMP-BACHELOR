//Blair z5351042
#include <stdio.h>

int main(int argc, char *argv[]){
    int i = 1;
    int j = 0;
    int k = 0;
    char str[1024];
    while (i < argc){
        while (argv[i][j] != '\0'){
            str[k] = argv[i][j];
            k++;
            j++;
        }
        i++;
        j = 0;
        str[k] = ' ';
        k++;
    }
    i = 0;
    while (i < k){
        if (str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + 'a' - 'A';
            putchar(str[i]);
        }
        else{
            putchar(str[i]);
        }
        i++;
    }
    printf("\n");
}
