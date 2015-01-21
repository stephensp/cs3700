// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client.h"


int SUCCESS	= 0;
int FAIL	= 0;

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
	char	buffer[256], write_buffer[256];
	char	ascSol[7];
	ssize_t	x, buff_length;
	int	sol, cnt, dig, max;

	if(clientInit(c) == -1) {
		// Gotta add some real error handling
		printf("Error detected, exiting... \n");
		close(c->sockfd);	
		return;
	}

	// Send hello message
	strcpy(buffer, "cs3700spring2015 HELLO ");
	sprintf(&(buffer[strlen(buffer)]), "%d", c->studentID);
	buffer[strlen(buffer)] = 10;

	printf("About to write hello message\n");
	
	x = write(c->sockfd, buffer, strlen(buffer));

	int z;
	while(1) {
		// Clear buffers
		memset(buffer,0,256);
		memset(write_buffer,0,256);

		// Now listen 
		x = read(c->sockfd, buffer, 256); 	
		

		// Calling a function to evaluate the string
		sol = clientMath(c, buffer);
		
		if(SUCCESS == 1) {
			printf("%s\n", buffer);
			break;
		}
		if(FAIL == 1) {
			printf("FAILURE\n");
			break;
		}

		strcpy(write_buffer,"cs3700spring2015 ");	
		sprintf(&(write_buffer[17]), "%d", sol);
		buff_length = strlen(write_buffer);
	

		// Add new line
		write_buffer[strlen(write_buffer)] = 10;

		x = write(c->sockfd, write_buffer, strlen(write_buffer));
		
	}

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
	memcpy(&(soc.sin_addr.s_addr), host->h_addr, host->h_length);
	soc.sin_port = htons(c->port);
	soc.sin_family = AF_INET;

	// Next connect client socket to server socket
	status = connect(c->sockfd, (struct sockaddr *) &soc, sizeof(soc));
	
	if(status == -1) {
		printf("Error: failed to connect to server\n");
		return -1;
	}

	return 0;
}
int clientMath(client *c, char buffer[256]) {
	// Now to parse the string in C, which will be ugly	
	char 	m1[] = "cs3700spring2015 ";
	char	m3[] = "STATUS ";
	char	p[3];
	char*	y1;
	char*	y2;
	int 	l1, l2, l3, start, stat, x1, x2, op, q, stat2, q2, sol;
	int 	i;

	l1 = strlen(m1);   	
	l2 = strlen(buffer);
	l3 = strlen(m3);
	stat = 0;
	y1 = (char *) malloc(1000);
	y2 = (char *) malloc(1000);
	memset(y1,0,1000);
	memset(y2,0,1000);

	// First check to make sure that the message is formatted correctly
	for(i = 0; i < (l1+l3); i++) {
		if(i < l1) {
			if(buffer[i] != m1[i]) {
				// Add real error handling
				printf("string does not match, ending\n");
				break;
			}
		}else {
			if(buffer[i] != m3[i-l1]) {
				stat = 1;
				SUCCESS = 1;
				break;
			}
		}
	}
	start = i;	
	
	
	q = 0;
	q2 = 0;
	stat2 = 0;
	for(i = start; i < l2; i++) {
		if(buffer[i] == 10) {
			break;
		}
		if((buffer[i] < 48) || (buffer[i] > 57)) {
			memcpy(p, &(buffer[i]) , 3);
			op = p[1];
			stat2 = 1;
			i = i+2;

		}else if(stat2 == 1) {
			y1[q] = buffer[i];
			q++;
		}else {
			y2[q2] = buffer[i];
			q2++;	
		}


	}
	
	x1 = atoi(y1);
	x2 = atoi(y2);

	free(y1);
	free(y2);

	if(op == 43) {
		return (x1 + x2);
	}
	if(op == 45) {
		return (x2 - x1);
	}
	if(op == 42) { 
		return (x1 * x2);
	}
	if(op == 47) {
		return (x2 / x1);
	}else {
		if(SUCCESS != 1) {
			printf("Error: non valid operator\n");
			FAIL = 1;
		}
		return 0;
	}
	


}
