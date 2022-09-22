/*Name: Aswatha Narayanan
 * roll no: MT2022026
 * 32. Write a program to implement semaphore to protect any critical section.
 * d. remove the created semaphore
*/

#include<sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>

union semnum{
	int val;
	struct sem_id *buf;
	unsigned short int *array;
};
int main(){
	int key=ftok(".",18);
	union semnum sem;
	sem.val=2;
	int semid=semget(key,1,IPC_CREAT|0744);
	printf("Semid:%d\n",semid);
	int ctlstatus=semctl(semid,0,IPC_RMID,sem);
	printf("sme control status: %d\n",ctlstatus);
	
	return 0;
}

