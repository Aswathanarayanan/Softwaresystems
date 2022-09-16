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
	
	//fcntl
	if(fork()){
		close(fd[0]);
		close(1);
		fcntl(fd[1],F_DUPFD,1);
		system(cmd1);
	}
	else{
		close(fd[1]);
		close(0);
		fcntl(fd[0],F_DUPFD,0);
		system(cmd2);
	}
	return 0;
}
