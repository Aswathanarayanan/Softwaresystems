/*Name: Aswatha Narayanan
 * roll no: MT2022026
 *25. Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
*/

#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main(){
	
	int key=ftok(".",5);
	int msgid=msgget(key,IPC_CREAT | 0700);
	printf("%d\n",msgid);
	struct msqid_ds msg_info;
	int res=msgctl(msgid,IPC_STAT,&msg_info);
	printf("access permission %d\n",msg_info.msg_perm.mode);
	printf("uid %ld\n",msg_info.msg_perm.uid);
	printf("gid %ld\n",msg_info.msg_perm.gid);	
	printf("time of last message sent and received %ld  %ld\n",msg_info.msg_stime,msg_info.msg_rtime);
	printf("time of last change in the message queue %ld\n",msg_info.msg_ctime);
	printf("size of the queue %ld\n",msg_info.__msg_cbytes);
	printf("number of messages in the queue %ld\n",msg_info.msg_qnum);
	printf("maximum number of bytes allowed %ld\n",msg_info.msg_qbytes);
	printf("pid of the msgsnd and msgrcv %d  %ld\n",msg_info.msg_lspid,msg_info.msg_lrpid);
	return 0;
}

