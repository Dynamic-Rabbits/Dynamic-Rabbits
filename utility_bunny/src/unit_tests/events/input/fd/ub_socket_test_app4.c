/**
 *  @file ub_socket_test_app4.c
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

	char client_message[20];
	int read_size;


	char client_message1[1];
	char client_message2[1];
	char client_message3[1];

	struct sockaddr_storage src_addr;

	struct iovec iov[3];
	iov[0].iov_base=client_message1;
	iov[0].iov_len= 1;
	iov[1].iov_base=client_message2;
	iov[1].iov_len= 1;
	iov[2].iov_base=client_message3;
	iov[2].iov_len= 1;

	struct msghdr message;
	message.msg_name=&src_addr;
	message.msg_namelen=sizeof(src_addr);
	message.msg_iov=iov;
	message.msg_iovlen=3;
	message.msg_control=0;
	message.msg_controllen=0;

	ssize_t count = recvmsg(client_sock,&message,0);

	printf("The char is %c\n", ((char *)message.msg_iov[0].iov_base)[0]);
	printf("The char is %c\n", ((char *)message.msg_iov[1].iov_base)[0]);
	printf("The char is %c\n", ((char *)message.msg_iov[2].iov_base)[0]);

	close(client_sock);
	close(socket_desc);
	return 0;
}

