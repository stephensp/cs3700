// client.h
// Header file for all client functions and Client struct

struct client {
	int port;
	int studentID;
};
typedef struct client Client;

void setPort(Client *c, int port);
void setStudentID(Client *c, int studentID);
