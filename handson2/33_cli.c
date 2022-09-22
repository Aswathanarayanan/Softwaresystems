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
	int soc_cli=socket(AF_INET,SOCK_STREAM,0);
	printf("Socket:%d\n",soc_cli);
	
	struct sockaddr_in c;
	c.sin_family=AF_INET;
	c.sin_port=htons(1028);
	c.sin_addr.s_addr=htonl(INADDR_ANY);

	int co=connect(soc_cli,&c,sizeof(c));
	printf("Connect:%d\n",co);

	char buf_ser[100];
	int r=read(soc_cli,buf_ser,100);
	printf("Msg from ser: \n%s\n\n",buf_ser);

	int w=write(soc_cli,"I am client",15);

	return 0;
}
