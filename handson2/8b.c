//Name: Aswatha Narayanan
//Roll no: MT2022026
	
//8. Write a separate program using signal system call to catch the following signals.
//b.SIGINT


#include <signal.h>
#include<stdio.h>
#include<unistd.h>
void fun(){
	printf("SIGINT signal");
	exit(0);    ///to exit the function or it will be in infinte loop
}
int main(){
	int singal_status = signal(SIGINT,(void *)fun);
	int s;
	while(1){
		printf("hi\n");
	}
	return 0;
}
