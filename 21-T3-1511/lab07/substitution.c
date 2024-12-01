//Blair z5351042
#include <stdio.h>

int main(int argc, char *argv[]){
    int word;
    int ori[26];
    int ecp[26];
    int i = 0;
    while (i < 26){
        ori[i] = 'a' + i;
        ecp[i] = argv[1][i];
        i++;
    }
    word = getchar();
    while (word != EOF){
        if (word >= 'A' && word <= 'Z'){
            i = 0;
            while (i < 26){
                if (ori[i] + 'A' - 'a' == word){
                    putchar(ecp[i] + 'A' - 'a');
                    break;
                }
                i++;
            }
        }
        else if (word >= 'a' && word <= 'z'){
            i = 0;
            while (i < 26){
                if (ori[i] == word){
                    putchar(ecp[i]);
                    break;
                }
                i++;
            }
        }
        else{
            putchar(word);
        }
        word = getchar();
    }
}
