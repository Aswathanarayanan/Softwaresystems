/*Name: ASWATHA NARAYANAN
 * Roll no: MT2022026
 * 18. Write a program to find out total number of directories on the pwd.
 *  execute ls -l | grep ^d | wc ? Use only dup2
 */

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main(){
	int fd[2];
	pipe(fd);
	char *cmd1="ls -l";
	char *cmd2="grep ^d";
	char *cmd3="wc";
	
	//dup2
	printf("Using Dup2:\n");
	if(fork()){
		close(fd[0]);
		dup2(fd[1],1);
		system(cmd1);
		//dup2(fd[0],0);
		//close(fd[1]);
	        //system(cmd2);
	}
	else{
		int fd1[2];
                pipe(fd1);
		close(fd[1]);
                dup2(fd[0],0);
		if(fork()){
			close(fd1[0]);
			dup2(fd1[1],1);
			system(cmd2);
		}
		else{
		       	close(fd1[1]);
			dup2(fd1[0],0);
		        system(cmd3);
		}
	}
	return 0;
}
