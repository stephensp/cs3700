// client.h
// Header file for all client functions and client struct

typedef struct {
	char *hostname;
	int port;
	int studentID;
	int sockfd;
} client;

void setPort(client *c, int port);
void setStudentID(client *c, int studentID);
void setHostname(client *c, char *hostname);
void clientRun(client *c);
int clientInit(client *c); 
int clientMath(client *c, char buffer[256]);


