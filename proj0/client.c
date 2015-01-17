// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include "client.h"

void setPort(client *c, int port) {
	printf(" setting port to %d\n", port);
	c->port = port;
}
void setStudentID(client *c, int studentID) {
	printf(" setting studentID to %d\n", studentID);
	c->studentID = studentID;
}
void setHostname(client *c, char *hostname) {
	printf(" setting hostname to %s\n", hostname);
	c->hostname = hostname;
}
void clientRun(client *c) {
	struct sockaddr_in soc;
	struct hostent *host;
	int sockfd;
	int status;

	// Let's first create a socket
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if(sockfd == -1) {
		printf("Error: socket returned failure\n");
		return;
	}
	
	// Now we need to get the host IP addr
	host = gethostbyname(c->hostname);
	if(host == NULL) {
		printf("Error: could not connect to host\n");
		return;
	}
	// Set socket info
	soc.sin_family = htons(AF_INET);
	soc.sin_port = htons(c->port);
	memcpy(&(soc.sin_addr.s_addr), host->h_addr, host->h_length);

	// Next connect client socket to server socket
	status = connect(sockfd, (struct sockaddr *) &soc, sizeof(struct sockaddr_in));
	
	if(status == -1) {
		printf("Error: failed to connect to socket\n");
		return;
	}
	// Let's make sure to close the connection
	close(sockfd);	
}
