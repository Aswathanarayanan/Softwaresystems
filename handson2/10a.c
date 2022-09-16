/*Name: Aswatha Narayanan
 * Roll no: MT2022026
 * 10. Write a separate program using sigaction system call to catch the following signals.
 *  a. SIGSEGV
 */
#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
void fun(){
	printf("Sigaction SIGSEGV handler");
	exit(0);
}
int main(){
	struct sigaction act;
	act.sa_handler= fun;
	act.sa_flags=0;
	int signalstatus=sigaction(SIGSEGV,&act,NULL);
	int s;
	printf("enter the num\n");
	scanf("%d",s);
	return 0;
}
