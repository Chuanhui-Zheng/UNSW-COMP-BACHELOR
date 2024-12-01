//Blair z5351042
#include <stdio.h>
#include <stdlib.h>

#define SERIES_MAX 30

int fibo(int n);

int main(void){
    int input;
    while (scanf("%d", &input) >= 0){
        if (input <= SERIES_MAX){
            int ans = fibo(input);
            printf("%d\n", ans);
        }
    }
    return 0;
}

int fibo(int n){
    if (n < 2){
        return n;
    }
    else{
        return fibo(n - 1) + fibo(n - 2);
    }
}
