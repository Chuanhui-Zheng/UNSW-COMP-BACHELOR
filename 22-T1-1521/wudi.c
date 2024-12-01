#include <stdio.h>
#include <math.h>

int main(){
    float a[170];
    a[0]=0.25;
    a[1]=2.25;
    for(int i=2;i<170;i++){
        a[i]=pow(4+a[i-1],0.5)/(3*a[i-2]);
    }
    printf("%f",a[169]);
    return 0;
}