//Blair z5351042
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fpin = fopen(argv[1], "r");
    int min;
    int num = 0;
    while ((min = getc(fpin)) != EOF)
    {
        if (min == 'a' || min == 'e' || min == 'i' || min == 'o' || min == 'u' || min == 'A' || min == 'E' || min == 'I' || min == 'O' || min == 'U')
            num++;
    }
    printf("%d\n", num);
    return 0;
}