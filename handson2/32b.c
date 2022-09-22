/*Name: Aswatha Narayanan
 * roll no: MT2022026
 * 32. Write a program to implement semaphore to protect any critical section.
b. protect shared memory from concurrent write access
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
	sem.val=1;
	int semid=semget(key,1,IPC_CREAT|0744);
	printf("Semid:%d\n",semid);
	int ctlstatus=semctl(semid,0,SETVAL,sem);
	printf("sme control status: %d\n",ctlstatus);

	int fd=open("ticket.txt",O_RDWR);
	char buf[10];


	struct sembuf semopr;
	semopr.sem_num=0;
	semopr.sem_op=-1;
	semopr.sem_flg=0;
	
	printf("Locking using semephore\n");
	int semstatus=semop(semid,&semopr,1);
	printf("locking status:%d\n",semstatus);
	
	//shared memory
	int shkey =ftok(".",9);
        int shmid=shmget(shkey,10,IPC_CREAT|0744);
        printf("shmid:%d\n",shmid);

        //Writting to shm
        char* attach=shmat(shmid,NULL,0);
        printf("output of shmat:%p\n",attach);
        printf("Enter the message to write\n");
        scanf("%s",attach);
	printf("reading shm:%s\n",attach);

	printf("Unocking using semephore\n");
	semopr.sem_op=1;
	semop(semid,&semopr,1);
	printf("unlocking status:%d\n",semstatus);

	return 0;
}

