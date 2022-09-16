/*Name: ASWATHA NARAYANAN
 *Roll no: MT2022026
 *21. Write two programs so that both can communicate by FIFO -Use two way communications.
 */

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

int main(int argc,char *argv[]){
	int fd=open("test_21a",O_RDWR);
	//printf("%d",fd);
	mkfifo("test_21a",0744);
	char buf[20];
	printf("Writting to the fifo file\nEnter the text to write\n");
	scanf("%s",buf);
	write(fd,buf,sizeof(buf));

	int fd1=open("test_21b",O_RDWR);
	printf("Reading the fifo file\n");
	read(fd1,buf,sizeof(buf));
	printf("%s",buf);
	return 0;
}
