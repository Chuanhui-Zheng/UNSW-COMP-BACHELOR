#include <stdio.h>
#include <stdlib.h>

#define LENGTH 1000
int main(void) {
    int ini = 0;
    int num = 1;
    int array[LENGTH];
    while (num != 0) {
        scanf("%d",&num);
        array[ini] = num;
        ini++;
    }
    int check = ini;
    ini = 0;
    printf("First Half:");
    while (ini < check/2) {
        printf(" %d", array[ini]);
        ini++;
    }
    printf("\n");
}
