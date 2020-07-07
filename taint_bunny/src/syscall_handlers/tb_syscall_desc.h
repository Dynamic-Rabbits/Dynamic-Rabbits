/*
 * tb_syscall_desc.h
 *
 *  Created on: 17 Sep 2018
 *      Author: john
 */

#ifndef TAINT_ENGINES_SYSCALL_HANDLERS_TB_SYSCALL_DESC_H_
#define TAINT_ENGINES_SYSCALL_HANDLERS_TB_SYSCALL_DESC_H_


/*-
 * Copyright (c) 2010, 2011, 2012, 2013, Columbia University
 * All rights reserved.
 *
 * This software was developed by Vasileios P. Kemerlis <vpk@cs.columbia.edu>
 * at Columbia University, New York, NY, USA, in June 2010.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Columbia University nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/timex.h>
#include <sys/types.h>
#include <sys/vfs.h>
#include <sys/vm86.h>
#include <asm/ldt.h>
#include <asm/posix_types.h>
#include <linux/aio_abi.h>
#include <linux/futex.h>
#include <linux/mqueue.h>
#include <linux/utsname.h>
#include <numaif.h> // requires installation of libnuma
#include <signal.h>
#include <ustat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define IPC_INFO	3

#define SEMCTL	3
#define MSGRCV	12
#define MSGCTL	14
#define SHMCTL	24

#define IPC_FIX	256

union semun {
	int		val;
	struct semid_ds	*buf;
	unsigned short	*array;
	struct seminfo	*__buf;
};

#define XQM_CMD(x)	(('X'<<8)+(x))
#define Q_XGETQUOTA     XQM_CMD(3)
#define Q_XGETQSTAT     XQM_CMD(5)

typedef struct fs_qfilestat {
	__u64 qfs_ino;
	__u64 qfs_nblks;
	__u32 qfs_nextents;
} fs_qfilestat_t;

struct fs_quota_stat {
	__s8		qs_version;
	__u16		qs_flag;
	__s8		qs_pad;
	fs_qfilestat_t	qs_uquota;
	fs_qfilestat_t	qs_gquota;
	__u32		qs_incoredqs;
	__s32		qs_btimelimit;
	__s32		qs_itimelimit;
	__s32		qs_rtbtimelimit;
	__u16		qs_bwarnlimit;
	__u16		qs_iwarnlimit;
};

struct fs_disk_quota {
	__s8	d_version;
	__s8	d_flags;
	__u16	d_fieldmask;
	__u32	d_id;
	__u64	d_blk_hardlimit;
	__u64	d_blk_softlimit;
	__u64	d_ino_hardlimit;
	__u64	d_ino_softlimit;
	__u64	d_bcount;
	__u64	d_icount;
	__s32	d_itimer;
	__s32	d_btimer;
	__u16	d_iwarns;
	__u16	d_bwarns;
	__s32	d_padding2;
	__u64	d_rtb_hardlimit;
	__u64	d_rtb_softlimit;
	__u64	d_rtbcount;
	__s32	d_rtbtimer;
	__u16	d_rtbwarns;
	__s16	d_padding3;
	char	d_padding4[8];
};

struct mmsghdr
  {
    struct msghdr msg_hdr;	/* Actual message header.  */
    unsigned int msg_len;	/* Number of received or sent bytes for the
				   entry.  */
  };

#include <linux/net.h>
#include <string.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <asm/unistd.h>
#include <sys/stat.h>
#include <sys/vfs.h>
#include <sys/epoll.h>
#include <sys/ipc.h>
#include <poll.h>
#include <sys/mman.h>
#include <linux/aio_abi.h>         /* Defines needed types */
#include <linux/sysctl.h>
#include <sys/quota.h>
#include <sys/types.h>

#endif /* TAINT_ENGINES_SYSCALL_HANDLERS_TB_SYSCALL_DESC_H_ */
