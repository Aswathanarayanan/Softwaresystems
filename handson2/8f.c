//Name: Aswatha Narayanan
//Roll no: MT2022026
	
//8. Write a separate program using signal system call to catch the following signals.
//SIGPROF (use setitimer system call)


#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
void fun(){
	printf("SIGVTALRM signal");
	exit(0);    ///to exit the function or it will be in infinte loop
}
int main(){
	int signal_status = signal(SIGVTALRM,(void *)fun);
	if(signal_status==-1)
		perror("");
	struct itimerval timer;
	timer.it_value.tv_sec = 1;
    	timer.it_value.tv_usec = 0;
        timer.it_interval.tv_sec = 0;
    	timer.it_interval.tv_usec = 1;
        int timer_status = setitimer(ITIMER_VIRTUAL, &timer, 0);
	if(timer_status==-1)
		perror("");
	//int s=10,n=0;
	//s=s/n;
	while(1);
	return 0;
}
