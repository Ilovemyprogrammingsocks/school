#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

//format of zarchive [ c|x ] "archive-name"
int main(int argc, char* argv[]){

	//argument checking
	char* archivename[100];
	if(argc < 2){
		printf("Error: Not enough arguments");
		return 1;
	}else if(arg c > 3){
		printf("Error: Too many arguments");
		return 1; 
	}else if(argc == 3){
	//FIXME this might not be how pointers work
	archivename = argv[2];
	}else{
	printf("HELLO %s, WHAT ARCHIVE WOULD YOU LIKE TO CREATE OR UNARCHIVE TODAY", 
		getpwuid(getuid()).pw_name);

	//TODO scan for entered filename and set archivename to it
	}





/*
	//this will be part of archive appending loop
	int fileloc = open(*//*FIXME*//*, O_RDWR);
    	int filesizebyte = lseek(fileloc, 0 ,SEEK_END);
	//reset file pointer
	int error = lseek(fileloc, 0, SEEK_SET);
	//error check
	if(error == -1){
		printf("%d", error);
		return error;
	}
*/

}
