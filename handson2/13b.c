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
int main(int argc, char* argv[]){
	int pid=atoi(argv[1]);
	printf("%d",pid);
	kill(pid,SIGSTOP);
	//sleep(20);
	return 0;
}
