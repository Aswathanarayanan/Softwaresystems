/*Name: ASWATHA NARAYANAN
 * Roll no: MT2022026
 * 17. Write a program to execute ls -l | wc.
 *  b. use dup2
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
	
	//dup2i
	printf("Using Dup2:\n");
	if(fork()){
		close(fd[0]);
		dup2(fd[1],1);
		system(cmd1);
	}
	else{
		close(fd[1]);
		dup2(fd[0],0);
		system(cmd2);
	}
	//fcntl
	
	return 0;
}
