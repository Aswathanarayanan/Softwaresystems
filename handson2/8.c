//Name: Aswatha Narayanan
//Roll no: MT2022026
	
//8. Write a separate program using signal system call to catch the following signals.
//a.SIGSEGV


#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void fun(){
	printf("SIGSEGV signal");
	exit(0);    ///to exit the function or it will be in infinte loop
}
int main(){
	int singal_status = signal(SIGSEGV,(void *)fun);
	int s;
	printf("enter the number\n");
	scanf("%d",s);
	return 0;
}
