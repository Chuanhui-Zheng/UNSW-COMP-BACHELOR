//Blair z5351042
#include <stdio.h>
#include <string.h>

int main(void){
	char a;
	while (scanf("%c", &a) == 1){
		if (a != '\n'){
			if (a != 'a' && a != 'e' 
			&& a != 'i' && a != 'o' 
			&& a != 'u' && a != 'A' 
			&& a != 'E' && a != 'I' 
			&& a != 'O' && a != 'U'){
				printf("%c", a);
			}
		}
		else{
			printf("\n");
		}
	}
}
