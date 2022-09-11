/*Name: Aswatha Narayanan
 * roll no: MT2022026
 *29. Write a program to remove the message queue.
*/

#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main(){
	struct msqid_ds msg_info;
        int key=ftok(".",5);
        int msgid=msgget(key,IPC_CREAT | 0700);
        printf("%d\n",msgid);
        int res=msgctl(msgid,IPC_RMID,&msg_info);
	return 0;
}
