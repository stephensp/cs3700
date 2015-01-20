// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
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
	char	buffer[256];
	ssize_t	x;
	int	sol;

	if(clientInit(c) == -1) {
		// Gotta add some real error handling
		printf("Error detected, exiting... \n");
		close(c->sockfd);	
		return;
	}

	// Send hello message
	strcpy(buffer, "cs3700spring2015 HELLO 583008\n");
	x = write(c->sockfd, buffer, strlen(buffer));
	printf("%lu bytes written\n", x);

	// Now listen 
	x = read(c->sockfd, buffer, 256); 	
	printf("%s\n", buffer);
	printf("%lu bytes read\n", x);

	// Calling a function to evaluate the string
	sol = clientMath(c, buffer);
	printf("%d\n", sol);
	
	// Let's make sure to close the connection
	close(c->sockfd);	
}
int clientInit(client *c) {
	struct 	sockaddr_in soc;
	struct 	hostent *host;
	int 	status;

	// Let's first create a socket
	c->sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if(c->sockfd == -1) {
		printf("Error: socket returned failure\n");
		return -1;
	}
	
	// Now we need to get the host IP addr
	host = gethostbyname(c->hostname);
	if(host == NULL) {
		printf("Error: could not find host\n");
		return -1;
	}

	// Set socket info
	printf("htonl(port) = %08x\n", c->port);
//	soc.sin_addr.s_addr = inet_addr("129.10.117.250");
	memcpy(&(soc.sin_addr.s_addr), host->h_addr, host->h_length);
	soc.sin_port = htons(c->port);
	soc.sin_family = AF_INET;

	// Next connect client socket to server socket
	status = connect(c->sockfd, (struct sockaddr *) &soc, sizeof(soc));
	
	printf("status = %d\n", status);
	if(status == -1) {
		printf("Error: failed to connect to server\n");
		return -1;
	}

	return 0;
}
int clientMath(client *c, char buffer[256]) {
	printf("%s\n", buffer);
	return 1;
}
