/*!
* Author : Niranjan A
* Description : This file contains the client side code for a concurrent client server application using udp protocol. 
*				This means, that the server will be able to handle multiple requests from different clients at the same time, without forming any 'connections'. 
*				Here, the messages sent by the clients to the server are received back from the server.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#ifndef maxLengthOfMessage
#define maxLengthOfMessage 200
#endif

int main(int argc, char const *argv[]) {
	
	int sockfd, lengthOfMessage, sizeOfSocket;
	char buffer1[maxLengthOfMessage], buffer2[maxLengthOfMessage];

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(5000);

	//! Declaring the connection to be UDP type
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sizeOfSocket = sizeof(address);
	printf("Enter message to be sent to the server:\n");
	scanf("%s", &buffer1);
	//! Using sendto instead of send, because we're using a connectionless protocol
	sendto(sockfd, buffer1, maxLengthOfMessage, 0, (struct sockaddr *) &address, sizeOfSocket);
	//! Using recvfrom instead of recv, because we're using a connectionless protocol
	lengthOfMessage = recvfrom(sockfd, buffer2, maxLengthOfMessage, 0, (struct sockaddr *) &address, &sizeOfSocket);
	if(lengthOfMessage == -1){
		printf("Error occured while receving message from the server.\n");
	}
	else{
		printf("Message from server:\t");
		puts(buffer2);
		printf("Length of Message: %d\n", lengthOfMessage);
	}
	close(sockfd);
	return 0;
}
