//Blair z5351042
#include<stdio.h>
int main(void){
    int dec = 0;
    int num;
    int array[20000]={0};
    printf("Enter numbers forwards:\n");
    while (scanf("%d",&num)==1 && dec < 20000){
        array[dec] = num;
        dec+=1;
    }
    dec--;
    printf("Reversed:\n");
    while (dec >= 0){
        printf("%d\n", array[dec]);
        dec-=1;
    }
}
