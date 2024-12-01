//Blair z5351042
#include <stdio.h>
#include <stdlib.h>

int encrypt(int ch, int shift);

int main(int arg, char *argv[]){
    int num = atoi(argv[1]);
    int ch = getchar();
    while (ch != EOF){
        if (num >= 0){
            ch = encrypt(ch, num);
        }
        else{
            ch = encrypt(ch, (num % 26) + 26);
        }
        putchar(ch);
        ch = getchar();
    }
}

int encrypt(int ch, int shift){
    int first = 0;
    if (ch >= 'A' && ch <= 'Z'){
        first = 'A';
    }
    else if (ch >= 'a' && ch <= 'z'){
        first = 'a';
    }
    int letter = ch + shift;
    letter -= first;
    letter %= 26;
    letter += first;
    if (first != 0){
        return letter;
    }
    return ch;
}
