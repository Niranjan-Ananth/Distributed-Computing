/*!
* Author : Niranjan A
* Description : This file contains the client side code for a concurrent
* 				day time client server application using tcp protocol. 
*				This means, that the server will be able to handle multiple 
*				requests from different clients at the same time. 
*				Here, the client receives the server system time, when it
*				makes a connection with the system.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#ifndef maxMessageLength
#define maxMessageLength 100
#endif
int main(int argc, char const *argv[]) {
	
	int sockfd;
	char buffer[maxMessageLength];

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(5000);
	address.sin_addr.s_addr = inet_addr("0.0.0.0");

	//Using a tcp, connection protocol
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int c = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
	//Check if the connection was successful
	if(c==-1){
		printf("Connection failed. Exiting program.\n");
	}
	//Receive the time from the server and display it
	recv(sockfd, buffer, 100, 0);
	puts(buffer);
	close(sockfd);

	return 0;
}