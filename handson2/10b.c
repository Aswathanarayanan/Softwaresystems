/*Name: Aswatha Narayanan
 * Roll no: MT2022026
 * 10. Write a separate program using sigaction system call to catch the following signals.
 * b. SIGINT
 *
 */
#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
void fun(){
	printf("Sigaction SIGINT handler");
	exit(0);
}
int main(){
	struct sigaction act;
	act.sa_handler= fun;
	act.sa_flags=0;
	int signalstatus=sigaction(SIGINT,&act,NULL);
	while(1){
		printf("hi\n");
	}
	return 0;
}
