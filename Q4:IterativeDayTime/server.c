#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

int main(int argc, char const *argv[]) {
	int sockfd, cs, sizeOfSocket;
	time_t currentTime;
	struct sockaddr_in address, client;
	address.sin_family = AF_INET;
	address.sin_port = htons(5000);
	address.sin_addr.s_addr = INADDR_ANY;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int b = bind(sockfd, (struct sockaddr *) &address, sizeof(address));
	if(b==-1){
		printf("Binding failed. Exiting program\n");
		exit(0);
	}

	listen(sockfd, 3);
	while(1){
		sizeOfSocket = sizeof(client);
		cs = accept(sockfd, (struct sockaddr *) &client, &sizeOfSocket);
		//sleep(5);
		currentTime = time(0);
		send(cs, ctime(&currentTime), 100, 0);
		close(cs);
	}
	close(sockfd);
	return 0;
}