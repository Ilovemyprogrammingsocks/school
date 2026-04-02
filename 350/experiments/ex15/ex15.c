#include <sys/time.h>
#include <signal.h>
#include <stdio.h>
void timerSignal(int sig){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("Sec:%ld USec:%ld\n", tv.tv_sec, tv.tv_usec);
}

int main(){
signal(SIGALRM, timerSignal);
struct itimerval interval;
interval.it_interval.tv_usec = 1000;
interval.it_value.tv_usec = 1;
setitimer(ITIMER_REAL, &interval, NULL);
for(;1;){
}
}
