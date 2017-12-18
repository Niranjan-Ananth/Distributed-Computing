/*!
* Author : Niranjan A
* Description : This file contains the server side code for a concurrent
* 				client server application using tcp protocol. This means,
*				that the server will be able to handle multiple requests
*				from different clients at the same time. 
*				Here, only a "Hello world" message is sent back to the
*				clients.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
	
	int cs, len, sockfd; /**< Few variables to store accepted socket descriptor, length of message and socket descriptor respectively */
	pid_t pid; /**< Used to store the pid of the child, when fork is used */
	char buffer[200]; /**< A buffer to store a string, either received by a client, or to send it to a client */

	/*!
	* Socket address is defined by the struct sockaddr_in and setting it's variables
	*/
	struct sockaddr_in address, client;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(5000); /**< Using the port number 5000 for the socket address. Care needs to be taken if port numbers below 1024 are to be used */

	//! Socket is used as an endpoint for communication, and a file descriptor of the socket is returned from the function
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//Reuse the port address, if it is already in use
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) == -1) { 
    	perror("setsockopt"); 
    	exit(1); 
	} 

	//! Bind the socket to the socket address
	int b = bind(sockfd, (struct sockaddr *) &address, sizeof(address));
	//! In case of error in binding, exit the server
	if(b==-1){
		printf("Error in binding. Exiting program.\n");
		exit(0);
	}
	//! Listen for any connections on the socket, with a queue of maximum 5 connections 
	listen(sockfd, 5);
	while(1){
		//! Accept a connection over the socket, and get the descriptor for it
		int l = sizeof(client);
		cs = accept(sockfd, (struct sockaddr *)&client, &l);
		//! Fork a child, to handle the request received over the connection
		pid = fork();
		//! Send a message from the child process, if it was successfully created
		if(pid==0){
			printf("Child successfully created\n");
			//! Close the socket of the child
			close(sockfd);
			//! Receive the message from the client, into the buffer
			len = recv(cs, buffer, 200, 0);
			printf("Length of received message: %d\n", len);
			printf("Message from Client:\t");
			puts(buffer);
			strcpy(buffer, "Hello World");
			//! Send "Hello World" back to the client
			send(cs, buffer, 200, 0);
			close(cs);
			exit(0);
		}
		close(cs);
	}
	return 0;
}