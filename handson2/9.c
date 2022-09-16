/*Name: Aswatha Naraynan
 * Roll no: MT2022026
 * 9. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT 
 * signal - Use signal system call.
 */

#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
int main(){
	int signal_id=signal(SIGINT,SIG_IGN);
	while(1){
		printf("hi");
	}
	return 0;
}
