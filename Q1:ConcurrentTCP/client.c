/*!
* Author : Niranjan A
* Description : This file contains the client side code for a concurrent
* 				client server application using tcp protocol. This means,
*				that the server will be able to handle multiple requests
*				from different clients at the same time. 
*				Here, only a "Hello world" message is received from the 
*				server, when any message is sent to it.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	int sockfd, cs, len; /**< Few variables to store accepted socket descriptor, length of message and socket descriptor respectively */
	char buffer1[200], buffer2[200]; /**< buffer1 is used to store the message to be sent to the server, while buffer 2 holds the received message from the server*/

	/*!
	* Socket address is defined by the struct sockaddr_in and setting it's variables
	*/
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(5000); /**< Same port number as the server needs to be used, since it is used to connect*/

	//!Socket is created, and a desciptor is returned
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//!Connecting the socket to the server, for communication
	int c = connect(sockfd, (struct sockaddr *) &address, sizeof(address));
	if(c==-1){
		printf("Connection failed. Exiting program\n");
		exit(0);
	}
	printf("Enter message\n");
	scanf("%s", &buffer1);
	//! Sending a message to the server
	send(sockfd, buffer1, 200, 0);
	//! Receiving a response back from the server
	recv(sockfd, buffer2, 200, 0);
	printf("Message from Server:\t");
	puts(buffer2);
	//!Closing the socket before exiting the program
	close(sockfd);
	return 0;
}