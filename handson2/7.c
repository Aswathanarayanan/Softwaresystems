/* Name: Aswatha Narayanan
 * Roll no: MT2022026
 * 
 * 7. Write a simple program to print the created thread ids.
 */

#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
void fun(void* args){
	printf("thread id:%ld\n",pthread_self());
}
int main(){
	void* val[3];
	pthread_t mythread[3];
	int thread_num[3];
	for(int i=0;i<3;i++){
		pthread_t mythread[i];//,mythread2,mythread3;
		thread_num[i]=i;
		pthread_create(&mythread[i],NULL,(void*)fun,&thread_num[i]);
		//pthread_create(&mythread2,NULL,(void*)fun,NULL);
		//pthread_create(&mythread3,NULL,(void*)fun,NULL);
		//void* val;
		pthread_join(mythread[i],&val[i]);
	}
	return 0;
}
