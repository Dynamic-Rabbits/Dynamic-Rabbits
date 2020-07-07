/**
 *  @file ub_socket_test_app6.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc, char *argv[]) {

	int sock;
	struct sockaddr_in server;
	char message[5], server_reply[5];

	//Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(7717);


	if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		return 1;
	}

	puts("Connected\n");

	//Receive a reply from the server
	recv(sock, server_reply, 5, 0);

	printf("The first reply is: %s", server_reply);

	recv(sock, server_reply, 5, 0);

	printf("The second reply is: %s", server_reply);

	close(sock);
}
