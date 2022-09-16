/* Name: Aswatha Narayanan
 * Roll no: MT2022026
4. Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

int main(){
	int start = __rdtsc();
	int i=0;
	while(i++<100)
		getpid();
	int end=__rdtsc();
	printf("the time differene:%d\n",end-start);
	return 0;
}

