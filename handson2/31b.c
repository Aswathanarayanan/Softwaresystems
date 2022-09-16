/*Name: Aswatha Narayanan
 * roll no: MT2022026
 * 31. Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
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

//we need different key for different semephore ??
int main(){
	int key=ftok(".",8);
	union semnum sem;
	sem.val=3;
	int semid=semget(key,1,IPC_CREAT|0744);
	semctl(semid,0,SETVAL,sem);
	return 0;
}

