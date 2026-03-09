#include <stdio.h>
#include <stdlib.h>

main(int argc, char * argv){
    int jobfile = fopen(argv[1], "r");
    int skillfile = fopen(argv[2], "r");
    char curlnjf[100];
    char curlnsf[100];

    //read one line of jobfile into currentlinejobfile
    //for each delimiter signified string chunk compare for 
    //>each delimiter signified string in currentlineskillfile
    //if match found, skip to next chunk in jobfile and 
}