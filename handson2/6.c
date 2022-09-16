/* Name: Aswatha Narayanan
 * Roll no: MT2022026
 * 
 * 6. Write a simple program to create three threads.
 */

#include <pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
void fun(void* args){
//	printf("thread id:%ld",pthread_self());
}
int main(){
	
	pthread_t mythread1,mythread2,mythread3;
	pthread_create(&mythread1,NULL,(void*)fun,NULL);
	pthread_create(&mythread2,NULL,(void*)fun,NULL);
	pthread_create(&mythread3,NULL,(void*)fun,NULL);
	return 0;
}
