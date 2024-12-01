//Blair z5351042
#include<stdio.h>
int main(void)
{
    int p, q, c;
    scanf("%d %d", &p, &q);
    c = p * q;
    if (c < 0)
        printf("%d\n",c * -1);
    else if (c == 0)
        printf("zero\n");
    else
        printf("%d\n",c);
    return 0;
}
