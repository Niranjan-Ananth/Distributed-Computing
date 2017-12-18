/*!
* Author : Niranjan A
* Description : This file contains the server side code for a concurrent
* 				day time client server application using tcp protocol. 
*				This means, that the server will be able to handle multiple 
*				requests from different clients at the same time. 
*				Here, the current server time is sent back to the client,
*				when a connection is made with it.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>

int main(int argc, char const *argv[]) {
	int sockfd, cs, sizeOfSocket;
	pid_t pid;
	time_t curtime;

	struct sockaddr_in address, client;
	address.sin_family = AF_INET;
	address.sin_port = htons(5000);
	address.sin_addr.s_addr =  INADDR_ANY;
	//Using a tcp, connection protocol
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int b = bind(sockfd, (struct sockaddr *) &address, sizeof(address));
	if(b==-1){
		printf("Binding failed. Exiting program.\n");
		exit(0);
	}
	//Listening for any connections over the socket
	listen(sockfd, 5);
	while(1){
		sizeOfSocket = sizeof(client);
		//Accepting a connection over the socket
		cs = accept(sockfd, (struct sockaddr *) &client, &sizeOfSocket);
		pid = fork();
		if(pid==0){
			printf("Child successfully created.\n");
			close(sockfd);
			//Putting it to sleep only to demonstrate the concurrency of the server
			sleep(5);
			//Get the current time of the server system
			//time(&curtime); //Or the next line can be used to get the current system time;
			curtime = time(0); // Or curtime = time(NULL);
			//Send the current server system time
			send(cs, ctime(&curtime), 100, 0);
			close(cs);
			exit(0);
		}
	}
	close(sockfd);
	return 0;
} 