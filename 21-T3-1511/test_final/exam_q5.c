#include <stdio.h>
#include <string.h>

#define SIZE 1024
                         
int main(int argc , char *argv[]) {
    char chara[SIZE];
    scanf("%s", chara);
    for (int a = 1; a < argc; a++) {
        for (int b = 0; b < strlen(argv[a]) && b < strlen(chara); b++) {
            if (chara[b] == argv[a][b]) {
                printf("%d %s\n", b, argv[a]);
                b = strlen(argv[a]);
                break;
            }
        }
    }
    return 0;
}

