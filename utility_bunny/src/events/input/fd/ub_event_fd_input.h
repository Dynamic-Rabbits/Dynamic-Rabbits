/**
 *  @file ub_file_input.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef EVENTS_INPUT_FILE_UB_FILE_INPUT_H_
#define EVENTS_INPUT_FILE_UB_FILE_INPUT_H_

#include "../../../location/ub_loc.h"
#include "../input_buf/input_buf_defines.h"
#include <netinet/in.h>

/**
 * Defines flags that specify what information to be available
 * upon the calling of the callback for parsing ci args.
 */
typedef unsigned int UB_EV_FD_INPUT_OPT;
// No additional information
#define UB_EV_FD_INPUT_OPT_BARE 0
#define UB_EV_FD_INPUT_OPT_SOURCE_INFO 1
#define UB_EV_FD_INPUT_OPT_OFFSET 2
#define UB_EV_FD_INPUT_OPT_FILE 4
#define UB_EV_FD_INPUT_OPT_LOCAL_SOCKET 8
#define UB_EV_FD_INPUT_OPT_REMOTE_SOCKET 16

/**
 * @struct file_info_t Information specific to files.
 *
 * @var file_info_t::base_name The base name of the file.
 */
typedef struct {
	char *base_name;
} file_info_t;

/**
 * @struct file_info_t Information specific to remote socket.
 *
 * @var socket_info_t::ip The IP of the socket.
 * @var socket_info_t::port The port of the socket
 */
typedef struct {

	char *ip;
	short port;
} remote_socket_info_t;

/**
 * @struct file_info_t Information specific to local socket.
 *
 * @var socket_info_t::ip The IP of the socket.
 */
typedef struct {

	short port;
} local_socket_info_t;


/**
 * An enum specifying whether the FD pertains to a file or a socket.
 */
typedef enum {
	UB_FD_REMOTE_SOCKET, UB_FD_LOCAL_SOCKET, UB_FD_FILE
} ub_fd_type_t;

/**
 *  @struct ub_fd_input_data_t Stores information about an fd.
 *
 *  @var fd The file descriptor.
 *  @var fd The current offset of the fd.
 *  @var source_info Specific info on file or socket pertaining to the fd.
 *  @var buf_list A list of bufs containing read information. The list is of
 *  type \p ub_input_buf_t.
 */
typedef struct {

	int fd;
	int64_t offset;
	ub_fd_type_t type;
	union {
		file_info_t file_info;
		remote_socket_info_t remote_socket_info;
		local_socket_info_t local_socket_info;
	} source_info;

	void *buf_list;
} ub_fd_input_data_t;

/**
 *  Call-back function when reading from a file descriptor source.
 *
 *  @param ub_fd_input_data_t Contains data of the read, such as the fd number.
 */
typedef void (*ub_handle_fd_read_event_t)(ub_fd_input_data_t *ub_fd_input_data);

/**
 *  Creates a new fd input ctx.
 *
 *  @param fd_read_hndlr A function pointer to the callback.
 *  @param consider_all Specifies whether to hook all reads regardless of source info
 *  @param options Specifies what data will be available to the callback.
 *  @oaram client_id The ID of the client.
 *  @return Returns the newly created fd input ctx.
 */
void *ub_ev_fd_input_init_ctx(ub_handle_fd_read_event_t fd_read_hndlr,
		bool consider_all, UB_EV_FD_INPUT_OPT options, client_id_t client_id);

/**
 * Destroys the fd input ctx created via \p ub_ev_file_input_init_ctx.
 *
 * @param fd_input_ctx The fd input ctx to destroy.
 */
void ub_ev_fd_input_destroy_ctx(void *fd_input_ctx);

/**
 *  Registers a base name such that read of this file will trigger the supplied
 *  callback. Note cannot be called, if considered all is set.
 *
 *  @param fd_input_ctx The fd input ctx
 *  @param base_name The base name of the file to consider.
 */
void ub_ev_fd_input_register_file(void *fd_input_ctx, const char *base_name);

/**
 *  Registers a server port such that reading from a client socket will trigger the supplied
 *  callback. Note cannot be called, if considered all is set.
 *
 *  @param fd_input_ctx The fd input ctx
 *  @param port The port to register.
 */
void ub_ev_fd_input_register_local_socket(void *fd_input_ctx,
		short port);

/**
 *  Registers a socket such that reading from a socket will trigger the supplied
 *  callback. Note cannot be called, if considered all is set.
 *
 *  @param fd_input_ctx The fd input ctx
 *  @param ip The IP of the server.
 *  @param port The port of the server.
 */
void ub_ev_fd_input_register_remote_socket(void *fd_input_ctx,
		char *ip, short port);

#endif /* EVENTS_INPUT_FILE_UB_FILE_INPUT_H_ */
