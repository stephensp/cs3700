#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "client.h"

int main(int argc, char *argv[]) {

	int 	port, studentID;
	char 	*hostname;

	if(argc != 3 && argc != 5) {
		printf("Usage: 3700client <-p port> [hostname] [NEU ID]\n");
		return 0;
	}
	// Creating a client instance
	client *c = (client *)malloc(sizeof(client));
	
	// No port specified, set port to 27993
	if(argc == 3) {
		port = 27993;
		studentID = atoi(argv[2]);
		hostname = argv[1];
		
	}

	// Set port to user specified port
	if(argc == 5) {
		// Get an int version of the char
		// Need to add check for -p flag and valid port number
		port = atoi(argv[2]);
		studentID = atoi(argv[4]);
		hostname = argv[3];
	}
	
	// Set all the client parameters
	setPort(c, port);
	setStudentID(c, studentID);
	setHostname(c, hostname);

	// Now run!
	clientRun(c);

	return 0;
}
