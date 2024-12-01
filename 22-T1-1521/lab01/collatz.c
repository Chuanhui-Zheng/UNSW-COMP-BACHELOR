//Blair z5351042
#include <stdio.h>
#include <stdlib.h>

int collatz(int n);

int main(int argc, char **argv){
	if (argc > 1){
		return collatz(atoi(argv[1]));
	}
	else{
		printf("Usage: ./collatz NUMBER\n");
	}
	return EXIT_FAILURE;
}

int collatz(int n){
	printf("%d\n", n);
	if (n == 1){
		return EXIT_SUCCESS;
	}
	else if (n % 2 == 0){
		n = n / 2;
	}
	else{
		n = 3 * n + 1;
	}
	return collatz(n);
}