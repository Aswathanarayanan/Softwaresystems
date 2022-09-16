/*Name: Aswatha Narayanan
 * roll no: MT2022026
 * 32. Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
*/

#include<sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include<stdio.h>
union semnum{
	int val;
	struct sem_id *buf;
	unsigned short int *array;
};
int main(){
	int key=ftok(".",8);
	union semnum sem;
	sem.val=3;
	int semid=semget(key,1,IPC_CREAT|0744);
	semctl(semid,0,SETVAL,sem);
	return 0;
}

