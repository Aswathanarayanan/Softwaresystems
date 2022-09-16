/* Name: Aswatha Narayanan
 * Roll no: MT2022026
 *1. Write a separate program (for each time domain) to set a interval timer in 10sec and 
10micro second
  c. ITIMER_PROF
 */
 
#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>

/* struct itimerval {
 *     struct timeval it_interval; ** Interval for periodic timer **
       struct timeval it_value;    ** Time until next expiration **
  };
  struct timeval {
       time_t      tv_sec;         ** seconds **
      suseconds_t tv_usec;        ** microseconds **
  };
*/

int main(){
	struct itimerval timer;
	int opt;
	printf("Select the interval timer\n1.10sec\n2.10microsec\n");
	scanf("%d",&opt);
	if(opt==1){
		timer.it_interval.tv_sec = 0;
        	timer.it_interval.tv_usec = 0;
        	timer.it_value.tv_sec = 10;
        	timer.it_value.tv_usec = 0;
	}
	else if(opt==2){
		timer.it_interval.tv_sec = 0;
	        timer.it_interval.tv_usec = 0;
	        timer.it_value.tv_sec = 0;
	        timer.it_value.tv_usec = 10;
	}
	int timestat=setitimer(ITIMER_PROF, &timer, 0);
	//sleep(20);
	return 0;
}
