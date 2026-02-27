#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]){

    //extensions to compare
    char extension[] = ".z827";
    char extension2[] = ".txt";
    //string lengths
    int strln = strlen(argv);
    int exln = strlen(extension);
    int ex2ln = strlen(extension2);
    //file flags
    int compress = 1;
    int validfile = 1;

    int fileloc = open(*argv);

    //compare end of given filename to expected extension for decompression and set flag accordingly
    for(int i = 0; i < strln && i < exln; i++){
        if (argv[i+strln-exln] != extension[i]){
            compress = 1;
            break;
        }
        compress = 0;
    }
    //check for hedge case where string is too small to contain extension
    if(strln < exln){
        compress = 1;
    }

    if(compress){
    //checks that given file is even a .txt
    for(int i = 0; i < strln && i < ex2ln; i++){
        if (argv[i+strln-ex2ln] != extension2[i]){
            validfile = 0;
            break;
        }
        validfile = 1;
    }
    }else{

}   



    return 0;
}