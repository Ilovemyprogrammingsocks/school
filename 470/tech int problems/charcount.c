#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	
	int alphabet[26] = {0};
	for(int j = 1; j < argc; j++){
		int entrylen = strlen(argv[j]);
		for(int i = 0; i < entrylen; i++){
			if(argv[j][i] == 'a'){
				alphabet[0]++;
			}else if(argv[j][i] == 'b'){
				alphabet[1]++;
			}else if(argv[j][i] == 'c'){
				alphabet[2]++;
			}else if(argv[j][i] == 'd'){
				alphabet[3]++;
			}else if(argv[j][i] == 'e'){
				alphabet[4]++;
			}else if(argv[j][i] == 'f'){
				alphabet[5]++;
			}else if(argv[j][i] == 'g'){
				alphabet[6]++;
			}else if(argv[j][i] == 'h'){
				alphabet[7]++;
			}else if(argv[j][i] == 'i'){
				alphabet[8]++;
			}else if(argv[j][i] == 'j'){
				alphabet[9]++;
			}else if(argv[j][i] == 'k'){
				alphabet[10]++;
			}else if(argv[j][i] == 'l'){
				alphabet[11]++;
			}else if(argv[j][i] == 'm'){
				alphabet[12]++;
			}else if(argv[j][i] == 'n'){
				alphabet[13]++;
			}else if(argv[j][i] == 'o'){
				alphabet[14]++;
			}else if(argv[j][i] == 'p'){
				alphabet[15]++;
			}else if(argv[j][i] == 'q'){
				alphabet[16]++;
			}else if(argv[j][i] == 'r'){
				alphabet[17]++;
			}else if(argv[j][i] == 's'){
				alphabet[18]++;
			}else if(argv[j][i] == 't'){
				alphabet[19]++;
			}else if(argv[j][i] == 'u'){
				alphabet[20]++;
			}else if(argv[j][i] == 'v'){
				alphabet[21]++;
			}else if(argv[j][i] == 'w'){
				alphabet[22]++;
			}else if(argv[j][i] == 'x'){
				alphabet[23]++;
			}else if(argv[j][i] == 'y'){
				alphabet[24]++;
			}else if(argv[j][i] == 'z'){
				alphabet[25]++;
			}
		}
	}
	printf("a: %d b: %d c: %d d: %d e: %d f: %d g: %d h: %d i: %d j: %d k: %d l: %d m: %d n: %d o: %d p: %d q: %d r: %d s: %d t: %d u: %d v: %d w: %d x: %d y: %d z: %d\n", alphabet[0], alphabet[1], alphabet[2], alphabet[3], alphabet[4], alphabet[5], alphabet[6], alphabet[7], alphabet[8], alphabet[9], alphabet[10], alphabet[11], alphabet[12], alphabet[13], alphabet[14], alphabet[15], alphabet[16], alphabet[17], alphabet[18], alphabet[19], alphabet[20], alphabet[21], alphabet[22], alphabet[23], alphabet[24], alphabet[25]);
	
}
