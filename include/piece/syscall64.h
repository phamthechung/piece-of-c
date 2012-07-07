/*
	Written by Pham The Chung
	create 27/5/2010
	last   27/6/2010
*/
#ifndef SYSCALL64_H
#define SYSCALL64_H
#include <linux/stat.h>
#include <linux/dirent.h>
#include <linux/mount.h>
#include <linux/socket.h>
#include <linux/time.h>
#include <linux/signal.h>
#include <linux/poll.h>
#include <linux/fcntl.h>
#include <piece/code_macro.h>

/**/
#define __PSYS(name) PROTOSYS(long,name)
/**/
extern void __exit_(int status);
extern __PSYS(open)(const char *name,int o_flag,int cmod);
extern __PSYS(close)(int fd);
extern __PSYS(read)(unsigned fd,void *buf,long count);
extern __PSYS(write)(unsigned fd,void *buf,long count);
extern __PSYS(fstat)(unsigned fd,struct stat *buf);
extern __PSYS(stat)(const char *name,struct stat *buf);
extern __PSYS(chdir)(const char *dir);
extern __PSYS(fchdir) (int fd);
extern __PSYS(fchown)(unsigned int fd, uid_t user, gid_t group);
extern __PSYS(getcwd) (char *buf,int size);
extern __PSYS(chmod)(const char *filename, mode_t _mode);
extern __PSYS(fchmod)(unsigned int fd, mode_t _mode);
extern __PSYS(access)(const char *filename, int _mode);
extern __PSYS(mknod)(const char *filename, int _mode, unsigned dev);
extern __PSYS(mkdir)(const char *pathname, int __mode);
extern __PSYS(rename)(const char *oldname, const char *newname);
extern __PSYS(rmdir)(const char *pathname);
extern __PSYS(unlink)(const char *pathname);
extern __PSYS(link)(const char *oldname, const char *newname);
extern __PSYS(symlink)( const char *oldname,const char __user *newname);
extern __PSYS(chroot)(const char *filename);
extern __PSYS(dup)(unsigned int fildes);
extern __PSYS(sync)(void);
extern __PSYS(truncate)(const char __user *path, long length);
extern __PSYS(ftruncate)(unsigned int fd, unsigned long length);
extern __PSYS(pipe)(int __user *fildes);
extern __PSYS(readv)(unsigned long fd, const struct iovec __user * vec,
		unsigned long vlen);
extern __PSYS(writev)
	(unsigned long fd, const struct iovec __user *vec,unsigned long vlen);
extern __PSYS(getdents64)
      (unsigned fd,struct linux_dirent64 *buf,unsigned sz);
extern __PSYS(mount)
      (const char *dev,const char *dir,char *type,long flag,void *data);
extern __PSYS(umount2)(const char *dir,int flag);
extern __PSYS(umask)(int mask);
extern __PSYS(flock)(unsigned int fd, unsigned int cmd);
extern __PSYS(mlock)(unsigned long start, size_t len);
extern __PSYS(munlock)(unsigned long start, size_t len);
extern __PSYS(mprotect)(unsigned long start, size_t len,unsigned long prot);
extern __PSYS(getuid)(void);
extern __PSYS(getgid)(void);
extern __PSYS(geteuid)(void);
extern __PSYS(getgid)(void);
extern __PSYS(getegid)(void);
extern __PSYS(gettid)(void);
/*time*/
extern __PSYS(gettimeofday)(struct timeval __user *tv,
							struct timezone __user * tz);
extern __PSYS(settimeofday)(struct timeval __user * tv,
		struct timezone __user * tz);
/*proccess*/
extern __PSYS(getpid)(void);
extern __PSYS(getppid)(void);
extern __PSYS(brk)(unsigned long brk);
extern __PSYS(mincore)(unsigned long start, size_t len,unsigned char * vec);
extern __PSYS(mmap)(unsigned long addr, unsigned long len,
		unsigned long prot, unsigned long flags,
		unsigned long fd, unsigned long off);
extern __PSYS(munmap)(unsigned long addr, size_t len);
extern __PSYS(ioctl)(unsigned fd, unsigned  cmd, unsigned long arg);
extern __PSYS(fcntl)(unsigned fd, unsigned cmd,unsigned long arg);

extern __PSYS(select)
		(int n, fd_set *inp, fd_set *outp,
		fd_set *exp, struct timeval *tvp);
extern __PSYS(poll)(struct pollfd *ufds, unsigned int nfds,long timeout_msecs);
extern __PSYS(times)(struct tm *tbuf);
/*signal syscall*/
extern __PSYS(rt_sigaction)
	(int sig,
	const struct sigaction *act,struct sigaction *oact,size_t sigsetsize);
extern __PSYS(rt_sigprocmask)
	(int how, sigset_t *set,sigset_t * oset, size_t sigsetsize);
extern __PSYS(rt_sigpending)(sigset_t * set, size_t sigsetsize);
extern __PSYS(rt_sigtimedwait)(const sigset_t * uthese,
		siginfo_t *uinfo, const struct timespec * uts,size_t sigsetsize);
extern __PSYS(rt_sigqueueinfo)(pid_t pid, int sig,siginfo_t *uinfo);
/*socket*/
/*
	open a socket, return a fd of socket like a file
*/
extern __PSYS(socket)(int family,int type,int protocol);
extern __PSYS(socketpair)(int family, int type, int protocol,
		int __user * usockvec);
extern __PSYS(bind)(int fd, struct sockaddr * umyaddr, int addrlen);
extern __PSYS(listen)(int fd, int backlog);
extern __PSYS(accept4)
(int fd, struct sockaddr * upeer_sockaddr,int *upeer_addrlen, int flags);
extern __PSYS(connect)(int fd, struct sockaddr *uservaddr,int addrlen);
extern __PSYS(getsockname)(int fd, struct sockaddr __user * usockaddr,
		int __user * usockaddr_len);
extern __PSYS(getsockopt)(int fd, int level, int optname,
		char __user *optval, int __user *optlen);
extern __PSYS(setsockopt)(int fd, int level, int optname,
		char __user *optval, int optlen);
extern __PSYS(socketcall)(int call, unsigned long __user *args);
extern __PSYS(sendto)(int fd, void *buff, size_t len,
		unsigned flags, struct sockaddr * addr,
		int addr_len);
extern __PSYS(send)(int fd, void *buff, size_t len,unsigned flags);
extern __PSYS(recvfrom)(int fd, void * ubuf, size_t size,
		unsigned flags, struct sockaddr *addr,int * addr_len);
		
extern __PSYS(shutdown)(int fd, int how);
extern __PSYS(fsync)( unsigned fd);
/*syscall_at*/
extern __PSYS(openat)(int dfd, const char * filename, int flags,int _mode);
extern __PSYS(fchownat)(int dfd, const char *filename, uid_t user,
						gid_t group,int flag);
extern __PSYS(fchmodat)(int dfd, const char *filename, mode_t _mode);
extern __PSYS(linkat)
		(int olddfd, const char *oldname,
		int newdfd, const char *newname, int flags);
extern __PSYS(unlinkat)( int dfd, const char *pathname, int flag);
extern __PSYS(mkdirat)(int dfd, const char *pathname, int _mode);
extern __PSYS(renameat)
		(int olddfd, const char __user *oldname,
		int newdfd, const char __user *newname);
extern __PSYS(symlinkat)(const char *oldname,int newdfd, const char *newname);
extern __PSYS(mknodat)(int dfd, const char *filename, int _mode,unsigned dev);
extern __PSYS(faccessat)(int dfd, const char __user * filename, int _mod);
extern __PSYS(execve)(const char *file,char **argv,char **anvp);
#endif
