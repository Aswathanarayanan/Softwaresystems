/* Name: Aswatha Narayanan
 * Roll no: MT2022026
 *
 * 7. Write a simple program to print the created thread ids.
 */

#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
void fun(){
        printf("thread id:%ld\n",pthread_self());
}
int main(){
        pthread_t mythread[3];
        for(int i=0;i<3;i++){
                pthread_create(&mythread[i],NULL,(void*)fun,NULL);
                //pthread_join(mythread[i],NULL);
        }
        pthread_exit(NULL);
        return 0;
}
