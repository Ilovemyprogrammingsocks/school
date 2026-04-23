//Amber Dean

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[]){
	printf("%s %d\n",argv[1], getpid());
	if (argv[1][0] - '0' >= 5){
		return 0;
	}
	argv[1][0] = argv[1][0] + 1;
	printf("hi");
	execvp(argv[0], argv);

}
