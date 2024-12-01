//Blair z5351042
// Prints the first n digits of pi, where n is specified 
// by the user

#include <stdio.h>

#define MAX_DIGITS 10

int main(void) {
    int pi[MAX_DIGITS] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int n;
    printf("How many digits of pi would you like to print? ");
    //TODO: Insert your code here
    
    scanf("%d", &n);
    int i = 1;
    while (i <= n){
        if (i == 2){
            printf(".");
        }
        printf("%d",pi[i-1]);
    i+=1;
    }
    printf("\n");
    
    return 0;
}
