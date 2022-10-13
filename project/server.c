#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include <string.h>

#include "./admin.h"
#include "./customer.h"
#include "./account.h"
#include "./admin_cred.h"

void connectionhandler(int socketfd){

	int r_bytes,w_bytes;
	char readbuffer[1000],writebuffer[1000];
	strcpy(writebuffer,"Welcome!!\n1.Admin\n2.Customer\nEnter the choice\n");
	w_bytes=write(socketfd,writebuffer,sizeof(writebuffer));

	bzero(writebuffer,sizeof(writebuffer));


	r_bytes=read(socketfd,readbuffer,sizeof(readbuffer));
	int opt=atoi(readbuffer);
	switch (opt)
	{
	case 1:
		//w_bytes=write(socketfd,"logged as admin",sizeof("logged as admin"));
		adminhandler(socketfd);
		break;
	case 2:
		//w_bytes=write(socketfd,"logged as cus",sizeof("logged as cus"));
		//customerhandler(socketfd);
	default:
		w_bytes=write(socketfd,"",sizeof(""));
		break;
	}
}

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
			connectionhandler(csd);
			close(csd);
			_exit(0);
		}
		// else{
		// 	close(csd);
		// }
	}
	close(sd);
}
