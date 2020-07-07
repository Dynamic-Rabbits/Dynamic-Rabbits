/**
 *  @file ip_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "../../utility_bunny.h"
#include "dr_api.h"
#include "drext.h"
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static void test1() {

	ub_connection_data_t connection_data;
	ub_ip_init_connection(&connection_data, "127.0.0.1", 80);
	char *ip_port_name = ub_ip_get_connection_name(&connection_data);

	DR_ASSERT_MSG(strcmp(ip_port_name, "127.0.0.1:80") == 0,
			"ub_ip_test - test1 - 0 - failed...");
	ub_string_destroy(ip_port_name);

	ub_ip_init_connection(&connection_data, "111.0.0.1", 83);
	ip_port_name = ub_ip_get_connection_name(&connection_data);

	DR_ASSERT_MSG(strcmp(ip_port_name, "127.0.0.1:80") != 0,
			"ub_ip_test - test1 - 1 - failed...");
	ub_string_destroy(ip_port_name);
}

static void test2() {

	ub_connection_data_t connection_data;
	ub_ip_init_connection(&connection_data, "127.0.0.1", 80);

	DR_ASSERT_MSG(strcmp(connection_data.ip, "127.0.0.1") == 0,
			"ub_ip_test - test2 - 0 - failed...");

	DR_ASSERT_MSG(connection_data.port == 80,
			"ub_ip_test - test2 - 1 - failed...");
}

static void test3() {

	struct sockaddr_in myaddr;

	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(3490);
	inet_pton(AF_INET, "63.161.169.137", &(myaddr.sin_addr.s_addr));

	ub_connection_data_t connection_data;
	ub_ip_init_connection_via_sockaddr(&connection_data, &myaddr);

	dr_fprintf(STDERR, "The connection is %s\n", connection_data.ip);

	DR_ASSERT_MSG(strcmp(connection_data.ip, "63.161.169.137") == 0,
			"ub_ip_test - test3 - 0 - failed...");

	DR_ASSERT_MSG(connection_data.port == 3490,
			"ub_ip_test - test3 - 1 - failed...");

	char *ip_port_name = ub_ip_get_connection_name(&connection_data);
	DR_ASSERT_MSG(strcmp(ip_port_name, "63.161.169.137:3490") == 0,
			"ub_ip_test - test1 - 1 - failed...");
	ub_string_destroy(ip_port_name);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
}

