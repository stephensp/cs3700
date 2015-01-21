// client.h
// Header file for all client functions and client struct

typedef struct {
	char *buffer;
	char *write_buffer;
	char *hostname;
	int port;
	int studentID;
	int sockfd;
} client;

// setPort()
// Sets port number from user input
// @client* 
// @int port number
void setPort(client *c, int port);

// setStudentID()
// Sets studentID from user input
// @client* 
// @int studentID 
void setStudentID(client *c, int studentID);

// setHostname()
// Sets Hostname from user input
// @client* 
// @int setHostname 
void setHostname(client *c, char *hostname);

// clientRun()
// The main function which runs a while loop for sending and receiving
// messages from the server
// @c
void clientRun(client *c);

// clientInit()
// Handles creating the socket and connecting to the server
// @c
// @return -1 on failure 0 on success
int clientInit(client *c); 

// clientMath()
// Evaluates the math expression given by the server
// @c
// @return int solution to the expression
int clientMath(client *c);

// clientCheckSuc()
// Checks thata SUCCCESS message was received and not a wrongly formatted
// message
// @client structure
// @char * buffer to check against, will start at where success message should
// 	exists. 
// @return 1 for success, 0 for failure
int clientCheckSuc(client *c, char *buffer);

