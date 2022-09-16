/*Name: ASWATHA NARAYANAN
 *Roll no: MT2022026
 *21. Write two programs so that both can communicate by FIFO -Use two way communications.
 */

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	int fd=open("test_21a",O_RDWR);
	char buf[20];
	printf("Reading the fifo file\n");
	read(fd,buf,20);
	printf("%s\n",buf);
	
	mkfifo("test_21b",0744);
	int fd1=open("test_21b",O_RDWR);
	printf("Writting to file\nEnter the text\n");
	scanf("%s",buf);
	write(fd1,buf,sizeof(buf));
	return 0;
}
