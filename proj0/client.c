// client.c
#include <stdio.h>
#include "client.h"

void setPort(Client *c, int port) {
	printf(" setting port to %d\n", port);
	c->port = port;
}
void setStudentID(Client *c, int studentID) {
	printf(" setting studentID to %d\n", studentID);
	c->studentID = studentID;
}
