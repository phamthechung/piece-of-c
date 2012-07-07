/*
 *	Written by Pham The Chung
 *	create June 27 2010
 *
 * */
#include <stdio.h>
#include <sys/mount.h>
char *usage="mount /dev/xxx dir\n";
char *version="mount version 0.1\
mount is part of piece-of-c\n\
written by Pham The Chung";
int checkarg ARG{

}
int main(int argc,char**argv ){
	if(getuid()!=0) {
	  puts("Only root can mount\n");
	  exit(1);
	}
	checkarg PASS
}

