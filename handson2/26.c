/*Name: Aswatha Narayanan
 * roll no: MT2022026
 *26. Write a program to send messages to the message queue. Check $ipcs -q
 */

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
	printf("Enter the msg to be sent\n");
        scanf("%d",&mg.mtext);
	int key=ftok(".",5);
        int msgid=msgget(key,IPC_CREAT | 0700);
        printf("%d\n",msgid);
	int res=msgsnd(msgid,&mg,sizeof(struct msgbuf),0);
	printf("Message sent");
	return 0;
}
