/*Name: Aswatha Narayanan
 * Roll no: MT2022026
 *
 * 30. Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include<stdio.h>
int main(){
	int key =ftok(".",9);
	int shmid=shmget(key,10,IPC_CREAT|0744);
	printf("shmid:%d\n",shmid);
	
	//Writting to shm
	char* attach=shmat(shmid,NULL,0);
        printf("output of shmat:%p\n",attach);
	printf("Enter the message to write\n");
        scanf("%s",attach);

	printf("reading shm:%s\n",attach);

	
	//attaching shared memory
	void* rdonly=shmat(shmid,NULL,SHM_RDONLY);
	printf("output of rdonly shmat:%p\n",rdonly);
	
	//Writting to rdonly shm
	//printf("Enter the message to write");
	//scanf("%[^\n]",attach);
	
	//detach the shared memory
	int dettach=shmdt(attach);
	printf("output of dettach:%d\n",dettach);

	//removing the shared memoryi
	struct shmid_ds shm_info;
	int rem=shmctl(shmid,IPC_RMID,&shm_info);
	printf("output of remove shm:%d",rem);

	return 0;
}
