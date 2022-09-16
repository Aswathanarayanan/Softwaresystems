/*Name:ASWATHA NARAYANAN
 * Rollno: MT2022026
 * 14. Write a simple program to create a pipe, write to the pipe, read from pipe and display on 
 * the monitor.
 * */
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	int fd[2];
	pipe(fd);
	char buf[10];
	char r[10];
	printf("enter the message to write to pipe\n");
	scanf("%s",buf);
	//close(fd[0]);
	write(fd[1],buf,10);
	read(fd[0],r,10);
	printf("the message read from pipe is \"%s\"",r);
	return 0;
}
