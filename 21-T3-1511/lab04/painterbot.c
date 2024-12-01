//Blair z5351042
#include<stdio.h>
int main(void){
    int scanned_in_value;
    int elements[36]={0};
    while (scanf("%d", &scanned_in_value)==1){
        elements[scanned_in_value]=1;
    }
    int i = 0;
    while (i<36){
        printf("%d ", elements[i]);
        i++;
    }
    printf("\n");
}
