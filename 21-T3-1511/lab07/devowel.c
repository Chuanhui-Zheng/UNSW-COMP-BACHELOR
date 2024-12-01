//Blair z5351042
#include <stdio.h>

int is_vowel(int character);

int main(void){
    int c;
    c = getchar();
    while (c != EOF){
        if (is_vowel(c) == 0){
            putchar(c);
        }
        c = getchar();
    }
    return 0;
}

int is_vowel(int character){
    if (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u'){
        return 1;
    }
    else{
        return 0;
    }
}
