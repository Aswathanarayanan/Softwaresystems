/*Name: Aswatha Narayanan
 * roll no: MT2022026
 * 27. Write a program to receive messages from the message queue.
 * a. with 0 as a flag
 * b. with IPC_NOWAIT as a flag
 */


// Using the message sent in 26.c

#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct msgbuf {
       long mtype;
       int mtext;
};
int main(){
	struct msgbuf mg;
	mg.mtype=1;
	int key=ftok(".",5);
        int msgid=msgget(key,IPC_CREAT | 0700);
        printf("%d\n",msgid);
	//printf("hello");
	//printf("hell:%zu",sizeof(mg));
	msgrcv(msgid,&mg,sizeof(struct msgbuf),mg.mtype,IPC_NOWAIT);
	printf("%d",mg.mtext);	
	return 0;
}
