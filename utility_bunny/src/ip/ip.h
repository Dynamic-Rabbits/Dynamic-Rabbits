/**
 *  @file ip.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef IP_IP_H_
#define IP_IP_H_

#define IP_SIZE 50

#include "dr_api.h"
#include "dr_defines.h"
#include <stdint.h>
#include <netinet/in.h>

/**
 *  @struct connection_data_t Describes a network connection.
 *
 *  @var connection_data_t::ip The IP of the connection.
 *  @var connection_data_t::port The port of the connection.
 */
typedef struct {

	char ip[IP_SIZE];
	short port;

} ub_connection_data_t;

/**
 *  Initialises connection data.
 *
 *  @param connection_data The connection data to initialise.
 *  @param ip The IP of the connection.
 *  @param port The port number of the connection.
 */
DR_EXPORT void ub_ip_init_connection(OUT ub_connection_data_t *connection_data, char *ip, short port);

/**
 *  Initialises connection data from a struct sockaddr_in.
 *
 *  @param connection_data The connection data to initialise
 *  @param sock_addr_in Contains data to use for initialisation.
 */
DR_EXPORT void ub_ip_init_connection_via_sockaddr(ub_connection_data_t *connection_data,
		struct sockaddr_in *sock_addr_in);

/**
 *  Initialises connection data.
 *
 *  @param connection_data The connection data to initialise.
 *  @param ip The IP of the connection.
 *  @param port The port number of the connection.
 */
DR_EXPORT char *ub_ip_get_connection_name(ub_connection_data_t *connection_data);

#endif /* IP_IP_H_ */
