#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int subject = atoi(argv[1]);
	if(!(subject%3)){
		printf("fizz");
	}
	if(!(subject%5)){
		printf("buzz");
	}
	printf("\n");
	
	
}
