#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include <string.h>

#include "./admin.h"
#include "./customer.h"
#include "./customer_struct.h"
#include "./account_struct.h"
#include "./admin_cred.h"

void connectionhandler(int socketfd){
	char readbuffer[1000],writebuffer[1000];
	int r_bytes,w_bytes;
	do{

		bzero(readbuffer, sizeof(readbuffer));
        bzero(writebuffer, sizeof(writebuffer));
		
		r_bytes=read(socketfd,readbuffer,sizeof(readbuffer));
		if (strchr(readbuffer,'*') != NULL)
            strcpy(writebuffer, getpass(readbuffer));
		
		else{	
			printf("%s",readbuffer);
			if (strchr(readbuffer,'~') != NULL)
            	close(socketfd);
			scanf("%[^\n]%*c",writebuffer);
		}
		//printf("--%s--",writebuffer);
		w_bytes=write(socketfd,writebuffer,sizeof(writebuffer));
		//printf("%d",w_bytes);

	}while(r_bytes>0);
}

void main()
{
	int sd,stat;
	char buf[100];
	sd = socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in cli;
	cli.sin_family = AF_INET;
	cli.sin_addr.s_addr = htonl(INADDR_ANY);
	cli.sin_port = htons(8081);
	
	stat = connect(sd,(struct sockaddr *) &cli, sizeof(cli));
	printf("\nConnection Established");
	
	// read(sd, &buf, 100);
	// printf("\nData From Server : %s",buf);
	// write(sd,"Hello from client",sizeof("Hello from client"));
	connectionhandler(sd);
	
	close(sd);
}
