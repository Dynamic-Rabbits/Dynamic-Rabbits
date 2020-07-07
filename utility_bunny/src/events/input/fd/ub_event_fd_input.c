/**
 *  @file ub_file_input.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ub_event_fd_input.h"

#include "dr_api.h"
#include "drmgr.h"
#include <inttypes.h>
#include "../../../syscalls/ub_syscall_helper.h"
#include "drsyscall.h"

#include "../input_buf/input_buf.h"

#include "fd_option/ub_fd_input_option.h"
#include "../../../string/ub_string.h"
#include "../../../datastructs/sets/ub_str_hashset.h"
#include "../../../datastructs/maps/ub_str_hashmap.h"
#include "../../../datastructs/maps/ub_intptr_hashmap.h"
#include "../../../datastructs/lists/ub_list.h"
#include "../../../datastructs/ub_datastruct.h"
#include "../../../ip/ip.h"
#include "../../../readers/ub_file_reader.h"

/***************************************************************************
 *  Structs
 */

/**
 *  @struct ub_mapped_file_data_t
 *
 *  @var ub_mapped_file_data_t::base_name The basename of the file.
 */
typedef struct {
	char *base_name;
} ub_mapped_file_data_t;

typedef struct {
	char *ip;
	int port;
} ub_mapped_remote_socket_data_t;

typedef struct {
	int port;
} ub_mapped_local_socket_data_t;

/**
 *  @struct ub_mapped_file_data_t
 *  Information of a file mapped to its file descriptor
 *  via fd_to_file_info_map in \p ub_file_mngr_data_t.
 *
 *  @var ub_mapped_file_data_t::offset The current offset value where
 *  the pointer in the file refers at.
 *  @var ub_mapped_file_data_t::base_name The base name of the file.
 */
typedef struct {
	int offset;
	ub_fd_type_t type;

	union {
		ub_mapped_file_data_t file_data;
		ub_mapped_remote_socket_data_t remote_socket_data;
		ub_mapped_local_socket_data_t local_socket_data;
	} fd_data;

	size_t ref_count;
} ub_mapped_fd_data_t;

/**
 *  @struct ub_fd_input_ctx_t
 *  Information of for managing input via files.
 *
 *  @var ub_fd_input_ctx_t::options Options set which specify which
 *  information should be available upon the handling of the callback.
 *  @var ub_fd_input_ctx_t::fd_read_hndlr The function pointer
 *  to the callback.
 *  @var ub_fd_input_ctx_t::base_name_set A set of source identifiers which will be considered. Any
 *  other opened fd, which has its identifier not included in the set, will not trigger the callback
 *  function, unless the consider all is set.
 *  @var ub_fd_input_ctx_t::fd_to_fd_info_map A map that associated live file desc
 *  with \ub_mapped_fd_data_t structs.
 */
typedef struct {
	bool consider_all;
	UB_EV_FD_INPUT_OPT options;
	ub_handle_fd_read_event_t fd_read_hndlr;
	void *identifier_set;
	void *fd_to_info_map;
} ub_fd_input_ctx_t;

/***************************************************************************
 *  Prototypes
 */

static size_t ub_ev_fd_create_identifier(const char *identifier_data,
		ub_fd_type_t fd_type, char **identifier);

static void ub_ev_fd_input_handle_post_syscall(void *drcontext, int sysnum,
		void *user_data);

static void ub_ev_fd_input_handle_socketcall(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx);
static void ub_ev_fd_input_handle_open(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx);
static void ub_ev_fd_input_handle_openat(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx);
static void ub_ev_fd_input_handle_close(void *drcontext,
		ub_fd_input_ctx_t *file_input_ctx);

static void ub_ev_fd_input_handle_mmap2(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx); /* NYI Fully */
static void ub_ev_fd_input_handle_readv(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx);
static void ub_ev_fd_input_handle_preadv(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx);
static void ub_ev_fd_input_handle_lseek(void *drcontext,
		ub_fd_input_ctx_t *file_input_ctx);
static void ub_ev_fd_input_handle_llseek(void *drcontext,
		ub_fd_input_ctx_t *file_input_ctx);
static void ub_ev_fd_input_handle_dup(void *drcontext,
		ub_fd_input_ctx_t *file_input_ctx);
static void ub_ev_fd_input_handle_dup2(void *drcontext,
		ub_fd_input_ctx_t *file_input_ctx);

static void ub_prepare_read_data(ub_fd_input_ctx_t *fd_input_ctx, int fd,
		ub_mapped_fd_data_t *mapped_file_data,
		ub_fd_input_data_t *fd_input_data);
static void ub_ev_fd_input_handle_read(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx);
static void ub_ev_fd_input_handle_pread(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx);
static void ub_ev_fd_input_handle_preadv(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx);

static bool ub_ev_fd_input_standard_filter_syscalls(void *drcontext, int sysnum);
static bool ub_ev_fd_input_socket_filter_syscalls(void *drcontext, int sysnum);
static bool ub_ev_fd_input_file_filter_syscalls(void *drcontext, int sysnum);

static void ub_ev_fd_input_filter_syscalls(ub_fd_input_ctx_t *fd_input_ctx);

static ub_mapped_fd_data_t *ub_ev_fd_input_create_mapping_data();
static ub_mapped_fd_data_t *ub_ev_fd_input_create_file_mapping_data(
		char *base_name);

static ub_mapped_fd_data_t *ub_ev_fd_input_create_remote_socket_mapping_data(
		ub_connection_data_t *connection_data);

static ub_mapped_fd_data_t *ub_ev_fd_input_create_local_socket_mapping_data(
		ub_connection_data_t *connection_data);

static void ub_ev_fd_input_map_fd_data(ub_fd_input_ctx_t *file_input_ctx,
		ssize_t file_desc, ub_mapped_fd_data_t *mapped_file_data);
static void ub_ev_fd_input_destroy_mapping_data(void *mapped_fd_data_opaque);
static void ub_ev_fd_input_handle_sock_connect(unsigned long *args,
		void *drcontext, ub_fd_input_ctx_t *fd_input_ctx);
static void ub_ev_fd_input_handle_sock_bind(unsigned long *args,
		void *drcontext, ub_fd_input_ctx_t *fd_input_ctx);
static void ub_ev_fd_input_handle_sock_accept(unsigned long *args,
		void *drcontext, ub_fd_input_ctx_t *fd_input_ctx);
static void ub_ev_fd_input_handle_sock_recv(unsigned long *args,
		void *drcontext, ub_fd_input_ctx_t *fd_input_ctx);

static void ub_ev_fd_input_handle_sock_recvmsg(unsigned long *args,
		void *drcontext, ub_fd_input_ctx_t *fd_input_ctx);

/***************************************************************************
 *  Implementation
 */

void *ub_ev_fd_input_init_ctx(ub_handle_fd_read_event_t fd_read_hndlr,
		bool consider_all, UB_EV_FD_INPUT_OPT options, client_id_t client_id) {

	drmgr_init();
	drsys_options_t ops = { sizeof(ops), 0, };

	if (drsys_init(client_id, &ops) != DRMF_SUCCESS)
		DR_ASSERT_MSG(false, "drsys failed to init");

	ub_fd_input_ctx_t *fd_input_ctx = (ub_fd_input_ctx_t *) dr_global_alloc(
			sizeof(ub_fd_input_ctx_t));

	fd_input_ctx->consider_all = consider_all;
	fd_input_ctx->identifier_set = ub_str_hashset_create();

	fd_input_ctx->fd_to_info_map = ub_intptr_hashmap_create_map();
	fd_input_ctx->fd_read_hndlr = fd_read_hndlr;

	if (!ub_fd_options_is_file_enabled(options)
			&& !ub_fd_options_is_socket_enabled(options))
		fd_input_ctx->options = options | UB_EV_FD_INPUT_OPT_FILE;
	else
		fd_input_ctx->options = options;

	ub_ev_fd_input_filter_syscalls(fd_input_ctx);

	drmgr_priority_t priority = { sizeof(priority), "utlity_bunny_input",
	NULL, NULL, UB_INPUT_PRIORITY };

	drmgr_register_post_syscall_event_user_data(
			ub_ev_fd_input_handle_post_syscall, &priority,
			(void *) fd_input_ctx);

	return fd_input_ctx;
}

void ub_ev_fd_input_destroy_ctx(void *fd_input_ctx_opaque) {

	ub_fd_input_ctx_t *fd_input_ctx = (ub_fd_input_ctx_t *) fd_input_ctx_opaque;

	ub_intptr_hashmap_destroy_map(fd_input_ctx->fd_to_info_map,
			ub_ev_fd_input_destroy_mapping_data);

	ub_str_hashset_destroy(fd_input_ctx->identifier_set);

	drmgr_unregister_post_syscall_event_user_data(
			ub_ev_fd_input_handle_post_syscall);
	dr_unregister_filter_syscall_event(ub_ev_fd_input_standard_filter_syscalls);

	dr_global_free(fd_input_ctx, sizeof(ub_fd_input_ctx_t));

	drsys_exit();
	drmgr_exit();
}

void ub_ev_fd_input_register_file(void *fd_input_ctx_opaque,
		const char *base_name) {

	ub_fd_input_ctx_t *fd_input_ctx = (ub_fd_input_ctx_t *) fd_input_ctx_opaque;

	DR_ASSERT_MSG(!fd_input_ctx->consider_all, "Consider All option is set!");

	char *identifier = NULL;
	size_t size = ub_ev_fd_create_identifier(base_name, UB_FD_FILE,
			&identifier);
	ub_str_hashset_insert(fd_input_ctx->identifier_set, identifier);
	dr_global_free(identifier, size);
}

void ub_ev_fd_input_register_remote_socket(void *fd_input_ctx_opaque, char *ip,
		short port) {

	ub_fd_input_ctx_t *fd_input_ctx = (ub_fd_input_ctx_t *) fd_input_ctx_opaque;

	DR_ASSERT_MSG(!fd_input_ctx->consider_all, "Consider All option is set!\n");

	ub_connection_data_t connection_data;
	ub_ip_init_connection(&connection_data, ip, port);
	char *ip_port = ub_ip_get_connection_name(&connection_data);

	char *identifier = NULL;
	size_t size = ub_ev_fd_create_identifier(ip_port, UB_FD_REMOTE_SOCKET,
			&identifier);
	ub_str_hashset_insert(fd_input_ctx->identifier_set, identifier);

	dr_global_free(identifier, size);
	ub_string_destroy(ip_port);
}

void ub_ev_fd_input_register_local_socket(void *fd_input_ctx_opaque, short port) {

	ub_fd_input_ctx_t *fd_input_ctx = (ub_fd_input_ctx_t *) fd_input_ctx_opaque;

	DR_ASSERT_MSG(!fd_input_ctx->consider_all, "Consider All option is set!\n");

	char port_string[20];
	dr_snprintf(port_string, 20, "%d", port);

	char *identifier = NULL;
	size_t size = ub_ev_fd_create_identifier(port_string, UB_FD_LOCAL_SOCKET,
			&identifier);
	ub_str_hashset_insert(fd_input_ctx->identifier_set, identifier);

	dr_global_free(identifier, size);
}

static size_t ub_ev_fd_create_identifier(const char *identifier_data,
		ub_fd_type_t fd_type, char **identifier) {

	int str_len = strlen(identifier_data);
	size_t size = (str_len + 2) * sizeof(char);

	*identifier = (char *) dr_global_alloc(size);

	DR_ASSERT(*identifier);

	memcpy(*identifier + 1, identifier_data, str_len + 1);

	switch (fd_type) {

	case UB_FD_REMOTE_SOCKET:
		(*identifier)[0] = 'r';
		break;
	case UB_FD_LOCAL_SOCKET:
		(*identifier)[0] = 'l';
		break;

	case UB_FD_FILE:
		(*identifier)[0] = 'f';
		break;
	}

	return size;
}

/***************************************************************************
 *  SysCall Handlers
 */

/**
 *  The entry point to handling a syscall.
 *
 *  @param sysnum The system call number
 *  @param user_data The ub_fd_input_ctx_t as opaque
 */
static void ub_ev_fd_input_handle_post_syscall(void *drcontext, int sysnum,
		void *user_data) {

	ub_fd_input_ctx_t *fd_input_ctx = (ub_fd_input_ctx_t *) user_data;

	if (sysnum == __NR_open
			&& ub_fd_options_is_file_enabled(fd_input_ctx->options))
		ub_ev_fd_input_handle_open(drcontext, fd_input_ctx);
	else if (sysnum == __NR_openat
			&& ub_fd_options_is_file_enabled(fd_input_ctx->options))
		ub_ev_fd_input_handle_openat(drcontext, fd_input_ctx);
	else if (sysnum == __NR_close)
		ub_ev_fd_input_handle_close(drcontext, fd_input_ctx);
	else if (sysnum == __NR_read)
		ub_ev_fd_input_handle_read(drcontext, fd_input_ctx);
	else if (sysnum == __NR_preadv)
		ub_ev_fd_input_handle_preadv(drcontext, fd_input_ctx);
	else if (sysnum == __NR_pread64)
		ub_ev_fd_input_handle_pread(drcontext, fd_input_ctx);
	else if (sysnum == __NR_dup)
		ub_ev_fd_input_handle_dup(drcontext, fd_input_ctx);
	else if (sysnum == __NR_dup2)
		ub_ev_fd_input_handle_dup2(drcontext, fd_input_ctx);
	else if (sysnum == __NR_socketcall
			&& ub_fd_options_is_socket_enabled(fd_input_ctx->options))
		ub_ev_fd_input_handle_socketcall(drcontext, fd_input_ctx);
	else if (sysnum == __NR_lseek
			&& ub_fd_options_is_read_offset_enabled(fd_input_ctx->options))
		ub_ev_fd_input_handle_lseek(drcontext, fd_input_ctx);
	else if (sysnum == __NR__llseek
			&& ub_fd_options_is_read_offset_enabled(fd_input_ctx->options))
		ub_ev_fd_input_handle_llseek(drcontext, fd_input_ctx);
	else if (sysnum == __NR_readv)
		ub_ev_fd_input_handle_readv(drcontext, fd_input_ctx);
//	else if (sysnum == __NR_mmap2)
//		ub_ev_fd_input_handle_mmap2(drcontext, fd_input_ctx);
}

/**
 *  Handler for socketcall. Argument 0 specifies what type of call was performed.
 *
 *  @param sysnum The system call number.
 *  @param fd_input_ctx The fd input ctx.
 */
static void ub_ev_fd_input_handle_socketcall(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx) {

	intptr_t sock_call;
	ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &sock_call);

	unsigned long *args;
	ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &args);

	switch (sock_call) {

	case SYS_CONNECT:
		if (ub_fd_options_is_remote_socket_enabled(fd_input_ctx->options))
			ub_ev_fd_input_handle_sock_connect(args, drcontext, fd_input_ctx);
		break;

	case SYS_BIND:
		if (ub_fd_options_is_local_socket_enabled(fd_input_ctx->options))
			ub_ev_fd_input_handle_sock_bind(args, drcontext, fd_input_ctx);
		break;

	case SYS_ACCEPT:
	case SYS_ACCEPT4:
		if (ub_fd_options_is_local_socket_enabled(fd_input_ctx->options))
			ub_ev_fd_input_handle_sock_accept(args, drcontext, fd_input_ctx);
		break;

	case SYS_RECV:
		ub_ev_fd_input_handle_sock_recv(args, drcontext, fd_input_ctx);
		break;

	case SYS_RECVFROM:
		ub_ev_fd_input_handle_sock_recv(args, drcontext, fd_input_ctx);
		break;

	case SYS_RECVMSG:
		ub_ev_fd_input_handle_sock_recvmsg(args, drcontext, fd_input_ctx);
		break;
	}
}

static void ub_ev_fd_input_handle_sock_connect(unsigned long *args,
		void *drcontext, ub_fd_input_ctx_t *fd_input_ctx) {

	int file_desc = (int) args[0];

	bool source_info_enabled = ub_fd_options_is_source_info_enabled(
			fd_input_ctx->options);

	if (fd_input_ctx->consider_all && !source_info_enabled) {

		ub_mapped_fd_data_t * mapped_data =
				ub_ev_fd_input_create_remote_socket_mapping_data(NULL);
		ub_ev_fd_input_map_fd_data(fd_input_ctx, file_desc, mapped_data);
		return;
	}

	ub_connection_data_t connection_data;
	ub_ip_init_connection_via_sockaddr(&connection_data,
			(struct sockaddr_in *) args[1]);

	char *ip_port_name = ub_ip_get_connection_name(&connection_data);

	char *identifier;
	size_t size = ub_ev_fd_create_identifier(ip_port_name, UB_FD_REMOTE_SOCKET,
			&identifier);

	bool is_id_included = ub_str_hashset_is_included(
			fd_input_ctx->identifier_set, identifier);
	dr_global_free(identifier, size);
	ub_string_destroy(ip_port_name);

	if (!fd_input_ctx->consider_all && !is_id_included)
		return;

	ub_mapped_fd_data_t * mapped_data;

	if (source_info_enabled)
		mapped_data = ub_ev_fd_input_create_remote_socket_mapping_data(
				&connection_data);
	else
		mapped_data = ub_ev_fd_input_create_remote_socket_mapping_data(NULL);

	ub_ev_fd_input_map_fd_data(fd_input_ctx, file_desc, mapped_data);
}

static void ub_ev_fd_input_handle_sock_bind(unsigned long *args,
		void *drcontext, ub_fd_input_ctx_t *fd_input_ctx) {

	int file_desc = (int) args[0];

	bool source_info_enabled = ub_fd_options_is_source_info_enabled(
			fd_input_ctx->options);

	if (fd_input_ctx->consider_all && !source_info_enabled) {

		ub_mapped_fd_data_t * mapped_data =
				ub_ev_fd_input_create_local_socket_mapping_data(NULL);
		ub_ev_fd_input_map_fd_data(fd_input_ctx, file_desc, mapped_data);
		return;
	}

	ub_connection_data_t connection_data;
	ub_ip_init_connection_via_sockaddr(&connection_data,
			(struct sockaddr_in *) args[1]);

	char port_string[20];
	dr_snprintf(port_string, 20, "%d", connection_data.port);

	char *identifier;
	size_t size = ub_ev_fd_create_identifier(port_string, UB_FD_LOCAL_SOCKET,
			&identifier);
	bool is_id_included = ub_str_hashset_is_included(
			fd_input_ctx->identifier_set, identifier);

	dr_global_free(identifier, size);

	if (!fd_input_ctx->consider_all && !is_id_included)
		return;

	ub_mapped_fd_data_t * mapped_data;

	if (source_info_enabled)
		mapped_data = ub_ev_fd_input_create_local_socket_mapping_data(
				&connection_data);
	else
		mapped_data = ub_ev_fd_input_create_local_socket_mapping_data(NULL);

	ub_ev_fd_input_map_fd_data(fd_input_ctx, file_desc, mapped_data);
}

static void ub_ev_fd_input_handle_sock_accept(unsigned long *args,
		void *drcontext, ub_fd_input_ctx_t *fd_input_ctx) {

	// We need to check if we registered the bind.
	int server_file_desc = (int) args[0];

	ub_intptr_hashmap_lock(fd_input_ctx->fd_to_info_map);

	ub_mapped_fd_data_t *server_mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
					fd_input_ctx->fd_to_info_map, server_file_desc);

	ub_intptr_hashmap_unlock(fd_input_ctx->fd_to_info_map);

	if (server_mapped_file_data == NULL)
		return;

	int file_desc;
	bool succ = ub_get_syscall_result(drcontext, (uint64 *) &file_desc);
	if (!succ)
		return;

	bool source_info_enabled = ub_fd_options_is_source_info_enabled(
			fd_input_ctx->options);

	ub_connection_data_t connection_data;
	connection_data.port =
			server_mapped_file_data->fd_data.local_socket_data.port;

	ub_mapped_fd_data_t * mapped_data =
			ub_ev_fd_input_create_local_socket_mapping_data(&connection_data);
	ub_ev_fd_input_map_fd_data(fd_input_ctx, file_desc, mapped_data);
}

static void ub_ev_fd_input_handle_sock_recv(unsigned long *args,
		void *drcontext, ub_fd_input_ctx_t *fd_input_ctx) {

	int64_t read_size;
	bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
	if (!succ)
		return;

	if (read_size <= ((int64_t) 0))
		return;

	int fd = (int) args[0];

	ub_intptr_hashmap_lock(fd_input_ctx->fd_to_info_map);

	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
					fd_input_ctx->fd_to_info_map, fd);

	ub_intptr_hashmap_unlock(fd_input_ctx->fd_to_info_map);

	if (mapped_file_data == NULL)
		return;

	void *buf = (void *) args[1];

	ub_fd_input_data_t fd_input_data;
	ub_prepare_read_data(fd_input_ctx, fd, mapped_file_data, &fd_input_data);
	fd_input_data.buf_list = ub_create_single_buf_input_list(buf, read_size);
	fd_input_data.offset = mapped_file_data->offset;
	fd_input_ctx->fd_read_hndlr(&fd_input_data);

	ub_list_destroy(fd_input_data.buf_list, ub_destroy_input_buf);

	int flags = args[3];

	if ((flags & MSG_PEEK) == 0
			&& ub_fd_options_is_read_offset_enabled(fd_input_ctx->options))
		mapped_file_data->offset += read_size;

}

static void ub_ev_fd_input_handle_sock_recvmsg(unsigned long *args,
		void *drcontext, ub_fd_input_ctx_t *fd_input_ctx) {

	int64_t read_size = 0;
	bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);

	if (!succ)
		return;

	if (read_size <= ((int64_t) 0))
		return;

	int fd = (int) args[0];

	ub_intptr_hashmap_lock(fd_input_ctx->fd_to_info_map);

	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
					fd_input_ctx->fd_to_info_map, fd);

	ub_intptr_hashmap_unlock(fd_input_ctx->fd_to_info_map);

	if (mapped_file_data == NULL)
		return;

	struct msghdr *msg = (struct msghdr *) args[1];

	ub_fd_input_data_t fd_input_data;
	ub_prepare_read_data(fd_input_ctx, fd, mapped_file_data, &fd_input_data);
	fd_input_data.buf_list = ub_create_input_list_from_iov(read_size,
			msg->msg_iov, msg->msg_iovlen);
	fd_input_data.offset = mapped_file_data->offset;

	fd_input_ctx->fd_read_hndlr(&fd_input_data);

	ub_list_destroy(fd_input_data.buf_list, ub_destroy_input_buf);

	int flags = args[2];

	if ((flags & MSG_PEEK) == 0
			&& ub_fd_options_is_read_offset_enabled(fd_input_ctx->options))
		mapped_file_data->offset += read_size;

}

static void ub_ev_fd_input_handle_open_helper(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx, uintptr_t fd, char *path) {

	bool source_info_enabled = ub_fd_options_is_source_info_enabled(
			fd_input_ctx->options);

	if (fd_input_ctx->consider_all && !source_info_enabled) {

		ub_mapped_fd_data_t * mapped_data =
				ub_ev_fd_input_create_file_mapping_data(
				NULL);
		ub_ev_fd_input_map_fd_data(fd_input_ctx, fd, mapped_data);
		return;
	}

	char *basename = ub_fr_get_basename(path);

	char *identifier;
	size_t size = ub_ev_fd_create_identifier(basename, UB_FD_FILE, &identifier);
	bool is_id_included = ub_str_hashset_is_included(
			fd_input_ctx->identifier_set, identifier);

	dr_global_free(identifier, size);

	if (!fd_input_ctx->consider_all && !is_id_included)
		return;

	ub_mapped_fd_data_t * mapped_data;

	if (source_info_enabled)
		mapped_data = ub_ev_fd_input_create_file_mapping_data(basename);
	else
		mapped_data = ub_ev_fd_input_create_file_mapping_data(NULL);

	ub_ev_fd_input_map_fd_data(fd_input_ctx, fd, mapped_data);

}

static void ub_ev_fd_input_handle_open(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx) {

	uint64 file_desc;
	bool succ = ub_get_syscall_result(drcontext, &file_desc);

	if (!succ)
		return;

	intptr_t path;
	ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &path);

	ub_ev_fd_input_handle_open_helper(drcontext, fd_input_ctx,
			(uintptr_t) file_desc, (char *) path);
}

static void ub_ev_fd_input_handle_openat(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx) {

	uint64 file_desc;
	bool succ = ub_get_syscall_result(drcontext, &file_desc);

	if (!succ)
		return;

	intptr_t path;
	ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &path);

	ub_ev_fd_input_handle_open_helper(drcontext, fd_input_ctx,
			(uintptr_t) file_desc, (char *) path);
}

static void ub_ev_fd_input_handle_close(void *drcontext,
		ub_fd_input_ctx_t *file_input_ctx) {

	bool succ = ub_get_syscall_result(drcontext, NULL);
	if (!succ)
		return;

	ssize_t file_desc;
	ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &file_desc);

	ub_intptr_hashmap_lock(file_input_ctx->fd_to_info_map);

	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_remove_entry(
					file_input_ctx->fd_to_info_map, file_desc);

	ub_intptr_hashmap_unlock(file_input_ctx->fd_to_info_map);

	if (mapped_file_data)
		ub_ev_fd_input_destroy_mapping_data(mapped_file_data);
}

/***************************************************************************
 *  SysCall Handlers: Read, ReadV, PRead, PReadV
 */

static void ub_prepare_read_data(ub_fd_input_ctx_t *fd_input_ctx, int fd,
		ub_mapped_fd_data_t *mapped_file_data,
		ub_fd_input_data_t *fd_input_data) {

	fd_input_data->fd = fd;
	fd_input_data->type = mapped_file_data->type;

	if (mapped_file_data->type == UB_FD_FILE) {

		if (ub_fd_options_is_source_info_enabled(fd_input_ctx->options))
			fd_input_data->source_info.file_info.base_name =
					mapped_file_data->fd_data.file_data.base_name;
		else
			fd_input_data->source_info.file_info.base_name = NULL;

	} else if (mapped_file_data->type == UB_FD_LOCAL_SOCKET) {

		if (ub_fd_options_is_source_info_enabled(fd_input_ctx->options)) {
			fd_input_data->source_info.local_socket_info.port =
					mapped_file_data->fd_data.local_socket_data.port;

		} else {
			fd_input_data->source_info.local_socket_info.port = 0;
		}
	} else if (mapped_file_data->type == UB_FD_REMOTE_SOCKET) {

		if (ub_fd_options_is_source_info_enabled(fd_input_ctx->options)) {

			fd_input_data->source_info.remote_socket_info.ip =
					mapped_file_data->fd_data.remote_socket_data.ip;
			fd_input_data->source_info.remote_socket_info.port =
					mapped_file_data->fd_data.remote_socket_data.port;
		} else {

			fd_input_data->source_info.remote_socket_info.ip = NULL;
			fd_input_data->source_info.remote_socket_info.port = 0;
		}
	}
}

static void ub_ev_fd_input_handle_read(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx) {

	int64_t read_size;
	bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
	if (!succ)
		return;

	if (read_size <= ((int64_t) 0))
		return;

	ptr_uint_t fd;
	ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &fd);

	ub_intptr_hashmap_lock(fd_input_ctx->fd_to_info_map);

	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
					fd_input_ctx->fd_to_info_map, fd);

	ub_intptr_hashmap_unlock(fd_input_ctx->fd_to_info_map);

	if (mapped_file_data == NULL)
		return;

	void *buf;
	ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &buf);

	ub_fd_input_data_t fd_input_data;
	ub_prepare_read_data(fd_input_ctx, fd, mapped_file_data, &fd_input_data);
	fd_input_data.buf_list = ub_create_single_buf_input_list(buf, read_size);
	fd_input_data.offset = mapped_file_data->offset;
	fd_input_ctx->fd_read_hndlr(&fd_input_data);

	ub_list_destroy(fd_input_data.buf_list, ub_destroy_input_buf);

	if (ub_fd_options_is_read_offset_enabled(fd_input_ctx->options))
		mapped_file_data->offset += read_size;
}

static void ub_ev_fd_input_handle_pread(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx) {

	int64_t read_size;
	bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);

	if (!succ)
		return;

	if (read_size <= ((int64_t) 0))
		return;

	ptr_uint_t fd;
	ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &fd);

	ub_intptr_hashmap_lock(fd_input_ctx->fd_to_info_map);
	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
					fd_input_ctx->fd_to_info_map, fd);
	ub_intptr_hashmap_unlock(fd_input_ctx->fd_to_info_map);

	if (mapped_file_data == NULL)
		return;

	void *buf;
	ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &buf);

	ub_fd_input_data_t fd_input_data;
	ub_prepare_read_data(fd_input_ctx, fd, mapped_file_data, &fd_input_data);
	fd_input_data.buf_list = ub_create_single_buf_input_list(buf, read_size);

	if (ub_fd_options_is_read_offset_enabled(fd_input_ctx->options)) {
		int64_t offset = 0;
		ub_get_syscall_arg(drcontext, 3, (ptr_uint_t *) &offset);

		fd_input_data.offset = offset;
	} else
		fd_input_data.offset = 0;

	fd_input_ctx->fd_read_hndlr(&fd_input_data);

	ub_list_destroy(fd_input_data.buf_list, ub_destroy_input_buf);
}

//static void ub_ev_fd_input_handle_mmap2(void *drcontext,
//        ub_fd_input_ctx_t *fd_input_ctx) {
//
//    int64_t addr = 0;
//    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &addr);
//
//    if (!succ)
//        return;
//
//    uintptr_t buf = addr;
//
//    // We got an error. Simply return
//    if (addr < 0)
//        return;
//
//    // Fetch args
//
//    ptr_uint_t fd;
//    ub_get_syscall_arg(drcontext, 4, (ptr_uint_t *) &fd);
//
//    ub_intptr_hashmap_lock(fd_input_ctx->fd_to_info_map);
//    ub_mapped_fd_data_t *mapped_file_data =
//            (ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
//                    fd_input_ctx->fd_to_info_map, fd);
//    ub_intptr_hashmap_unlock(fd_input_ctx->fd_to_info_map);
//
//    if (mapped_file_data == NULL)
//        return;
//
//    ptr_uint_t length;
//    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &length);
//
//    if (length <= 0)
//        return;
//
//    ub_fd_input_data_t fd_input_data;
//    ub_prepare_read_data(fd_input_ctx, fd, mapped_file_data, &fd_input_data);
//    fd_input_data.buf_list = ub_create_single_buf_input_list((void *) buf,
//            length);
//    fd_input_data.offset = mapped_file_data->offset;
//    fd_input_ctx->fd_read_hndlr(&fd_input_data);
//
//    ub_list_destroy(fd_input_data.buf_list, ub_destroy_input_buf);
//
//    if (ub_fd_options_is_read_offset_enabled(fd_input_ctx->options))
//        mapped_file_data->offset += length;
//}

static void ub_ev_fd_input_handle_readv(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx) {

	int64_t read_size = 0;
	bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
	if (!succ)
		return;

	if (read_size <= ((int64_t) 0))
		return;

	int fd;
	ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &fd);

	ub_intptr_hashmap_lock(fd_input_ctx->fd_to_info_map);
	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
					fd_input_ctx->fd_to_info_map, fd);
	ub_intptr_hashmap_unlock(fd_input_ctx->fd_to_info_map);

	if (mapped_file_data == NULL)
		return;

	struct iovec *iov;
	ub_get_syscall_arg(drcontext, 1, (ptr_uint_t*) &iov);

	int iovcnt;
	ub_get_syscall_arg(drcontext, 2, (ptr_uint_t*) &iovcnt);

	ub_fd_input_data_t fd_input_data;
	ub_prepare_read_data(fd_input_ctx, fd, mapped_file_data, &fd_input_data);
	fd_input_data.buf_list = ub_create_input_list_from_iov(read_size, iov,
			iovcnt);
	fd_input_data.offset = mapped_file_data->offset;

	fd_input_ctx->fd_read_hndlr(&fd_input_data);

	ub_list_destroy(fd_input_data.buf_list, ub_destroy_input_buf);

	if (ub_fd_options_is_read_offset_enabled(fd_input_ctx->options))
		mapped_file_data->offset += read_size;
}

static void ub_ev_fd_input_handle_preadv(void *drcontext,
		ub_fd_input_ctx_t *fd_input_ctx) {

	int64_t read_size = 0;
	bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);

	if (!succ)
		return;

	if (read_size <= ((int64_t) 0))
		return;

	int fd;
	ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &fd);

	ub_intptr_hashmap_lock(fd_input_ctx->fd_to_info_map);
	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
					fd_input_ctx->fd_to_info_map, fd);
	ub_intptr_hashmap_unlock(fd_input_ctx->fd_to_info_map);

	if (mapped_file_data == NULL)
		return;
	struct iovec *iov;
	ub_get_syscall_arg(drcontext, 1, (ptr_uint_t*) &iov);

	int iovcnt;
	ub_get_syscall_arg(drcontext, 2, (ptr_uint_t*) &iovcnt);

	ub_fd_input_data_t fd_input_data;
	ub_prepare_read_data(fd_input_ctx, fd, mapped_file_data, &fd_input_data);
	fd_input_data.buf_list = ub_create_input_list_from_iov(read_size, iov,
			iovcnt);
	if (ub_fd_options_is_read_offset_enabled(fd_input_ctx->options)) {
		int64_t offset = 0;
		ub_get_syscall_arg(drcontext, 3, (ptr_uint_t *) &offset);
		fd_input_data.offset = offset;
	} else
		fd_input_data.offset = 0;
	fd_input_ctx->fd_read_hndlr(&fd_input_data);

	ub_list_destroy(fd_input_data.buf_list, ub_destroy_input_buf);
}

/***************************************************************************
 *  SysCall Handlers: LSEEK
 */

static void ub_ev_fd_input_handle_lseek(void *drcontext,
		ub_fd_input_ctx_t *file_input_ctx) {

	if (!ub_fd_options_is_read_offset_enabled(file_input_ctx->options))
		DR_ASSERT_MSG(false,
				"lseek hanlder should not be called because we do not track offsets");

	uint64 resultant_offset;

	bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &resultant_offset);

	if (!succ)
		return;

	ssize_t file_desc;
	ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &file_desc);

	ub_intptr_hashmap_lock(file_input_ctx->fd_to_info_map);
	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
					file_input_ctx->fd_to_info_map, file_desc);
	ub_intptr_hashmap_unlock(file_input_ctx->fd_to_info_map);

	if (mapped_file_data)
		mapped_file_data->offset = (int) resultant_offset;

}

static void ub_ev_fd_input_handle_llseek(void *drcontext,
		ub_fd_input_ctx_t *file_input_ctx) {

	if (!ub_fd_options_is_read_offset_enabled(file_input_ctx->options))
		DR_ASSERT_MSG(false,
				"lseek hanlder should not be called because we do not track offsets");

	uint64 succ;

	ub_get_syscall_result(drcontext, (uint64_t*) &succ);

	if (succ)
		return;

	ssize_t file_desc;
	ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &file_desc);

	ssize_t resultant_offset;
	ub_get_syscall_arg(drcontext, 2, (ptr_uint_t *) &resultant_offset);


	ub_intptr_hashmap_lock(file_input_ctx->fd_to_info_map);
	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
					file_input_ctx->fd_to_info_map, file_desc);
	ub_intptr_hashmap_unlock(file_input_ctx->fd_to_info_map);

	if (mapped_file_data)
		mapped_file_data->offset = (int) resultant_offset;

}

/***************************************************************************
 *  SysCall Handlers: DUP, DUP2
 */

static void ub_ev_fd_input_handle_dup(void *drcontext,
		ub_fd_input_ctx_t *file_input_ctx) {

	int dupped_desc;
	bool succ = ub_get_syscall_result(drcontext, (uint64 *) &dupped_desc);

	if (!succ)
		return;

	ssize_t file_desc;
	ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &file_desc);

	ub_intptr_hashmap_lock(file_input_ctx->fd_to_info_map);
	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
					file_input_ctx->fd_to_info_map, file_desc);
	ub_intptr_hashmap_unlock(file_input_ctx->fd_to_info_map);

	if (mapped_file_data)
		ub_ev_fd_input_map_fd_data(file_input_ctx, dupped_desc,
				mapped_file_data);
}

static void ub_ev_fd_input_handle_dup2(void *drcontext,
		ub_fd_input_ctx_t *file_input_ctx) {

	uint64 dupped_desc;
	bool succ = ub_get_syscall_result(drcontext, (uint64 *) &dupped_desc);

	if (!succ)
		return;

	ssize_t file_desc;
	ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &file_desc);

	if (file_desc == dupped_desc)
		return;

	ub_intptr_hashmap_lock(file_input_ctx->fd_to_info_map);
	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) ub_intptr_hashmap_lookup_entry(
					file_input_ctx->fd_to_info_map, file_desc);
	ub_intptr_hashmap_unlock(file_input_ctx->fd_to_info_map);

	if (mapped_file_data) {
		ub_ev_fd_input_map_fd_data(file_input_ctx, dupped_desc,
				mapped_file_data);
	}
}

/*********************************************************************************
 * FILTERS
 */

static bool ub_ev_fd_input_standard_filter_syscalls(void *drcontext, int sysnum) {

	switch (sysnum) {

	case __NR_dup:
	case __NR_dup2:
	case __NR_lseek:
	case __NR_close:
	case __NR_read:
	case __NR_readv:
		return true;
	}

	return false;
}

static bool ub_ev_fd_input_socket_filter_syscalls(void *drcontext, int sysnum) {

	if (sysnum == __NR_socketcall)
		return true;

	return false;
}

static bool ub_ev_fd_input_file_filter_syscalls(void *drcontext, int sysnum) {

	if (sysnum == __NR_open)
		return true;

	return false;
}

static void ub_ev_fd_input_filter_syscalls(ub_fd_input_ctx_t *fd_input_ctx) {

	drsys_sysnum_t sysnum;
	sysnum.secondary = 0;

	dr_register_filter_syscall_event(ub_ev_fd_input_standard_filter_syscalls);

	if (ub_fd_options_is_file_enabled(fd_input_ctx->options)) {
		dr_register_filter_syscall_event(ub_ev_fd_input_file_filter_syscalls);

		sysnum.number = __NR_open;
		if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
			DR_ASSERT_MSG(false,
					"could not include open during filter_syscalls");
	}

	if (ub_fd_options_is_socket_enabled(fd_input_ctx->options)) {
		dr_register_filter_syscall_event(ub_ev_fd_input_socket_filter_syscalls);

		sysnum.number = __NR_socketcall;
		if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
			DR_ASSERT_MSG(false,
					"could not include open during filter_syscalls");
	}

	sysnum.number = __NR_readv;
	if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
		DR_ASSERT_MSG(false, "could not  include readv during filter_syscalls");

	sysnum.number = __NR_dup;
	if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
		DR_ASSERT_MSG(false, "could not  include dup during filter_syscalls");

	sysnum.number = __NR_dup2;
	if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
		DR_ASSERT_MSG(false, "could not include dup2 during filter_syscalls");

	sysnum.number = __NR_lseek;
	if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
		DR_ASSERT_MSG(false, "could not include lseek during filter_syscalls");

	sysnum.number = __NR_read;
	if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
		DR_ASSERT_MSG(false, "could not include read during filter_syscalls");

	sysnum.number = __NR_close;
	if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
		DR_ASSERT_MSG(false, "could not include close during filter_syscalls");
}

/***************************************************************************
 *  Helper Functions
 */

/**
 *  Maps a file descriptor to file data.
 *
 *  @param file_input_ctx File input context
 *  @param file_desc The file descriptor to map.
 *  @param mapped_file_data The data to map.
 */
static void ub_ev_fd_input_map_fd_data(ub_fd_input_ctx_t *file_input_ctx,
		ssize_t file_desc, ub_mapped_fd_data_t *mapped_file_data) {

	ub_key_value_pair_t key_value;
	key_value.key = file_desc;
	key_value.value = mapped_file_data;

	ub_intptr_hashmap_lock(file_input_ctx->fd_to_info_map);
	ub_mapped_fd_data_t *old_mapped_data = ub_intptr_hashmap_insert_entry(
			file_input_ctx->fd_to_info_map, &key_value);
	ub_intptr_hashmap_unlock(file_input_ctx->fd_to_info_map);

	mapped_file_data->ref_count++;

	if (old_mapped_data)
		ub_ev_fd_input_destroy_mapping_data(old_mapped_data);
}

static ub_mapped_fd_data_t *ub_ev_fd_input_create_mapping_data() {

	ub_mapped_fd_data_t *mapped_file_data =
			(ub_mapped_fd_data_t *) dr_global_alloc(
					sizeof(ub_mapped_fd_data_t));

	mapped_file_data->ref_count = 0;
	mapped_file_data->offset = 0;

	return mapped_file_data;
}

/**
 *  Creates a struct for storing info on a file and is intended to be
 *  mapped to a file descriptor.
 *
 *  Destroyed via \p ub_ev_fd_input_destroy_mapping_data.
 *
 *  @param base_name The base name of the file. The string is stored in the
 *  struct, thus creating a new copy. Accepts NULL, should no base name be required
 *  due to how passed options are set.
 *  @return Returns the newly created data. User's responsibility to perform the
 *  actual mapping.
 */
static ub_mapped_fd_data_t *ub_ev_fd_input_create_file_mapping_data(
		char *base_name) {

	ub_mapped_fd_data_t * ub_mapped_fd_data =
			ub_ev_fd_input_create_mapping_data();

	ub_mapped_fd_data->type = UB_FD_FILE;

	if (base_name)
		ub_mapped_fd_data->fd_data.file_data.base_name = ub_string_create_copy(
				base_name);
	else
		ub_mapped_fd_data->fd_data.file_data.base_name = NULL;

	return ub_mapped_fd_data;
}

/**
 *  Creates a struct for storing info on a remote socket and is intended to be
 *  mapped to a file descriptor.
 *
 *  Destroyed via \p ub_ev_fd_input_destroy_mapping_data.
 *
 *  @param connection_data Details on the connection.
 *  @return Returns the newly created data. User's responsibility to perform the
 *  actual mapping.
 */
static ub_mapped_fd_data_t *ub_ev_fd_input_create_remote_socket_mapping_data(
		ub_connection_data_t *connection_data) {

	ub_mapped_fd_data_t * ub_mapped_fd_data =
			ub_ev_fd_input_create_mapping_data();

	ub_mapped_fd_data->type = UB_FD_REMOTE_SOCKET;

	if (connection_data != NULL) {
		ub_mapped_fd_data->fd_data.remote_socket_data.ip =
				ub_string_create_copy(connection_data->ip);
		ub_mapped_fd_data->fd_data.remote_socket_data.port =
				connection_data->port;
	} else {
		ub_mapped_fd_data->fd_data.remote_socket_data.ip = NULL;
		ub_mapped_fd_data->fd_data.remote_socket_data.port = 0;
	}
	return ub_mapped_fd_data;
}

/**
 *  Creates a struct for storing info on a local socket and is intended to be
 *  mapped to a file descriptor.
 *
 *  Destroyed via \p ub_ev_fd_input_destroy_mapping_data.
 *
 *  @param connection_data Details on the connection. IP may be NULL.
 *  @return Returns the newly created data. User's responsibility to perform the
 *  actual mapping.
 */
static ub_mapped_fd_data_t *ub_ev_fd_input_create_local_socket_mapping_data(
		ub_connection_data_t *connection_data) {

	ub_mapped_fd_data_t * ub_mapped_fd_data =
			ub_ev_fd_input_create_mapping_data();

	ub_mapped_fd_data->type = UB_FD_LOCAL_SOCKET;

	if (connection_data != NULL)
		ub_mapped_fd_data->fd_data.local_socket_data.port =
				connection_data->port;
	else
		ub_mapped_fd_data->fd_data.local_socket_data.port = 0;

	return ub_mapped_fd_data;
}

/**
 *  Destroys the mapping data.
 *
 *  Since file descriptors, due to dup, may map to the same mapping data, a reference
 *  counter is employed to determine when to deallocate completely the struct.
 *
 *  @param mapped_file_data The mapped file data to destroy.
 */
static void ub_ev_fd_input_destroy_mapping_data(void *mapped_fd_data_opaque) {

	ub_mapped_fd_data_t *mapped_fd_data =
			(ub_mapped_fd_data_t *) mapped_fd_data_opaque;

	DR_ASSERT(mapped_fd_data);

	// Decrement the ref counter.
	mapped_fd_data->ref_count--;

	if (mapped_fd_data->ref_count == 0) {

		if (mapped_fd_data->type == UB_FD_FILE
				&& mapped_fd_data->fd_data.file_data.base_name)
			ub_string_destroy(mapped_fd_data->fd_data.file_data.base_name);

		else if (mapped_fd_data->type == UB_FD_REMOTE_SOCKET
				&& mapped_fd_data->fd_data.remote_socket_data.ip)
			ub_string_destroy(mapped_fd_data->fd_data.remote_socket_data.ip);

		dr_global_free(mapped_fd_data, sizeof(ub_mapped_fd_data_t));
	}
}
