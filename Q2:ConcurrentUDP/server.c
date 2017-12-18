/*!
* Author : Niranjan A
* Description : This file contains the server side code for a concurrent client server application using udp protocol. 
*				This means, that the server will be able to handle multiple requests from different clients at the same time, without forming any 'connections'. 
*				Here, the messages sent by the clients are sent back to the them.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define maxMessageLength 200
int main(int argc, char const *argv[]) {
	
	int sockfd, lengthOfMessage, sizeOfSocket;
	pid_t pid;
	char buffer[maxMessageLength];

	struct sockaddr_in address, client;
	address.sin_family = AF_INET;
	address.sin_port = htons(5000);
	address.sin_addr.s_addr = INADDR_ANY;
	//! Declaring the connection to be UDP type
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//Reuse the port address, if it is already in use
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) == -1) { 
    	perror("setsockopt"); 
    	exit(1); 
	}
	
	int b = bind(sockfd, (struct sockaddr *) &address, sizeof(address));
	if(b==-1){
		printf("Binding failed. Exiting program.\n");
		exit(0);
	}
	printf("Binding done\n\n");
	
	//! Since it is a connectionless protocol, no need to listen for connections over the socket, or accept them
	while(1){
		sizeOfSocket = sizeof(client);
		//! Using recvfrom instead of recv, because we're using a connectionless protocol
		lengthOfMessage = recvfrom(sockfd, buffer, maxMessageLength, 0, (struct sockaddr *) &client, &sizeOfSocket);
		if(lengthOfMessage != -1){
			printf("\nDatagram from client received\n");
			pid = fork();
			if(pid==0){
				printf("Child successfully created\n");
				printf("Length of message: %d\n", lengthOfMessage);
				printf("Message from client:\t");
				puts(buffer);
				//! Using sendto instead of send, because we're using a connectionless protocol
				sendto(sockfd, buffer, maxMessageLength, 0, (struct sockaddr *) &client, sizeOfSocket);
				close(sockfd);
				exit(0);
			}
		}
		else{
			printf("Error occured while receiving message.\n");
		}
	}
	close(sockfd);
	return 0;
}
