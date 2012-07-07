/*
	convention of register for piece
*/
#ifndef PIECE_CONVENTION_H
#define PIECE_CONVENTION_H
#include <piece/config.h>
/*
	default is 64 bit if not define __x86_32__
*/
#ifdef __x86_32__
	#define SIZEOF_LONG 4
#else
	#define SIZEOF_LONG 8
#endif

/*calling convention define for register*/
	#if SIZEOF_LONG == 4 
		#define ar0 "(%eax)"
		#define r0 "%eax"
		#define r1 "%ecx"
		#define r2 "%ecx"
		#define r3 "%ebx"
	#else 
		#if SIZEOF_LONG == 8
		#define ar0 "(%rax)"
		#define r0 "%rax"
		#define r1 "%rdi"
		#define r2 "%rsi"
		#define r3 "%rdx"
		#define r4 "%rcx"
		#define r5 "%r8"
		#define r6 "%r9"
		#else
		#error "I dont know, what kind if this machine"
		#endif
	#endif

#endif 
