/*Name: ASWATHA NARAYANAN
 *Roll no: MT2022026
 *20. Write two programs so that both can communicate by FIFO -Use one way communication
 */

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	char* file=argv[1];
	int fd=open(file,O_RDWR);
	char buf[20];
	printf("Reading to the fifo file\n");
	read(fd,buf,20);
	printf("%s",buf);
	return 0;
}
