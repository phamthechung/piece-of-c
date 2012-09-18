#ifndef _c_lang_h
#define _c_lang_h

#ifdef i386
#define __x86_32__
#else
#define __x86_64__
#endif
#if 0
#ifdef __x86_32__
typedef unsigned int size_t;
typedef signed int ssize_t;
#endif
#ifdef __x86_64__
typedef unsigned long size_t;
typedef signed long ssize_t;
#endif
#endif
#define _STR(x)	#x
#define STR(x)	_STR(x)

#define MAIN	int main(int argc,char **argv)
#define ARG	(int argc,char **argv)
#define PASS	(argc,argv)
#define TRUE	1
#define FALSE	0
#endif
