//Name: Aswatha Narayanan
//Roll no: MT2022026
	
//8. Write a separate program using signal system call to catch the following signals.
//c.SIGFPE


//SIGFPE - signal for airthmetic error

#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void fun(){
	printf("SIGFPE signal");
	exit(0);    ///to exit the function or it will be in infinte loop
}
int main(){
	int singal_status = signal(SIGFPE,(void *)fun);
	int s=10;
	int p=0;
	s=s/p;
	return 0;
}
