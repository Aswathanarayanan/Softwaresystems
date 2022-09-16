/*Name: ASWATHA NARAYANAN
 * Roll no: MT2022026
 * 17. Write a program to execute ls -l | wc.
 *  a. use dup
 *  b. use dup2
 *  c. use fcntl
 */

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main(){
	int fd[2];
	pipe(fd);
	char *cmd1="ls -l";
	char *cmd2="wc";
	
	//dup
	printf("Using dup:\n");
	int f=fork();
	if(f!=0){
		close(fd[0]);
		close(1);
	  	dup(fd[1]);
	  	system(cmd1);
	}
	else{

		close(fd[1]);
		close(0);
		dup(fd[0]);
		system(cmd2);
	}
	return 0;
}
