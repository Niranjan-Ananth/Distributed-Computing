#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char const *argv[]) {
	key_t key = 06656;
	int shmid = shmget(key, 4096, 0666);
	printf("Accessing shared memory at : %d\n", shmid);
	int counterValue = 0;
	int *address = (int *) shmat(shmid, NULL, 0);
	counterValue = *address;
	int choice = 1;
	while(choice==1){
		counterValue = *address;
		counterValue++;
		*address = counterValue;
		printf("Counter value: %d\n", *address);
		printf("Enter 1 to increment the counter Value\n");
		scanf("%d", &choice);
	}
	return 0;
}