//Blair z5351042
#include <stdio.h>
int main(void){
    int i = 0;
    int code1 = 0;
    int code2 = 0;
    int code = getchar();
    while (code != EOF){
        if (i % 2 == 0){
            code1 = code;
        }
        else if (i % 2 != 0){
            code2 = code;
        }
        if (code1 != 0 && code2 != 0){
            if (code1 <= code2){
                printf("%c", code1);
            }
            else{
                printf("%c", code2);
            }
            code1 = 0;
            code2 = 0;
        }
        code = getchar();
        i++;
    }
    printf("\n");
}