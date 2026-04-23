#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>
////MAKE file and man page

//format of >zarchive [c|x] "archive-name" --extractdest
int main(int argc, char* argv[]){

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


	
	//argument checking
	if(argc == 1){printf("NO ARGUMENTS FOUND\n");return 1;}
	if(strcmp(argv[1], "x") == 0){ //EXTRACT MODE
		//make directory
		if(argc == 4){
			struct stat dirstat;
			if(stat(argv[3], &dirstat) != -1){
				printf("Error: Existing directory shares name with parameter\n");
				return 1;
			}

			mkdir(argv[3], 0777);
			
		}

		if (argc == 3 || argc == 4){
			//extract to current directory
			struct stat archstat;
			if(stat(argv[2], &archstat) < 0){
				printf("Error: Archive does not exist\n");
				return 1;
			}
			FILE * archive = fopen(argv[2], "r");
			//change directory
			if(argc == 4){chdir(argv[3]);}
			unsigned int buf;
			struct header arch_head;
			arch_head.n_files = 0;
			arch_head.uid = 1;
			arch_head.owner[0] = 'h';
			fread(&arch_head, sizeof(arch_head), 1, archive);
			for(unsigned int i = 0; i < arch_head.n_files; i++){
				struct file file_head;
				fread(&file_head, sizeof(file_head), 1, archive);
				FILE * cur_file = fopen(file_head.file_name, "w+");
				for(unsigned int z = 0; z < file_head.size; z++){
					fread(&buf, 1, 1, archive);
					fwrite(&buf, 1, 1, cur_file);
				}
				struct utimbuf temp;
				temp.modtime = file_head.timestamp;
				temp.actime = file_head.timestamp;
				fclose(cur_file);
				utime(file_head.file_name, &temp);
				
			}
			fclose(archive);	
		}else{printf("Error: unexpected argument count\n");return 1;}

	}else if(strcmp(argv[1], "c") == 0){  //CREATE MODE
		char archivename[100];
					//making the header
		struct header arch_head;
		arch_head.uid = getuid();
		arch_head.n_files = 0;
		strcpy(arch_head.owner, (*getpwuid(getuid())).pw_name);

		if(argc == 3){
			strcpy(archivename, argv[2]);
		}
		if(argc < 2){
			printf("Error: Not enough arguments\n");
			return 1;
		}else if(argc > 3){
			printf("Error: Too many arguments\n");
			return 1; 
		}else if (argc == 2){
			printf("HELLO %s, WHAT ARCHIVE WOULD YOU LIKE TO CREATE TODAY\n",
					(*getpwuid(getuid())).pw_name);
			scanf("%s", archivename);
		}
		//append the extension
		strcat(archivename, ".z");
		
		//ARCHIVE BULK
		printf("HERE IS A LIST OF AVAILIBLE FILES, PLEASE ENTER A LIST OF YOUR OWN INCLUDING THE FILES YOU WISH TO ARCHIVE, OR ENTER \"*\" TO SELECT ALL FILES\n<<enter 'q' when done>>\n");
		struct dirent **dirlist;
		int dirlen = scandir(".", &dirlist, NULL, alphasort);
		int dirlist_flags[dirlen];
		//array initializer
		for(int j = 0; j < dirlen; j++){dirlist_flags[j] = 0;}

		//prints out directory
		for(int i = dirlen -1 ;i; i--){
			if(strncmp(dirlist[i]->d_name, ".", 1)){
				struct stat printstat;
				stat(dirlist[i]->d_name, &printstat);
				time_t sec = printstat.st_mtim.tv_sec;
				struct tm* temptm = localtime(&sec);
				const char* format = "%Y-%m-%d %H:%M:%S";
				char buf[64];
				strftime(buf, sizeof(buf), format, temptm);
				if((printstat.st_mode & S_IFMT) != S_IFDIR){
					printf("%s \t %ld bytes \t %s\n", dirlist[i]->d_name, printstat.st_size, buf);
				}
			}
		}

		//Loop that scans until "q" entered, and searches for a match in the dirlist
		while(1){
			char cur_entry[100];
			scanf("%s", cur_entry);
			if(strcmp(cur_entry, "q") == 0){break;}
			else if(strcmp(cur_entry, "*") == 0){
				for(int j = 0; j < dirlen; j++){
					//sets all flags for wildcard
						
						dirlist_flags[j] = 1;
					
				}
				break;
			}
			else{
				for(int j = 0; j < dirlen; j++){
					//Found a match and sets corresponding flag
					if(strcmp(cur_entry, dirlist[j]->d_name) == 0){
						dirlist_flags[j] = 1;
					}
				}
			}
		}
		for(int j = 0;j < dirlen;j++){
			if(dirlist_flags[j]){
				arch_head.n_files+=1;
			}
		}

		//MAKE NEW FILE AND WRITE TO IT
		int dupe_name = 0;  //checking for invalid archive name			
		for(int j = 0; j < dirlen; j++){
			if(strcmp(archivename, dirlist[j]->d_name) == 0){
				dupe_name = 1;
				break;
			}
		}
		if(dupe_name){printf("Error: Archive already exists\n"); return 1;}
		FILE * archiveloc = fopen(archivename, "w+");
		fwrite(&arch_head, sizeof(arch_head), 1, archiveloc);
		for(int j = 0; j < dirlen; j++){
			struct stat printstat;
			stat(dirlist[j]->d_name, &printstat);
			if(((printstat.st_mode & S_IFMT) != S_IFDIR) && dirlist_flags[j]){
				FILE * fileloc = fopen(dirlist[j]->d_name, "r");
				unsigned int buf[64];

				//making header
				struct file header;
				struct stat filestat;
				for(int k = 0 ;k < 256; k++){header.file_name[k] = '0';}
				strcpy(header.file_name, dirlist[j]->d_name);
				stat(dirlist[j]->d_name, &filestat);
				header.size = filestat.st_size;
				header.timestamp = filestat.st_mtim.tv_sec;
				header.options= 0;
				
				fwrite(&header, sizeof(header), 1, archiveloc);
				int z;
				while(z = fread(&buf, 1, 64, fileloc)){
					fwrite(&buf, 1, z, archiveloc);
				}
				fwrite(&buf, 1, z, archiveloc);
				fclose(fileloc);

			}	
		}
		fclose(archiveloc);
		for(int i= dirlen -1 ;i; i--){
			if(dirlist_flags[i]){
				struct stat printstat;
				stat(dirlist[i]->d_name, &printstat);
				time_t sec = printstat.st_mtim.tv_sec;
				struct tm* temptm = localtime(&sec);
				const char* format = "%Y-%m-%d %H:%M:%S";
				char buf[64];
				strftime(buf, sizeof(buf), format, temptm);
				if((printstat.st_mode & S_IFMT) != S_IFDIR){
					printf("%s \t %ld bytes \t %s\n", dirlist[i]->d_name, printstat.st_size, buf);
				}
			}
		}

	}else{printf("Argument error: invalid arguments\n"); return 1;}


}
