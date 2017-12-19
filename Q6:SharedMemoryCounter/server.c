#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char const *argv[]) {
	key_t key = 06656;
	int * address;
	int shmid = shmget(key, 4096, IPC_CREAT | 0666);
	printf("Created shared memory at : %d\n", shmid);
	int counterValue = 0;
	address = (int *)shmat(shmid, NULL, 0);
	*address = counterValue;
	printf("Counter initialised to 0.\n");
	while(1);
	return 0;
}