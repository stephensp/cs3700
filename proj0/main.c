#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {

	if(argc < 2) {
		printf("Error: incorrect number of arguments\n");
		return 0;
	}
	if(argc == 2) {
		printf("%s\n", argv[0]);
	}
	return 0;
}
