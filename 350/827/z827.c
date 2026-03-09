#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    if(argc > 2){
        fprintf(stderr,"Error: too many arguments\n");
        return 1;
    } else if(argc < 2){
        fprintf(stderr,"Error: too few arguments\n");
        return 1;
    }
    //extensions to compare
    char extension[] = ".z827";
    char extension2[] = ".txt";
    //string lengths
    int strln = strlen(argv[1]);
    int exln = strlen(extension);
    int ex2ln = strlen(extension2);
    //file flags
    int decompress = 0; //flag for if file ends with .z827
    int validtxt = 0;   //flag for if file ends with .txt

    int fileloc = open(argv[1], O_RDWR);
    //Throws error if file doesnt exist
    if(fileloc < 0){
        fprintf(stderr,"ERROR: Given file does not exist\n");
        return 1;
    }

    //compare end of given filename to expected extension for decompression and set flag accordingly
    for(int i = 0; i < strln && i < exln; i++){
        if ((char)argv[1][i+strln-exln] != extension[i]){
            decompress = 0;
            break;
        }
        decompress = 1;
    }
    //check for hedge case where string is too small to contain extension
    if(strln < exln){
        decompress = 0;
    }
    //checks that given file is a .txt and possibly throws error
    if(!decompress){
        for(int i = 0; i < strln && i < ex2ln; i++){
            if ((char) argv[1][i+strln-ex2ln] != extension2[i]){
                validtxt = 0;
                fprintf(stderr,"ERROR: Given file not correct format");
                return 1;
            }
        validtxt = 1;
        }
    }
    //check for hedge case where string is too small to contain extension
    if(strln < ex2ln){
    fprintf(stderr,"ERROR: Given file not correct format");
    return 1;
    }
    


    //COMPRESSION ALGO
    unsigned int buf1 = 0;
    unsigned int buf2 = 0;

    unsigned int filesizebyte = lseek(fileloc, 0 ,SEEK_END);
    int offset = 7;
    if(!decompress){
        int newfileloc = creat(strcat(argv[1], ".z827"), O_WRONLY);
        write(newfileloc, &filesizebyte, 1);
        read(fileloc, &buf1, 1);
        for(int i = 0; i < filesizebyte; i++){
            read(fileloc, &buf2, 1);
            buf2 = buf2 << offset;
            buf1 = buf1 | buf2;
            write(newfileloc, &buf1, 1);
            buf1 = buf1 >> 8;
            offset += -1;
            if (offset==0){
                offset = 7;
                read(fileloc, &buf1, 1);
                i++;
            }
        }
    }
    //TESTING
    printf("decompress: %d, validtxt: %d, fileloc: %d, filesizebyte: %d\n", decompress, validtxt, fileloc, filesizebyte);

    return 0;
}
