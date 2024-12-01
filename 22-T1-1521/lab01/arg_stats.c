//Blair z5351042
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int i = 1;
	int min = 999999;
	int max = -999999;
	int sum = 0;
	int prod = 1;
	int mean;
	while (i < argc){
		int a = atoi(argv[i]);
		sum += a;
		prod *= a;
		if (a > max){
			max = a;
		}
		if (a < min){
			min = a;
		}
		i++;
	}
	if (argc > 1){
		if (sum != 0){
			mean = sum / (argc - 1);
		}
		else{
			mean = 0;
		}
		printf("MIN:  %d\nMAX:  %d\nSUM:  %d\nPROD: %d\nMEAN: %d\n", min, max, sum, prod, mean);
	}

	return 0;
}
