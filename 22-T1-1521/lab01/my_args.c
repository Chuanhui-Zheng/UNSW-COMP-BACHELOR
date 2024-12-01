//Blair z5351042
#include <stdio.h>

int main(int argc, char **argv){
	int i = 1;
	printf("Program name: %s\n", argv[0]);
	if (argc > 1){
		printf("There are %d arguments:\n", argc - 1);
	}
	else{
		printf("There are no other arguments\n");
	}
	while (i < argc){
		printf("	Argument %d is \"%s\"\n", i, argv[i]);
		i++;
	}
	return 0;
}
