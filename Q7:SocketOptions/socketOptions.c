#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

int main(int argc, char const *argv[]) {
	
	int sockfd, optval;
	socklen_t optlen = sizeof(optval);
	struct linger l;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen);
	printf("SO_KEEPALIVE: %s\n", (optval)? "True" : "False");
	optval=1;
	optlen = sizeof(optval);
	setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen);
	getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen);
	printf("SO_KEEPALIVE: %s\n", (optval)? "True" : "False");

	getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &optval, &optlen);
	printf("SO_SNDBUF: %d\n", optval);
	optval = 22222;
	optlen = sizeof(optval);
	setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &optval, optlen);
	getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &optval, &optlen);
	printf("SO_SNDBUF: %d\n", optval);

	getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &optval, &optlen);
	printf("SO_RCVBUF: %d\n", optval);
	optval = 33333;
	optlen = sizeof(optval);
	setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &optval, optlen);
	getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &optval, &optlen);
	printf("SO_RCVBUF: %d\n", optval);

	getsockopt(sockfd, SOL_SOCKET, SO_LINGER, &l, &optlen);
	if(l.l_onoff > 0){
		printf("SO_LINGER is on and linger time in seconds is: %d\n", l.l_linger);
	}
	else{
		printf("SO_LINGER is off\n");
	}
	
	l.l_onoff = 1;
	l.l_linger = 2;
	optlen = sizeof(l);
	setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &l, optlen);
	getsockopt(sockfd, SOL_SOCKET, SO_LINGER, &l, &optlen);
	if(l.l_onoff > 0){
		printf("SO_LINGER is on and linger time in seconds: %d\n", l.l_linger);
	}
	else{
		printf("SO_LINGER is off\n");
	}


	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	getsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &optval, &optlen);
	printf("IPPROTO_TCP: %s\n", (optval==0)?"Off":"On");
	optval = 1;
	optlen = sizeof(optval);
	setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &optval, optlen);
	getsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &optval, &optlen);
	printf("IPPROTO_TCP: %s\n", (optval==0)?"Off":"On");

	return 0;
}