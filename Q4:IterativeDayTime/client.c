#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

int main(int argc, char const *argv[]) {
	int sockfd;
	char buffer[100];
	struct timeval startTime, endTime;

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(5000);
	address.sin_addr.s_addr = inet_addr("0.0.0.0");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int c = connect(sockfd, (struct sockaddr *) &address, sizeof(address));
	if(c==-1){
		printf("Connection failed. Exiting program\n");
		exit(0);
	}

	gettimeofday(&startTime, NULL);
	recv(sockfd, buffer, 100, 0);
	gettimeofday(&endTime, NULL);
	puts(buffer);
	printf("Roundtrip time is : %lu microseconds.\n", endTime.tv_usec - startTime.tv_usec);
	close(sockfd);
	return 0;
}