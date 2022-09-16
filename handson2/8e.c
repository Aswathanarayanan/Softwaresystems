//Name: Aswatha Narayanan
//Roll no: MT2022026
	
//8. Write a separate program using signal system call to catch the following signals.
//SIGALRM (use setitimer system call)


#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
void fun(){
	printf("SIGALRM signal");
	exit(0);    ///to exit the function or it will be in infinte loop
}
int main(){
	int singal_status = signal(SIGALRM,(void *)fun);
	struct itimerval timer;
	timer.it_value.tv_sec = 1;
    	timer.it_value.tv_usec = 0;
        timer.it_interval.tv_sec = 0;
    	timer.it_interval.tv_usec = 0;
        int timer_status = setitimer(ITIMER_REAL, &timer, 0);
	return 0;
}
