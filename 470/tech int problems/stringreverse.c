#include <stdio.h>

void reverse(char string[]){
	int length = 0;
	for(; string[length] != NULL; length++){}
	printf("length: %d \n", length);
	char swaptemp;
	for(int i=1; i<=(length/2); i++){
		swaptemp = string[length-i];
		string[length-i] = string[i-1];
		string[i-1] = swaptemp;
	}
	
}

int main(int argc, char **argv){
	if(argc != 2){
		printf("uhoh \n");
	}
	
	reverse(argv[1]);
	printf("%s \n", argv[1]);

}
