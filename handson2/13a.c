/* Name: Aswatha Narayanan
 * Roll no: MT2022026
 * 13. Write two programs: first program is waiting to catch SIGSTOP signal, the second program 
 * will send the signal (using kill system call). Find out whether the first program is able to catch 
 * the signal or not.
 *
 */

#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
void fun(){
	printf("SIGSTOP Singal received");
	exit(0);
}
int main(){
	int signalstatus=signal(SIGSTOP,fun);
	printf("process id:%d\n",getpid());
	sleep(20);
	return 0;
}
