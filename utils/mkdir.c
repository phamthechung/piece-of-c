/*
 *	Written by Pham The Chung
 *	create June 23 2010
 *	mkdir.c
 */
#ifdef STD_CALL
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
#else
	#include <piece/piece_stdio.h>
	#include <piece/piece_string.h>
	#include <piece/stdlib.h>
#endif
#include <piece/piece_code.h>
#include <piece/call_macro.h>
/*Incomplete code
	convert string octal format to integer
	0755
	bit stream convert
	
*/
#ifdef INCOMPLETE
// set s to o at t
#define SETOC(o,s,t) (o^(s<<t))
int a2oc(const char *a){
	short r=0;
	char ch=0;
	if(a){
	  while(a[r]){
	    ch=a[r]-0x30;
	    r++;
	  }
	}
}
#endif
int main(int argc,char **argv){
	int ret=0;
		
	return ret;
}

