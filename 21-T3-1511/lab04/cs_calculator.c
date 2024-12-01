//Blair z5351042
#include<stdio.h>
int main(void){
    
    int ins;
    printf("Enter instruction: ");
    int dec=scanf("%d", &ins);
    while (dec==1){
        if (ins==1){
           int power;
           scanf("%d", &power);
           printf("%d\n", power*power);
        }
        else if (ins==2){
            int power, num;
            scanf("%d %d", &num, &power);
            int i = 1;
            int ans = num;
            while (i < power){
                ans = ans * num;
                i++;
            }
            printf("%d\n", ans);
        }
    printf("Enter instruction: ");
    dec=scanf("%d", &ins);
    }
    //printf("\n");
    return 0;
}
