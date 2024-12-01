//Blair z5351042
#include <stdio.h>
#include <string.h>

int main(void){
	char c[1024];
	while (fgets(c, 1024, stdin)){
		if (strlen(c) % 2 == 0){
			fputs(c, stdout);
		}
	}
}
