//Name: Aswatha Narayanan
//Rollno: MT2022026
//
//33. Write a program to communicate between two machines using socket.
//

#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include<unistd.h>
int main(){
	int soc=socket(AF_INET,SOCK_STREAM,0);
	printf("Socket:%d\n",soc);
	
	struct sockaddr_in ser;
	ser.sin_family=AF_INET;
	ser.sin_port=htons(1028);
	ser.sin_addr.s_addr=htonl(INADDR_ANY);

	int b=bind(soc,&ser,sizeof(ser));
	printf("Bind:%d\n",b);

	int l=listen(soc,3);
        printf("listen:%d\n",l);

	struct sockaddr_in cli;
	int acc=accept(soc,&cli,sizeof(cli));
	printf("Accepted:%d\n",acc);
	if(acc==-1)
		perror("accept error\n");

	int w=write(acc,"I am server",15);

	char buf_cli[100];
	int r=read(acc,buf_cli,100);
	printf("Msg from cli: \n%s\n\n",buf_cli);

	return 0;
}
