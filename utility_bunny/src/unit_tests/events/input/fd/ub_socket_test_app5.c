/**
 *  @file ub_socket_test_app5.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>

int main(int argc, char *argv[]) {

	int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
		printf("Could not create socket");

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(7717);

	if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("bind failed. Error");
		return 1;
	}
	listen(socket_desc, 3);

	struct sockaddr_in client;
	int len = sizeof(struct sockaddr_in);

	//accept connection from an incoming client
	int client_sock = accept(socket_desc, (struct sockaddr *) &client,
			(socklen_t*) &len);
	if (client_sock < 0) {
		perror("accept failed");
		return 1;
	}
	printf("Connection accepted\n");

	int socket_desc2 = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc2 == -1)
		printf("Could not create socket");

	struct sockaddr_in server2;
	server2.sin_family = AF_INET;
	server2.sin_addr.s_addr = INADDR_ANY;
	server2.sin_port = htons(8888);

	if (bind(socket_desc2, (struct sockaddr *) &server2, sizeof(server2)) < 0) {
		perror("bind failed. Error");
		return 1;
	}
	listen(socket_desc2, 3);

	struct sockaddr_in client2;
	int len2 = sizeof(struct sockaddr_in);

	//accept connection from an incoming client
	int client_sock2 = accept(socket_desc2, (struct sockaddr *) &client,
			(socklen_t*) &len2);
	if (client_sock2 < 0) {
		perror("accept failed");
		return 1;
	}
	printf("Connection accepted\n");

	char client_message[20];
	int read_size;

	char client_message2[20];
	int read_size2;

	struct sockaddr_storage sender2;
	socklen_t sendsize2 = sizeof(sender2);
	bzero(&sender2, sizeof(sender2));

	struct sockaddr_storage sender;
	socklen_t sendsize = sizeof(sender);
	bzero(&sender, sizeof(sender));

	//Receive a message from client
	while ((read_size = recvfrom(client_sock, client_message, 5, 0,
			(struct sockaddr*) &sender, &sendsize)) > 0) {

		client_message[read_size] = '\0';
		printf("The client message is %s\n", client_message);
		break;
	}

	while ((read_size2 = recvfrom(client_sock2, client_message2, 6, 0,
			(struct sockaddr*) &sender2, &sendsize2)) > 0) {

		client_message2[read_size] = '\0';
		printf("The client message is %s\n", client_message2);
		break;
	}

	close(client_sock);
	close(client_sock2);

	close(socket_desc);
	close(socket_desc2);

	return 0;
}

