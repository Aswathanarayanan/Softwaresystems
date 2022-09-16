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
	int fd=open("test_22",O_RDONLY);
	//printf("%d",fd);
	char buf[20];
	fd_set rfds;
        struct timeval t;
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        t.tv_sec = 10;
        t.tv_usec = 0;

	int  res=select(fd+1,&rfds,NULL,NULL,&t);
        if(res==-1)
        perror("select()");
        else if(res){
		printf("data available\n");
		 printf("reading the fifo file\n");
	         read(fd,buf,sizeof(buf));
	         printf("%s",buf);
	}
        else
		printf("data not available in 10sec");
	return 0;
}
