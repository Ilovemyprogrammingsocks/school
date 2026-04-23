//Amber Dean

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int child1 = fork();
	int child2 = fork();
	int child5 = 0;
	if(child1 && child2){
		child5 = fork();
	}
	if(child1 && child2 && child5){
		printf("1 %d\n", getpid());
	}else if(child1 && child2){
		printf("5 %d\n", getpid());
	}else if(child1){
		printf("3 %d\n", getpid());
	}else if(child2){
		printf("2 %d\n", getpid());
	}else{
		printf("4 %d\n", getpid());
	}
	

}
