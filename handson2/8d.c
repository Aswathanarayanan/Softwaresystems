//Name: Aswatha Narayanan
//Roll no: MT2022026
	
//8. Write a separate program using signal system call to catch the following signals.
//d.SIGALRM (use alarm system call)
//


#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void fun(){
	printf("SIGALRM signal");
	exit(0);    ///to exit the function or it will be in infinte loop
}
int main(){
	int singal_status = signal(SIGALRM,(void *)fun);
	alarm(2);	
	return 0;
}
