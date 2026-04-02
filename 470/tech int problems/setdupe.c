//C ARRAYS DONT HAVE END OF ARRAY CHARACTERS EXCEPT FOR STRINGS

#include <stdio.h>

int main(){
int array[4]= {1, 2, 3, 4};
int dupefound=0;
for(int i = 0; array[i] != NULL; i++){
	printf("%d\n",array[i]);
}
for(int i = 0; array[i]!= NULL; i++){
	for(int j = i + 1; array[j]!= NULL; j++){
		if(array[i] == array[j]){
			printf("found dupe %d %d\n", array[i], array[j]);
			dupefound = 1;
			break;
		}
	}

}
if(!dupefound){
	printf("nodupes");
}
return 0;
}
