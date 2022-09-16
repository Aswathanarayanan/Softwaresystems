/*Name: ASWATHA NARAYANAN
 *Roll no: MT2022026
 *19. Create a FIFO file by
  a. mknod command
   b. mkfifo command
    c. use strace command to find out, which command (mknod or mkfifo) is better.
     c. mknod system call
      d. mkfifo library function
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	/*mknod test_19_3.txt p
	 * mkfifo test_19_4.txt
	 * strace -c mknod test_19_3.txt p
	 * strace -c mkfifo test_19_4.txt
	 */ 

	//mknod
	mknod("test_19_1.txt",S_IFIFO|0744,0);
	//mkfifo
	mkfifo("test_19_2.txt",0744);
	//
	return 0;
}
