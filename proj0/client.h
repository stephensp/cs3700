// client.h
// Header file for all client functions and client struct

typedef struct {
	char *hostname;
	int port;
	int studentID;
} client;

void setPort(client *c, int port);
void setStudentID(client *c, int studentID);
void setHostname(client *c, char *hostname);
void clientRun(client *c);
