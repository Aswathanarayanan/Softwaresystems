/*Name: Aswatha Narayanan
 * Roll no: MT2022026
 * 11. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - 
 * use sigaction system call.
 */
#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
int main(){
	struct sigaction act;
	struct sigaction old_act;
	act.sa_handler= SIG_IGN;
	act.sa_flags=0;
	int signalstatus=sigaction(SIGINT,&act,&old_act);
	sleep(5);
	signalstatus=sigaction(SIGINT,&old_act,NULL);
	while(1){
		printf("hi\n");
	}
	return 0;
}
