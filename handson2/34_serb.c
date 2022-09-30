/* Name: Aswatha Narayanan
 * Roll no: MT2022026
 *
 * 34. Write a program to create a concurrent server.
 * b. use pthread_create
 *
 */
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include <pthread.h>


void fun(int *csd){
	char buf[100];
	write(*csd,"I am Server",sizeof("I am Server"));
        read(*csd, &buf, 100);
        printf("Msg from client : %s",buf);
	close(*csd);
}

void main()
{
	int sd,csize,csd;
	char buf[100];
	pthread_t thread;
	sd = socket(AF_INET,SOCK_STREAM,0);
	printf("Socket:%d\n",sd);
	
	struct sockaddr_in serv,cli;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(8080);
	int b=bind(sd,(struct sockaddr *)&serv,sizeof(serv));
	printf("Bind:%d\n",b);
	
	int l=listen(sd,2);
	printf("Listen:%d\n",l);
	while(1){
		int cize = (int)sizeof(cli);
		csd = accept(sd, (struct sockaddr *)&cli,&csize);
		printf("\nAccept:%d\n",csd);
		perror("Accept error:");
		pthread_create(&thread,NULL,(void *)fun,&csd);
	}
	close(sd);
}

