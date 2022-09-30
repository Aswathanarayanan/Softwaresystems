/* Name: Aswatha Narayanan
 * Roll no: MT2022026
 *
 * 34. Write a program to create a concurrent server.
 *
 */

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>

void main()
{
	int sd,stat;
	char buf[100];
	sd = socket(AF_INET,SOCK_STREAM,0);
	printf("Socket:%d\n",sd);
	
	struct sockaddr_in cli;
	cli.sin_family = AF_INET;
	cli.sin_addr.s_addr = htonl(INADDR_ANY);
	cli.sin_port = htons(8080);
	
	stat = connect(sd,(struct sockaddr *) &cli, sizeof(cli));
	printf("Connect:%d\n,stat");
	
	read(sd, &buf, 100);
	printf("Msg from Server : %s",buf);
	write(sd,"I am Client",sizeof("I am Client"));
	
	close(sd);
}

