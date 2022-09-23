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
        pthread_t mythread;
        for(int i=1;i<=3;i++){
                pthread_create(&mythread,NULL,(void*)fun,NULL);
                //pthread_join(mythread,&val[i]);
        }
        return 0;
}
