//Blair z5351042
#include<stdio.h>
int main(void){
    int a;
    printf("Enter number: ");
    scanf("%d", &a);
    if (a > 0){
        int count1 = 0;
        while (count1 <= a){
            printf("%d\n", count1);
            count1 ++;
            }
    }
    else{
        int count2 = 0;
        while (count2 >= a){
            printf("%d\n", count2);
            count2 -=1;
            }
    }
}
