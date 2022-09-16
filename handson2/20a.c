/*Name: ASWATHA NARAYANAN
 *Roll no: MT2022026
 *20. Write two programs so that both can communicate by FIFO -Use one way communication
 */

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

int main(int argc,char *argv[]){
	char* file="test_20";
	int fd=open(file,O_RDWR);
	//printf("%d",fd);
	mkfifo("test_20",0744);
	char buf[20];
	printf("Writting to the fifo file\nEnter the text to write\n");
	scanf("%s",buf);
	write(fd,buf,sizeof(buf));
	return 0;
}
