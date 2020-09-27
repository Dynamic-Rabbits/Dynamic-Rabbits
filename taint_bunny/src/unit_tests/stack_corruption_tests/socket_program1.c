/**
 *  @file ub_socket_test_app.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

void parse_input(char *userInput)
{
  char arr[20];

  strcpy(arr, userInput);
  printf("Hello there: %s", arr);

}

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

	char client_message[400];
	int read_size;

	while ((read_size = recv(client_sock, client_message, 400, 0)) > 0) {

		client_message[read_size] = '\0';
		printf("The client message is %s\n", client_message);
		break;
	}


	// close the sockets before the crash, otherwise they might just hang!
	close(client_sock);
	close(socket_desc);

	parse_input(client_message);

	return 0;
}
