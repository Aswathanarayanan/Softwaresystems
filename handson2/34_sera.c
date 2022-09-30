/* Name: Aswatha Narayanan
 * Roll no: MT2022026
 *
 * 34. Write a program to create a concurrent server.
 * a. use fork
 */
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>

void main()
{
	int sd,csize,csd;
	char buf[100];
	sd = socket(AF_INET,SOCK_STREAM,0);
	printf("Socket:%d\n",sd);
	
	struct sockaddr_in serv,cli;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(8080);
	int b=bind(sd,(struct sockaddr *)&serv,sizeof(serv));
	printf("Bind:%d\n",b);
	
	int l=listen(sd,1);
	printf("Listen:%d\n",l);
	while(1){
		int cize = (int)sizeof(cli);
		csd = accept(sd, (struct sockaddr *)&cli,&csize);
		printf("\nAccept:%d\n",csd);
		if(!fork()){
			write(csd,"I am Server",sizeof("I am Server"));
			read(csd, &buf, 100);
		        printf("Msg from client : %s",buf);
		}
		else{
			close(csd);
		}
	
	}
	close(sd);
}

