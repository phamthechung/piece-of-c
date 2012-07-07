/*
	written by phamthechung0@gmail.com
*/
#ifndef __KERNEL_H
#define __KERNEL_H
#ifdef i386
#define __x86_32__
#else if
#define __x86_64__
#endif

#ifndef __x86_32__
	#ifndef __x86_64__
	#error "must define spec x86 arch"
	#endif
#endif
#ifdef	__x86_32__
	#ifdef __x86_64__
	#error	"cant define both x86 32 or 64 simultanously"
	#endif
#endif

#ifdef __GET_KERNEL_H_VERSION
#define __KERNEL_VERSION	1
#endif

#ifdef __BASE_TYPES
typedef unsigned char	__u8;
typedef unsigned short	__u16;
typedef unsigned int	__u32;
typedef signed char		__s8;
typedef signed short	__s16;
typedef signed int		__s32;
#ifdef __x86_64__
typedef	unsigned long	__u64;
typedef signed long		__s64;
#endif
#endif /*end of __BASE_TYPES*/

#ifdef	__KERNEL_TYPES
typedef __u32	__kernel_mode_t;
typedef	__s32	__kernel_pid_t;
typedef __s32	__kernel_ipc_pid_t;
typedef __u32	__kernel_uid_t;
typedef __u32	__kernel_gid_t;
typedef __s32	__kernel_timer_t;
typedef __s32	__kernel_clockid_t;
typedef __s32	__kernel_daddr_t;
typedef __u8 *	__kernel_caddr_t;

#ifdef	__x86_32__
typedef __u32	__kernel_ino_t;
typedef __s32	__kernel_time_t;
typedef __s32	__kernel_off_t;
typedef __u32	__kernel_size_t;
typedef __s32	__kernel_ssize_t;
#endif

#ifdef __x86_64__
typedef	__u64	__kernel_ino_t;
typedef __s64	__kernel_time_t;
typedef __s64	__kernel_off_t;
typedef __u64	__kernel_size_t;
typedef	__s64	__kernel_ssize_t;
typedef	__s64	__kernel_ptrdiff_t;
typedef __s64	__suseconds_t;
typedef __s64	__kernel_clock_t;

#endif
#ifdef __KERNEL__
#define __NFDBITS	(8* sizeof(unsigned long))
#define __FD_SETSIZE	1024
#define __FDSET_LONGS	(__FD_SETSIZE/__NFDBITS)
typedef struct {
	unsigned long fds_bits[__FDSET_LONGS];
}__kernel_fd_set;

typedef	__kernel_fd_set	fd_set;
typedef void (*__kernel_sighandler_t)(int);
#endif

#ifdef __GNUC__
typedef long long __kernel_loff_t;
#endif
typedef struct {
        int     val[2];
} __kernel_fsid_t;

#endif /*kernel types*/
#ifdef __KERNEL_DIRENT
#ifdef __x86_64__
struct dirent{
	__u64	d_ino;
	__s64	d_off;
	__u16	d_reclen;
	__u8	d_type;
	__u8	d_name[0];
};
#endif

#endif /*KERNEL_DIRENT*/

#endif
