/*
 * tb_syscall_handlers.c
 *
 *      Author: john
 */

/**
 *  @file ub_file_input.c
 *  @brief
 *  @author John F.X. Galea
 */

/**
 * Big thanks to LibDFT authors for handling syscalls.
 * Most of my handlers are based on their code.
 */

#include "tb_syscall_handlers.h"

#define _GNU_SOURCE

#include "../tb_bunny_private.h"

#include "dr_api.h"
#include "drmgr.h"
#include "drsyscall.h"
#include "utility_bunny.h"
#include "tb_syscall_desc.h"
#include <sys/ipc.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <sys/msg.h>

/***************************************************************************
 *  Prototypes
 */

static bool tb_filter_syscalls(void *drcontext, int sysnum);
static void tb_input_handle_post_syscall(void *drcontext, int sysnum,
        void *user_data);
static void tb_set_filter();
static void tb_handle_0_buf_arg(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_1_buf_arg(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_2_buf_arg(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_stat(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_statfs(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_mincore(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_epoll_wait(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_getgroups(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_poll(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_rt_sigpending(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_mmap(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_io_getevents(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_readv(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_sysctl(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_quotactl(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_get_mempolicy(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_mq_timedreceive(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_fcntl(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_syslog(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_ipc(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_socketcall(void *drcontext, tb_context_t *tb_ctx);
static void tb_handle_recvmmsg(void *drcontext, tb_context_t *tb_ctx);
static void tb_recvmmsg_helper(void *drcontext, tb_context_t *tb_ctx,
        size_t ret, struct mmsghdr *mmsghdr_1, struct timespec *time_4);

void tb_syscall_handlers_init(client_id_t client_id, void *tb_ctx) {

    drmgr_init();
    drsys_options_t ops = { sizeof(ops), 0, };

    if (drsys_init(client_id, &ops) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "drsys failed to init");

    tb_set_filter();

    drmgr_priority_t priority = { sizeof(priority), "taint_bunny_syscalls",
    NULL, NULL, UB_INPUT_PRIORITY - 1 };

    // These syscall need to be performed prior to the Utility Bunny's input handlers.
    // Otherwise, input will be tainted, followed by untainted!
    drmgr_register_post_syscall_event_user_data(tb_input_handle_post_syscall,
            &priority, tb_ctx);
}

void tb_syscall_handlers_destroy() {

    dr_unregister_filter_syscall_event(tb_filter_syscalls);
    drmgr_unregister_post_syscall_event_user_data(tb_input_handle_post_syscall);

    drsys_exit();
    drmgr_exit();
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
static void tb_input_handle_post_syscall(void *drcontext, int sysnum,
        void *user_data) {

    tb_context_t *tb_ctx = (tb_context_t *) user_data;

    switch (sysnum) {

	case __NR_read:
	case __NR_getdents:
	case __NR_listxattr:
	case __NR_llistxattr:
	case __NR_flistxattr:
	case __NR_lookup_dcookie:
	case __NR_modify_ldt:
		tb_handle_1_buf_arg(drcontext, tb_ctx);
		break;

	case __NR_preadv:
	case __NR_readv:
		tb_handle_readv(drcontext, tb_ctx);
		break;

	case __NR__sysctl:
		tb_handle_sysctl(drcontext, tb_ctx);
		break;

	case __NR_stat:
	case __NR_fstat:
	case __NR_lstat:
		tb_handle_stat(drcontext, tb_ctx);
		break;

	case __NR_statfs:
	case __NR_fstatfs:
		tb_handle_statfs(drcontext, tb_ctx);
		break;

	case __NR_socketcall:
		tb_handle_socketcall(drcontext, tb_ctx);
		break;

	case __NR_syslog:
		tb_handle_syslog(drcontext, tb_ctx);
		break;

	case __NR_ipc:
		tb_handle_ipc(drcontext, tb_ctx);
		break;


	case __NR_quotactl:
		tb_handle_quotactl(drcontext, tb_ctx);
		break;

	case __NR_ppoll:
	case __NR_poll:
		tb_handle_poll(drcontext, tb_ctx);
		break;

	case __NR_rt_sigpending:
		tb_handle_rt_sigpending(drcontext, tb_ctx);
		break;

	case __NR_getcwd:
		tb_handle_0_buf_arg(drcontext, tb_ctx);
		break;


    case __NR_mmap2:
        tb_handle_mmap(drcontext, tb_ctx);
        break;

    case __NR_getgroups:
        tb_handle_getgroups(drcontext, tb_ctx);
        break;

    case __NR_mincore:
        tb_handle_mincore(drcontext, tb_ctx);
        break;

    case __NR_fcntl:
    case __NR_fcntl64:
        tb_handle_fcntl(drcontext, tb_ctx);
        break;

    case __NR_lgetxattr:
    case __NR_getxattr:
    case __NR_fgetxattr:
    case __NR_readlinkat:
        tb_handle_2_buf_arg(drcontext, tb_ctx);
        break;

    case __NR_io_getevents:
        tb_handle_io_getevents(drcontext, tb_ctx);
        break;

    case __NR_epoll_pwait:
    case __NR_epoll_wait:
        tb_handle_epoll_wait(drcontext, tb_ctx);
        break;

    case __NR_get_mempolicy:
        tb_handle_get_mempolicy(drcontext, tb_ctx);
        break;

    case __NR_mq_timedreceive:
        tb_handle_mq_timedreceive(drcontext, tb_ctx);
        break;

    case __NR_recvmmsg:
        tb_handle_recvmmsg(drcontext, tb_ctx);
        break;

    }

}

/********************************************************************************
 * System Call Handlers
 */

static void tb_handle_socketcall(void *drcontext, tb_context_t *tb_ctx) {

    int64_t ret = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &ret);
    if (!succ)
        return;

    if (ret <= ((int64_t) 0))
        return;

    struct msghdr *msg;

    ub_input_buf_t * input_buf;
    int indx;

    int cmd;
    ub_get_syscall_arg(drcontext, 0, (ptr_uint_t*) &cmd);

    unsigned long *args;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t*) &args);

    /* demultiplex the socketcall */
    switch (cmd) {

    case SYS_ACCEPT:
    case SYS_ACCEPT4:
    case SYS_GETSOCKNAME:
    case SYS_GETPEERNAME:
        /* addr argument is provided */
        if ((void *) args[1] != NULL) {

            /* clear the tag bits */
            tb_untaint_mem_block(tb_ctx, (uintptr_t) args[1],
                    *((int *) args[2]));

            /* clear the tag bits */
            tb_untaint_mem_block(tb_ctx, (uintptr_t) args[2], sizeof(int));
        }
        break;
    case SYS_SOCKETPAIR:
        tb_untaint_mem_block(tb_ctx, (uintptr_t) args[3], (sizeof(int) * 2));
        break;
    case SYS_RECV:

        tb_untaint_mem_block(tb_ctx, (uintptr_t) args[1], (size_t) ret);
        break;
    case SYS_RECVFROM:

        tb_untaint_mem_block(tb_ctx, (uintptr_t) args[1], (size_t) ret);

        if ((void *) args[4] != NULL) {
            tb_untaint_mem_block(tb_ctx, (uintptr_t) args[4],
                    *((int *) args[5]));

            tb_untaint_mem_block(tb_ctx, (uintptr_t) args[5], sizeof(int));
        }
        break;

    case SYS_GETSOCKOPT:
        tb_untaint_mem_block(tb_ctx, (uintptr_t) args[3], *((int *) args[4]));

        tb_untaint_mem_block(tb_ctx, (uintptr_t) args[4], sizeof(int));
        break;
    case SYS_RECVMSG:

        msg = (struct msghdr *) args[1];

        if (msg->msg_name != NULL) {
            /* clear the tag bits */
            tb_untaint_mem_block(tb_ctx, (uintptr_t) msg->msg_name,
                    msg->msg_namelen);

            tb_untaint_mem_block(tb_ctx, (uintptr_t) &msg->msg_namelen,
                    sizeof(int));
        }

        if (msg->msg_control != NULL) {
            tb_untaint_mem_block(tb_ctx, (uintptr_t) msg->msg_control,
                    msg->msg_controllen);

            tb_untaint_mem_block(tb_ctx, (uintptr_t) &msg->msg_controllen,
                    sizeof(int));
        }

        tb_untaint_mem_block(tb_ctx, (uintptr_t) &msg->msg_flags, sizeof(int));

        void *buf_list = ub_create_input_list_from_iov((size_t) ret,
                msg->msg_iov, msg->msg_iovlen);

        void *buf_it = ub_list_get_start_it(buf_list);

        while (buf_it) {

            ub_input_buf_t * input_buf =
                    (ub_input_buf_t *) ub_list_get_it_value(buf_it);

            tb_untaint_mem_block(tb_ctx, (uintptr_t) input_buf->buf,
                    (int) input_buf->size);

            // We need to store the entry label in the
            buf_it = ub_list_get_next_it(buf_it);
        }

        ub_list_destroy(buf_list, ub_destroy_input_buf);

        break;
    case SYS_RECVMMSG:

        tb_recvmmsg_helper(drcontext, tb_ctx, ret, (struct mmsghdr *) args[1],
                (struct timespec *) args[4]);

        break;
    default:
        /* nothing to do */
        return;
    }
}

static void tb_handle_recvmmsg(void *drcontext, tb_context_t *tb_ctx) {

    int64_t ret = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &ret);
    if (!succ)
        return;

    if (ret <= ((int64_t) 0))
        return;

    struct mmsghdr *mmsghdr;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t*) &mmsghdr);

    struct timespec *time_4;
    ub_get_syscall_arg(drcontext, 4, (ptr_uint_t*) &time_4);

    tb_recvmmsg_helper(drcontext, tb_ctx, ret, mmsghdr, time_4);
}

static void tb_recvmmsg_helper(void *drcontext, tb_context_t *tb_ctx,
        size_t ret, struct mmsghdr *mmsghdr_1, struct timespec *time_4) {

    struct mmsghdr *msg;
    struct msghdr *m;

    size_t iov_tot;

    size_t i, j;
    struct iovec *iov;

    size_t tot;

    for (i = 0; i < ret; i++) {
        /* get the next mmsghdr structure */
        msg = mmsghdr_1 + i;

        /* extract the message header */
        m = &msg->msg_hdr;

        /* source address specified */
        if (m->msg_name != NULL) {
            /* clear the tag bits */
            tb_untaint_mem_block(tb_ctx, (uintptr_t) m->msg_name,
                    m->msg_namelen);

            /* clear the tag bits */
            tb_untaint_mem_block(tb_ctx, (uintptr_t) &m->msg_namelen,
                    sizeof(int));
        }

        /* ancillary data specified */
        if (m->msg_control != NULL) {
            /* clear the tag bits */
            tb_untaint_mem_block(tb_ctx, (uintptr_t) m->msg_control,
                    m->msg_controllen);

            /* clear the tag bits */
            tb_untaint_mem_block(tb_ctx, (uintptr_t) &m->msg_controllen,
                    sizeof(int));
        }

        /* flags; clear the tag bits */
        tb_untaint_mem_block(tb_ctx, (uintptr_t) &m->msg_flags, sizeof(int));

        /* total bytes received; clear the tag bits */
        tot = (size_t) msg->msg_len;
        tb_untaint_mem_block(tb_ctx, (uintptr_t) &msg->msg_len,
                sizeof(unsigned));

        void *buf_list = ub_create_input_list_from_iov((size_t) ret, m->msg_iov,
                m->msg_iovlen);

        void *buf_it = ub_list_get_start_it(buf_list);

        while (buf_it) {

            ub_input_buf_t * input_buf =
                    (ub_input_buf_t *) ub_list_get_it_value(buf_it);

            tb_untaint_mem_block(tb_ctx, (uintptr_t) input_buf->buf,
                    (int) input_buf->size);

            // We need to store the entry label in the
            buf_it = ub_list_get_next_it(buf_it);
        }

        ub_list_destroy(buf_list, ub_destroy_input_buf);

    }

    if (time_4 != NULL)
        tb_untaint_mem_block(tb_ctx, (uintptr_t) time_4,
                sizeof(struct timespec));

}

static void tb_handle_ipc(void *drcontext, tb_context_t *tb_ctx) {

    int64_t ret = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &ret);
    if (!succ)
        return;

    if (ret <= ((int64_t) 0))
        return;

    size_t call;
    ub_get_syscall_arg(drcontext, 0, (ptr_uint_t*) &call);

    int second;
    ub_get_syscall_arg(drcontext, 2, (ptr_uint_t*) &second);
    second -= IPC_FIX;

    int third;
    ub_get_syscall_arg(drcontext, 3, (ptr_uint_t*) &third);
    third -= IPC_FIX;

    void *ptr;
    ub_get_syscall_arg(drcontext, 4, (ptr_uint_t*) &ptr);

    union semun *su;

    switch (call) {

    case MSGCTL:

        /* differentiate based on the cmd */
        switch (second) {
        case IPC_STAT:
        case MSG_STAT:
            /* clear the tag bits */
            tb_untaint_mem_block(tb_ctx, (uintptr_t) ptr,
                    sizeof(struct msqid_ds));
            break;

        case IPC_INFO:
        case MSG_INFO:
            /* clear the tag bits */
            tb_untaint_mem_block(tb_ctx, (uintptr_t) ptr,
                    sizeof(struct msginfo));
            break;
        default:
            /* nothing to do */
            return;
        }
        break;

        /* shmctl() */
    case SHMCTL:

        /* differentiate based on the cmd */
        switch (second) {
        case IPC_STAT:
        case SHM_STAT:
            /* clear the tag bits */
            tb_untaint_mem_block(tb_ctx, (uintptr_t) ptr,
                    sizeof(struct shmid_ds));
            break;

        case IPC_INFO:
        case SHM_INFO:
            /* clear the tag bits */
            tb_untaint_mem_block(tb_ctx, (uintptr_t) ptr,
                    sizeof(struct shminfo));
            break;
        default:
            /* nothing to do */
            return;
        }
        break;

    case SEMCTL:

        su = (union semun *) ptr;

        /* differentiate based on the cmd */
        switch (third) {
        case IPC_STAT:
        case SEM_STAT:
            tb_untaint_mem_block(tb_ctx, (uintptr_t) su->buf,
                    sizeof(struct semid_ds));
            break;

        case IPC_INFO:
        case SEM_INFO:
            tb_untaint_mem_block(tb_ctx, (uintptr_t) su->buf,
                    sizeof(struct seminfo));
            break;

        default:
            /* nothing to do */
            return;
        }
        break;
        /* msgrcv() */
    case MSGRCV:

        /* clear the tag bits */
        tb_untaint_mem_block(tb_ctx, (uintptr_t) ptr,
                (size_t) ret + sizeof(long));
        break;
    default:
        /* nothing to do */
        return;
    }
}

static void tb_handle_syslog(void *drcontext, tb_context_t *tb_ctx) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;

    if (read_size <= ((int64_t) 0))
        return;

    int type;
    ub_get_syscall_arg(drcontext, 0, (ptr_uint_t*) &type);

    char *bufp;
    ub_get_syscall_arg(drcontext, 0, (ptr_uint_t*) &bufp);

    switch (type) {
    case 2:
    case 3:
    case 4:
        tb_untaint_mem_block(tb_ctx, (uintptr_t) bufp, read_size);
        break;
    default:
        /* nothing to do */
        return;
    }
}

static void tb_handle_sysctl(void *drcontext, tb_context_t *tb_ctx) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;

    if (read_size <= ((int64_t) 0))
        return;

    struct __sysctl_args *args;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t*) &args);

    tb_untaint_mem_block(tb_ctx, (uintptr_t) args->newval, args->newlen);

    if (args->oldval != NULL) {
        tb_untaint_mem_block(tb_ctx, (uintptr_t) args->oldval, *args->oldlenp);
        tb_untaint_mem_block(tb_ctx, (uintptr_t) args->oldval, *args->oldlenp);
        tb_untaint_mem_block(tb_ctx, (uintptr_t) args->oldlenp, sizeof(size_t));
    }

}

static void tb_handle_readv(void *drcontext, tb_context_t *tb_ctx) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;

    if (read_size <= ((int64_t) 0))
        return;

    struct iovec *iov;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t*) &iov);

    int iovcnt;
    ub_get_syscall_arg(drcontext, 2, (ptr_uint_t*) &iovcnt);

    void *buf_list = ub_create_input_list_from_iov(read_size, iov, iovcnt);

    void *buf_it = ub_list_get_start_it(buf_list);

    while (buf_it) {

        ub_input_buf_t * input_buf = (ub_input_buf_t *) ub_list_get_it_value(
                buf_it);

        tb_untaint_mem_block(tb_ctx, (uintptr_t) input_buf->buf,
                (int) input_buf->size);

        // We need to store the entry label in the
        buf_it = ub_list_get_next_it(buf_it);
    }

    ub_list_destroy(buf_list, ub_destroy_input_buf);
}

static void tb_handle_mmap(void *drcontext, tb_context_t *tb_ctx) {

    int64_t addr_opaque = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &addr_opaque);
    if (!succ)
        return;

    void * addr = (void *) (int) addr_opaque;

    if (addr == MAP_FAILED)
        return;

    size_t size = 0;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &size);

    int flags = 0;
    ub_get_syscall_arg(drcontext, 3, (ptr_uint_t *) &flags);

    if (flags & MAP_GROWSDOWN)
        addr = addr - size;

    tb_untaint_mem_block(tb_ctx, (uintptr_t) addr, size);
}

static void tb_handle_io_getevents(void *drcontext, tb_context_t *tb_ctx) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;

    if (read_size <= ((int64_t) 0))
        return;

    struct io_event * io_event;
    ub_get_syscall_arg(drcontext, 3, (ptr_uint_t *) &io_event);

    struct timespec * timeout;
    ub_get_syscall_arg(drcontext, 4, (ptr_uint_t *) &timeout);

    tb_untaint_mem_block(tb_ctx, (uintptr_t) io_event, sizeof(struct io_event));
    tb_untaint_mem_block(tb_ctx, (uintptr_t) timeout, sizeof(struct timespec));

}

static void tb_handle_rt_sigpending(void *drcontext, tb_context_t *tb_ctx) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;

    if (read_size <= ((int64_t) 0))
        return;

    int size;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &size);

    struct pollfd *set;
    ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &set);

    tb_untaint_mem_block(tb_ctx, (uintptr_t) set, size);
}

static void tb_handle_poll(void *drcontext, tb_context_t *tb_ctx) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;

    if (read_size <= ((int64_t) 0))
        return;

    int number_of_fds;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &number_of_fds);

    struct pollfd *array;
    ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &array);

    for (int i = 0; i < number_of_fds; i++) {

        struct pollfd *poll_fd = array + i;

        /* clear the tag bits */
        tb_untaint_mem_block(tb_ctx, (uintptr_t) &poll_fd->revents,
                sizeof(short));
    }
}

static void tb_handle_n_buf_arg(void *drcontext, tb_context_t *tb_ctx,
        int arg_buf) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;

    if (read_size <= ((int64_t) 0))
        return;

    int buf;
    ub_get_syscall_arg(drcontext, arg_buf, (ptr_uint_t *) &buf);

    tb_untaint_mem_block(tb_ctx, buf, read_size);
}

static void tb_handle_0_buf_arg(void *drcontext, tb_context_t *tb_ctx) {

    tb_handle_n_buf_arg(drcontext, tb_ctx, 0);
}

static void tb_handle_1_buf_arg(void *drcontext, tb_context_t *tb_ctx) {

    tb_handle_n_buf_arg(drcontext, tb_ctx, 1);
}

static void tb_handle_2_buf_arg(void *drcontext, tb_context_t *tb_ctx) {

    tb_handle_n_buf_arg(drcontext, tb_ctx, 2);
}

static void tb_handle_epoll_wait(void *drcontext, tb_context_t *tb_ctx) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;
    if (read_size <= ((int64_t) 0))
        return;

    int buf;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &buf);

    tb_untaint_mem_block(tb_ctx, buf, sizeof(struct epoll_event) * read_size);
}

static void tb_handle_stat(void *drcontext, tb_context_t *tb_ctx) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;
    if (read_size <= ((int64_t) 0))
        return;

    int buf;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &buf);

    tb_untaint_mem_block(tb_ctx, buf, sizeof(struct stat));
}

static void tb_handle_statfs(void *drcontext, tb_context_t *tb_ctx) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;
    if (read_size <= ((int64_t) 0))
        return;

    int buf;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &buf);

    tb_untaint_mem_block(tb_ctx, buf, sizeof(struct statfs));

}

static void tb_handle_getgroups(void *drcontext, tb_context_t *tb_ctx) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;

    if (read_size <= ((int64_t) 0))
        return;

    int number_of_guests;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &number_of_guests);

    int buf;
    ub_get_syscall_arg(drcontext, 2, (ptr_uint_t *) &buf);

    size_t block_size = sizeof(gid_t) * number_of_guests;

    tb_untaint_mem_block(tb_ctx, buf, block_size);
}

static void tb_handle_mincore(void *drcontext, tb_context_t *tb_ctx) {

    int64_t read_size = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &read_size);
    if (!succ)
        return;

    if (read_size <= ((int64_t) 0))
        return;

    int length;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &length);

    int buf;
    ub_get_syscall_arg(drcontext, 2, (ptr_uint_t *) &buf);

    size_t page_size = dr_page_size();
    size_t block_size = (length + page_size - 1) / page_size;

    tb_untaint_mem_block(tb_ctx, buf, block_size);
}

static void tb_handle_quotactl(void *drcontext, tb_context_t *tb_ctx) {

    int64_t ret = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &ret);
    if (!succ)
        return;

    if (ret <= ((int64_t) 0))
        return;

    size_t size;

    void *addr;
    ub_get_syscall_arg(drcontext, 3, (ptr_uint_t *) &addr);

    int cmd;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &cmd);

    /* different offset ranges */
    switch (cmd) {

    case Q_GETFMT:
        size = sizeof(__u32 );
        break;

    //case Q_GETINFO:
    //    size = sizeof(struct if_dqinfo);
    //    break;

    //case Q_GETQUOTA:
    //    size = sizeof(struct if_dqblk);
    //    break;

    case Q_XGETQSTAT:
        size = sizeof(struct fs_quota_stat);
        break;

    case Q_XGETQUOTA:
        size = sizeof(struct fs_disk_quota);
        break;

    default:
        /* nothing to do */
        return;
    }

    tb_untaint_mem_block(tb_ctx, (uintptr_t) addr, size);
}

static void tb_handle_get_mempolicy(void *drcontext, tb_context_t *tb_ctx) {

    int64_t ret = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &ret);
    if (!succ)
        return;

    if (ret <= ((int64_t) 0))
        return;

    unsigned long flags;
    ub_get_syscall_arg(drcontext, 4, (ptr_uint_t *) &flags);

    int *mode;
    ub_get_syscall_arg(drcontext, 0, (ptr_uint_t *) &mode);

    unsigned long *nodemask;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &nodemask);

    if (flags == 0) {
        tb_untaint_mem_block(tb_ctx, (uintptr_t) mode, sizeof(int));
        tb_untaint_mem_block(tb_ctx, (uintptr_t) nodemask,
                sizeof(unsigned long));
        return;
    }

    if ((flags & MPOL_F_MEMS_ALLOWED) != 0) {
        ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &nodemask);
        return;
    }

    if ((flags & MPOL_F_ADDR) != 0 && (flags & MPOL_F_NODE) == 0) {

        if (mode != NULL)
            tb_untaint_mem_block(tb_ctx, (uintptr_t) mode, sizeof(int));

        if (nodemask != NULL)
            tb_untaint_mem_block(tb_ctx, (uintptr_t) nodemask,
                    sizeof(unsigned long));
        return;
    }

    if ((flags & MPOL_F_ADDR) != 0 && (flags & MPOL_F_NODE) != 0) {
        tb_untaint_mem_block(tb_ctx, (uintptr_t) mode, sizeof(int));
        return;
    }

    if ((flags & MPOL_F_NODE) != 0) {
        tb_untaint_mem_block(tb_ctx, (uintptr_t) mode, sizeof(int));
        return;
    }
}

static void tb_handle_mq_timedreceive(void *drcontext, tb_context_t *tb_ctx) {

    int64_t ret = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &ret);
    if (!succ)
        return;

    if (ret <= ((int64_t) 0))
        return;

    char * msg_ptr;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &msg_ptr);

    size_t *priority;
    ub_get_syscall_arg(drcontext, 4, (ptr_uint_t *) &priority);

    /* clear the tag bits */
    tb_untaint_mem_block(tb_ctx, (uintptr_t) msg_ptr, (size_t) ret);

    /* priority argument is supplied */
    if (priority != NULL)
        /* clear the tag bits */
        tb_untaint_mem_block(tb_ctx, (uintptr_t) priority, sizeof(size_t));
}

static void tb_handle_fcntl(void *drcontext, tb_context_t *tb_ctx) {

    int64_t ret = 0;
    bool succ = ub_get_syscall_result(drcontext, (uint64_t*) &ret);
    if (!succ)
        return;

    if (ret <= ((int64_t) 0))
        return;

    int cmd;
    ub_get_syscall_arg(drcontext, 1, (ptr_uint_t *) &cmd);

    int arg;
    ub_get_syscall_arg(drcontext, 2, (ptr_uint_t *) &arg);

    /* differentiate based on the cmd argument */
    switch (cmd) {
    /* F_GETLK */
    case F_GETLK:
        /* clear the tag bits */
        tb_untaint_mem_block(tb_ctx, (uintptr_t) arg, sizeof(struct flock));
        break;
        /* F_GETLK64 */
    case F_GETLK64:
#ifdef __USE_LARGEFILE64
        /* clear the tag bits */
        tb_untaint_mem_block(tb_ctx, (uintptr_t) arg, sizeof(struct flock64));
        break;
#endif
    default:
        /* nothing to do */
        break;
    }
}

static void tb_set_filter() {

    dr_register_filter_syscall_event(tb_filter_syscalls);

    drsys_sysnum_t sysnum;
    sysnum.secondary = 0;

    sysnum.number = __NR_readv;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_getdents;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_listxattr;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_llistxattr;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_flistxattr;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_lookup_dcookie;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_modify_ldt;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_readv;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_preadv;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR__sysctl;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_stat;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_fstat;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_lstat;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_statfs;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_fstatfs;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_socketcall;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_syslog;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_ipc;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_quotactl;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_ppoll;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_rt_sigpending;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_getcwd;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_mmap2;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_getgroups;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_mincore;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_fcntl;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_fcntl64;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_lgetxattr;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_getxattr;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_fgetxattr;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_readlinkat;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_io_getevents;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_epoll_pwait;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_epoll_wait;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_get_mempolicy;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_mq_timedreceive;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

    sysnum.number = __NR_recvmmsg;
    if (drsys_filter_syscall(sysnum) != DRMF_SUCCESS)
        DR_ASSERT_MSG(false, "could not filter_ syscalls");

}

/********************************************************************************
 * Filter
 */

static bool tb_filter_syscalls(void *drcontext, int sysnum) {

    switch (sysnum) {

    case __NR_read:
    case __NR_getdents:
    case __NR_listxattr:
    case __NR_llistxattr:
    case __NR_flistxattr:
    case __NR_lookup_dcookie:
    case __NR_modify_ldt:
    case __NR_preadv:
    case __NR_readv:
    case __NR__sysctl:
    case __NR_stat:
    case __NR_fstat:
    case __NR_lstat:
    case __NR_statfs:
    case __NR_fstatfs:
    case __NR_socketcall:
    case __NR_syslog:
    case __NR_ipc:
    case __NR_quotactl:
    case __NR_ppoll:
    case __NR_poll:
    case __NR_rt_sigpending:
    case __NR_getcwd:
    case __NR_mmap2:
    case __NR_getgroups:
    case __NR_mincore:
    case __NR_fcntl:
    case __NR_fcntl64:
    case __NR_lgetxattr:
    case __NR_getxattr:
    case __NR_fgetxattr:
    case __NR_readlinkat:
    case __NR_io_getevents:
    case __NR_epoll_pwait:
    case __NR_epoll_wait:
    case __NR_get_mempolicy:
    case __NR_mq_timedreceive:
    case __NR_recvmmsg:
        return true;
    }

    return false;
}
