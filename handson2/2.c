/* Name: Aswatha Narayanan
 * Roll no: MT2022026
 *1. Write a separate program (for each time domain) to set a interval timer in 10sec and 
10micro second
  b. ITIMER_VIRTUAL
 */

#include<stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
int main(){
	struct rlimit limit;
	getrlimit(RLIMIT_AS,&limit);
	printf("Virtual memory:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);
	
	getrlimit(RLIMIT_CPU,&limit);
        printf("CPU Core:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);
	
	getrlimit(RLIMIT_DATA,&limit);
        printf("size of the process's  data  segment:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);
	
	getrlimit(RLIMIT_FSIZE,&limit);
        printf("size in bytes of files that the process may create\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	getrlimit(RLIMIT_LOCKS,&limit);
        printf("combined number of locks  and fcntl leases that this process may establish.\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	getrlimit(RLIMIT_MEMLOCK,&limit);
        printf("umber  of  bytes of memory that may be locked into RAM\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	getrlimit(RLIMIT_MSGQUEUE,&limit);
        printf("the number of bytes that  can  be  allocated for  POSIX  message  queues:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);
	
	getrlimit(RLIMIT_NICE,&limit);
        printf(" ceiling to which the process's nice value  can be  raised:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	getrlimit(RLIMIT_NOFILE,&limit);
        printf("value one greater than the maximum file descriptor number that can be opened by this  process.:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	getrlimit(RLIMIT_NPROC,&limit);
        printf("limit on the number of extant process:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	getrlimit(RLIMIT_RSS,&limit);
        printf("limit (in bytes) on the process's resident set:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	getrlimit(RLIMIT_RTPRIO,&limit);
        printf("ceiling on the real-time priority:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	getrlimit(RLIMIT_RTTIME,&limit);
        printf("limit  (in microseconds) on the amount of CPU time:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	getrlimit(RLIMIT_SIGPENDING,&limit);
        printf("limit on the number of signals that may be queued:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	getrlimit(RLIMIT_STACK,&limit);
        printf("the maximum size of the process stack:\nhardlimit: %ld\nsoftlimit: %ld\n",limit.rlim_max,limit.rlim_cur);

	return 0;
}
