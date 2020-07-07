/**
 *  @file ip.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ip.h"

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include <string.h>
#include <arpa/inet.h>

DR_EXPORT void ub_ip_init_connection(OUT ub_connection_data_t *connection_data,
		char *ip, short port) {

	DR_ASSERT(ip != NULL);

	strncpy(connection_data->ip, ip, IP_SIZE);
	connection_data->port = port;
}

DR_EXPORT void ub_ip_init_connection_via_sockaddr(
		ub_connection_data_t *connection_data, struct sockaddr_in *sock_addr_in) {

	inet_ntop(AF_INET, &(sock_addr_in->sin_addr.s_addr), connection_data->ip,
			IP_SIZE);

	connection_data->port = ntohs(sock_addr_in->sin_port);
}

DR_EXPORT char *ub_ip_get_connection_name(ub_connection_data_t *connection_data) {

	DR_ASSERT(connection_data->ip != NULL);

	char port_string[20];
	dr_snprintf(port_string, 20, "%d", connection_data->port);

	int size = strlen(connection_data->ip) + strlen(port_string) + 2;

	char *ip_port_name = (char *) dr_global_alloc(sizeof(char) * size);

	strcpy(ip_port_name, connection_data->ip);
	strcat(ip_port_name, ":");
	strcat(ip_port_name, port_string);

	return ip_port_name;
}
