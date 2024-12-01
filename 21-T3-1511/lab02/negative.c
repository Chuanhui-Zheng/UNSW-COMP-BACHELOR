// Blair z5351042
#include<stdio.h>
int main(void){
    int a;
    scanf("%d",&a);
    if (a<0){
        printf("Don't be so negative!\n");
    }
    else if (a==0){
        printf("You have entered zero.\n");
    }
    else
    {
        printf("You have entered a positive number.\n");
    }
}
