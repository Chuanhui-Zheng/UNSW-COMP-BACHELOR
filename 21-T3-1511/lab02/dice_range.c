//Blair z5351042
#include<stdio.h>
int main(void){
    printf("Enter the number of sides on your dice: ");
    float a;
    scanf("%f",&a);
    printf("Enter the number of dice being rolled: ");
    float b;
    scanf("%f",&b);
    if (a<=0){printf("These dice will not produce a range.\n");
    return 1;
    }else if (b<0){printf("These dice will not produce a range.\n");
    return 1;}
    else{printf("Your dice range is %.0f to %.0f. \n",b,a*b);
        printf("The average value is %.6f\n",(b+a*b)/2);
    }
}
