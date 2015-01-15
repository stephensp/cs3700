// client.c
#include <stdio.h>
#include <sys/socket.h>
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
	int sockfd;
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if(sockfd == -1) {
		printf("Error: socket returned failure\n");
		return;
	}
	
}
