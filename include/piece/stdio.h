#ifndef STDIO_H
#define STDIO_H

	#define __need_size_t
	#define __need_NULL
	#include <stddef.h>
	#define	EOF	(-1)
	#define SEEK_SET 0
	#define SEEK_CUR 1
	#define SEEK_END 2
#define FRAME_SIZE	4096
typedef struct _iofile{
	const char *name;
	int fd;
	long size;
	char mode;
	long offset;
	long pos;
	void *frame;
}FILE;
#endif
FILE *fopen(const char *file,const char *mode);
int fclose(FILE *fd);
int fread(void*m,size_t,size_t,FILE*);
int fwrite(void *m,sizet,size_t,FILE*);