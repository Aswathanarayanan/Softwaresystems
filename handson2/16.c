/*Name: ASWATHA NARAYANAN
 * Roll no: MT2022026
 * 16. Write a program to send and receive data from parent to child vice versa. Use two way 
 * communication.
 */

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
int main(){
	int fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);
	char buf1[20];
	char buf2[20];
	int t=5;
	int f=fork();
	if(f==0){
		sleep(6);
		close(fd2[1]);
		printf("Pipe read by child\n");
		read(fd2[0],buf1,20);
		printf("Message: %s\n",buf1);


		printf("Child pipe write\n");
		close(fd1[0]);
		//close(fd2[1]);
		printf("Enter the message\n");
		scanf("%s",buf1);
		write(fd1[1],buf1,20);

	}
	else{
		printf("Parent writing to the pipe\n");
		close(fd2[0]);
		//close(fd1[1]);
		printf("Enter the message\n");
		scanf("%s",buf2);
		write(fd2[1],buf2,20);

		sleep(2);
		close(fd1[1]);
		printf("Pipe read by parent\n");
		read(fd1[0],buf2,20);
		printf("message: %s\n",buf2);
	}
	return 0;
}

