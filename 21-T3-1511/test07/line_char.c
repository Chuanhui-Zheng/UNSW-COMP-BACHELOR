//Blair z5351042
#include <stdio.h>
int main(void){
    int i = 0;
    int cha;
    int num;
    int word[256];
    cha = getchar();
    while (cha != '\n'){
        word[i] = cha;
        cha = getchar();
        i++;
    }
    scanf("%d", &num);
    printf("The character in position %d is '%c'\n",num,word[num]);
}