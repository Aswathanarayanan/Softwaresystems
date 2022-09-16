/*Name: ASWATHA NARAYANAN
 *Roll no: MT2022026
 *23. Write a program to print the maximum number of files can be opened within a process and 
 size of a pipe (circular buffer).
 */

#include<stdio.h>
#include <unistd.h>

int main(){
	int no_of_proc=sysconf(_SC_OPEN_MAX);
	int max_pipe_size=pathconf(".",_PC_PIPE_BUF);
	printf("Max no of files that can be opened by a process %d\nThe max pipe size %d",no_of_proc,max_pipe_size);
	return 0;
}
