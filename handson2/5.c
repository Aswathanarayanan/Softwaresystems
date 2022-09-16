/* Name: Aswatha Narayanan
 * Roll no: MT2022026
 *
 * 5. Write a program to print the system limitation of
a. maximum length of the arguments to the exec family of functions.
b. maximum number of simultaneous process per user id.
c. number of clock ticks (jiffy) per second.
d. maximum number of open files
e. size of a page
f. total number of pages in the physical memory
g. number of currently available pages in the physical memory.

*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
	long conf;
	conf=sysconf(_SC_ARG_MAX);
	printf("maximun arg length : %ld\n",conf);
	
	conf=sysconf(_SC_CHILD_MAX);
        printf("maximum number of simultaneous process per user id : %ld\n",conf);

	conf=sysconf(_SC_CLK_TCK);
        printf("number of clock ticks (jiffy) per second : %ld\n",conf);

	conf=sysconf(_SC_OPEN_MAX);
        printf("maximum number of open files : %ld\n",conf);

	conf=sysconf(_SC_PAGESIZE);
        printf("size of a page : %ld\n",conf);

	conf=sysconf(_SC_PHYS_PAGES);
        printf("total number of pages in the physical memory : %ld\n",conf);

	conf=sysconf(_SC_AVPHYS_PAGES);
        printf("number of currently available pages in the physical memory : %ld\n",conf);
	return 0;
}

