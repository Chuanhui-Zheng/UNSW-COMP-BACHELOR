#include <stdio.h>

int func1(int a,int b);
int func2(int a,int b);

int main(int argc, char *argv[]) {
    fgets(line1, 16,stdin);
    fgets(line2, 16,stdin);
    printf("%d\n", func1(0,0));
    return 0;
}

int func1(int a,int b){
    if (line2[b] == '\n' || line1[a] == '\n') {
        return 0;
    }
    if (line1[a] == line2[b]) {
        return 1+ func1(a + 1, b + 1);
    }
    else{
        return func2(func1(a, b+1), func1(a+1, b));
    }
}

int func2(int a, int b){
    if (a < b){
        return b;
    }
    else{
        return a;
    }
}