/*Name: ASWATHA NARAYANAN
 *Roll no: MT2022026
 *22. Write a program to wait for data to be written into FIFO within 10 seconds, use select 
 system call with FIFO
 */

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

int main(int argc,char *argv[]){
	int fd=open("test_22",O_RDWR);
	//printf("%d",fd);
	mkfifo("test_22",0744);
	
	char buf[20];
	printf("Writting to the fifo file\nEnter the text to write\n");
	scanf("%s",buf);
	write(fd,buf,sizeof(buf));
	return 0;
}
