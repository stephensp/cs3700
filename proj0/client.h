// client.h
// Header file for all client functions and client struct

typedef struct {
	int port;
	int studentID;
} client;

void setPort(client *c, int port);
void setStudentID(client *c, int studentID);
