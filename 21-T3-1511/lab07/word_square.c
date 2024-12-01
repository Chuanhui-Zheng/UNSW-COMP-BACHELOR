//Blair z5351042
#include <stdio.h>

int main(void){
    int i = 0;
    int word;
    int word_str[2024] = {0};
    printf("Input word: ");
    word = getchar();
    while (word != '\n'){
        word_str[i] = word;
        i++;
        word = getchar();
    }
    printf("\n");
    printf("Word square is:\n");
    for (int a = 0; a < i; a++){
        for (int b = 0; b < i; b++){
            putchar(word_str[b]);
        }
        printf("\n");
    }
}
