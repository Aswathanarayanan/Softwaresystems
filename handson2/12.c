/* Name: Aswatha Narayanan
 * Roll no: MT2022026
 * 12. Write a program to create an orphan process. Use kill system call to send SIGKILL signal to 
 * the parent process from the child process.
 */

#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
int main(){
	if(fork()){
               printf("parent process %d\n",getpid()); 
	       sleep(10);
        }
        else
        {
               printf("child process %d\n",getpid());
               int ppid=getppid();
	       printf("parent id:%d\n",ppid);
	       //sleep(10);
	       kill(ppid,SIGKILL);
	       sleep(10);
        }
	return 0;
}
