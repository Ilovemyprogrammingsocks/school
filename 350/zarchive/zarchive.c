#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

struct header {
	unsigned int uid; // uid of the archive owner (fron getuid())
	char owner[64]; // username of the archive owner
	unsigned int n_files; // the number of files in the archive
};

struct file {
	size_t size; // size of file in bytes
	time_t timestamp; // unix modification time of the file
	char file_name[256]; // name of file, zero padded
  	unsigned int options; // bit 0 is set if z827 compressed, 0 otherwise
					// other bits are unused.
};

//format of >zarchive [c|x] "archive-name" --extractdest
int main(int argc, char* argv[]){

	//argument checking
	char* archivename[100];
	if(argc < 2){
		printf("Error: Not enough arguments");
		return 1;
	}else if(argc > 3 && (argv[1] != "c")){
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
