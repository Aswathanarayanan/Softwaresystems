/*Name: Aswatha Narayanan
 * roll no: MT2022026
 * 28. Write a program to change the exiting message queue permission. (use msqid_ds structure)
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
	msg_info.msg_perm.mode=0777;
	int res=msgctl(msgid,IPC_SET,&msg_info);
	printf("changed permission: %d",msg_info.msg_perm.mode);
	return 0;
}

	
