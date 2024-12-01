//Blair z5351042
#include<stdio.h>
int main(void){
    char a;
    int b;
    printf("Uppercase: ");
    scanf("%c",&a);
    if (a!='y'&&a!='n'){
        printf("You need to enter 'y' or 'n'\n");
        printf("Exiting the program with error code 1\n");
        return 1;
    }
    
    printf("Index: ");
    scanf("%d",&b);
    
    if (b>26||b<=0){
        printf("You need to enter a number between 1 and 26 inclusive\n");
        printf("Exiting the program with error code 2\n");
        return 2;
    }
    
    if (a=='y'){
        printf("The letter is %c\n",'A'+b-1);
    }
    else if(a=='n'){
        printf("The letter is %c\n",'a'+b-1);
    }
}
