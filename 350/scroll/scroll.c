#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/time.h>


//buffer
char* buf;

//window size variables
int win_r;
int win_c;

//bookmarks
int bufbeg = 0;
int bufend = 0;

//tooltip
char tooltip[] = "enter:pause-q:quit-f/s:speed-space:skip";

//scroll speed and control function
int speed = 0;
int spdctl(int control){
	struct timeval t;
	t.tv_sec = 0;
	if(control == 0){
		speed = 0;
		alarm(0);
	} else if(control > 0){
		if(speed <= 0){
			speed = 3000000;
			t.tv_usec = speed;
			if(speed >= 1000000){
				t.tv_sec = speed / 1000000;
				t.tv_usec = speed % 1000000;
			}
			struct itimerval tt;
			tt.it_interval = t;
			tt.it_value = t;
			setitimer(ITIMER_REAL, &tt, NULL);
		}else{
			speed = speed * 1.2;
			t.tv_usec = speed;
			if(speed >= 1000000){
				t.tv_sec = speed / 1000000;
				t.tv_usec = speed % 1000000;
			}
			struct itimerval tt;
			tt.it_interval = t;
			tt.it_value = t;
			setitimer(ITIMER_REAL, &tt, NULL); 
		}
	}else{
		speed = speed * 0.8;
		t.tv_usec = speed;
		if(speed >= 1000000){
			t.tv_sec = speed / 1000000;
			t.tv_usec = speed % 1000000;
		}
		struct itimerval tt;
		tt.it_interval = t;
		tt.it_value = t;
		setitimer(ITIMER_REAL, &tt, NULL);;
	}
	return speed;
}

//closes buf and turns on echo and canon recording
void cleanexit(){
	free(buf);
	struct termios tsettings;
	tcgetattr(0, &tsettings);
	tsettings.c_lflag |= ECHO;
	tsettings.c_lflag |= ICANON;
	tcsetattr(0, 0, &tsettings);
	exit(0);
}

//reprints buf and increments the bookmarks
void next(){
	printf("\n");
	for(int i = bufbeg;i <= bufend; i+= win_c){
		for(int j = i; i < win_c; j++){
			printf("%c", buf[j]);
		}
		printf("\n");
	}
	printf("%s", tooltip);
	fflush(stdout);
	return;
}


//error thrower
void error(char *ermsg){
	perror(ermsg);
	cleanexit();
}

int main(int argc, char *argv[]){
	//argument checking
	struct stat filestat;
	if ((argc != 2) || (stat(argv[1], &filestat) < 0) || 
			(strcmp(&argv[1][strlen(argv[1])-4], ".txt") != 0)){
		error("Argument error\n");
	}
	//malloc and read into buffer
	buf = malloc(filestat.st_size);
	if(buf == NULL){error("malloc failure\n");}
	FILE* file = fopen(argv[1], "r");
	fread(buf, sizeof(char), filestat.st_size, file);

	//need TWO handlers, one for SIGINT, and one for SIGALRM
	signal(SIGALRM, next);
	signal(SIGINT, cleanexit);
	
	struct winsize sbuf;
	//get terminal size
	if(ioctl(1, TIOCGWINSZ, &sbuf) != -1){
		win_r = sbuf.ws_row;
		win_c = sbuf.ws_col;
	}else{error("ioctl failure\n");}
	if(strlen(tooltip) > win_c){error("window too small\n");}
	
	bufend = (win_r-1 * win_c)-1;

	//turn off echoing and canonical terminal
	struct termios tsettings;
	tcgetattr(0, &tsettings);
	tsettings.c_lflag &= ~ECHO;
	tsettings.c_lflag &= ~ICANON;
	tcsetattr(0, 0, &tsettings);
	
	//start the timer
	spdctl(1);
	char key;
	while(scanf("%c", &key)){
		if(key == 'q'){
			cleanexit();
		}
		else if(key == '\n'){
			spdctl(0);
		}
		else if(key == 'f'){
			spdctl(-1);
		}
		else if(key == 's'){
			spdctl(1);
		}
		else if(key == ' '){
			for(int i=0; i < win_r-1;i++){
				next();
			}
			spdctl(0);
		}
	}
	cleanexit();
}
