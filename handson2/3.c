/*Name: Aswatha Narayanan
 *Roll no: MT2022026
 * 3. Write a program to set (any one) system resource limit. Use setrlimit system call.
 */

#include<stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
int main(){
	struct rlimit limit;
	printf("before changing\n");
	getrlimit(RLIMIT_NPROC,&limit);
        printf("limit on the number of extant process:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	limit.rlim_cur=5537;
        setrlimit(RLIMIT_NPROC,&limit);
	
	printf("after changing\n");
        getrlimit(RLIMIT_NPROC,&limit);
        printf("limit on the number of extant process:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);
	
	return 0;
}

