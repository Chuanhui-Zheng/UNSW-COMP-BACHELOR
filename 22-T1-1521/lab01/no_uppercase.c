//Blair z5351042
#include <stdio.h>
#include <ctype.h>

int main(void){
	char a;
	while (scanf("%c", &a) == 1){
		if (a >= 'A' && a <= 'Z'){
			a += 'a' - 'A';
		}
		printf("%c", a);
	}
}
