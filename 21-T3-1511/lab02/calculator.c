//Blair z5351042
#include<stdio.h>
int main(void){
    int a,b,c;
    printf("Enter instruction: ");
    scanf("%d %d %d",&a,&b,&c);
    if(a==1){
        printf("%d\n",b+c);
    }
    else if(a==2){
        printf("%d\n",b-c);
    }
}
