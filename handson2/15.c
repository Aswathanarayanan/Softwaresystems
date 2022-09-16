/*Name: ASWATHA NARAYANAN
 *Roll no: MT2022026
 15. Write a simple program to send some data from parent to the child process..
 */

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	int fd[2];
	pipe(fd);
	int f=fork();
	char buf[10];
	//child reads the pipe
	if(f==0){
		close(fd[1]);
		read(fd[0],buf,10);
		printf("Printing the data read from pipe by child\nmessage: ");
		printf("%s",buf);
	}
	//write by parent
	else{
		close(fd[0]);
		printf("Enter the message to write to pipe by parent\n");
		scanf("%s",buf);
		write(fd[1],buf,10);
	}
	return 0;
}

