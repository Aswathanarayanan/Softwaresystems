#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main(){
	int key=ftok(".",2);
	int msgid=msgget(key,IPC_CREAT|0777);
	printf("Key:%d\n",key);
	printf("Msgid:%d\n",msgid);
	return 0;
}
