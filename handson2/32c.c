/*Name: Aswatha Narayanan
 * roll no: MT2022026
 * 32. Write a program to implement semaphore to protect any critical section.
c. protect multiple pseudo resources ( may be two) using counting semaphore
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
	int ctlstatus=semctl(semid,0,SETVAL,sem);
	printf("sme control status: %d\n",ctlstatus);


	struct sembuf semopr;
	semopr.sem_num=0;
	semopr.sem_op=-1;
	semopr.sem_flg=IPC_NOWAIT;
	
	//critical section
	printf("press enter to enter the critical section");
        getchar();

	printf("Locking using semephore\n");
        int semstatus=semop(semid,&semopr,1);
        printf("locking status:%d\n",semstatus);
	
	if(semstatus == -1){
		printf("cannot enter the critical secction\n");
		return 0;
	}
	printf("Inside critical section\n");
	printf("press enter to exit the critical section");
	getchar();


	printf("Unocking using semephore\n");
	semopr.sem_op=1;
	semop(semid,&semopr,1);
	printf("unlocking status:%d\n",semstatus);

	return 0;
}

