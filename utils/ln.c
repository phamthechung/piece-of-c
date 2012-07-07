/*
	ln.c 2010 Pham The Chung
	LASTDATE Mon Feb 01 2010 10:11:09 AM ICT
*/
/* INCLUDE sector */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#define YES	1
#define NO	0
//#include <syscall.h>
/* end INCLUDE sector */
char buf[256];
/* INTERFACE to kernel */
long k_symlink(const char*from,const char*to){
	return symlink(from,to);
}
long k_link( char*from,char*to ){
	return link(from,to);
}
/* end of INTERFACE*/
static char help[]="Usage: ln [OPTION]... [-T] TARGET LINK_NAME   (1st form)\n\
  or:  ln [OPTION]... TARGET                  (2nd form)\n\
  or:  ln [OPTION]... TARGET... DIRECTORY     (3rd form)\n\
  or:  ln [OPTION]... -t DIRECTORY TARGET...  (4th form)\n\
  understand: ln [OPT] EXIST LINK_NAME \n\
In the 1st form, create a link to TARGET with the name LINK_NAME.\n\
In the 2nd form, create a link to TARGET in the current directory.\n\
In the 3rd and 4th forms, create links to each TARGET in DIRECTORY.\n\
Create hard links by default, symbolic links with --symbolic.\n\
When creating hard links, each TARGET must exist.\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
      --backup[=CONTROL]      make a backup of each existing destination file\n\
  -b                          like --backup but does not accept an argument\n\
  -d, -F, --directory         allow the superuser to attempt to hard link\n\
                                directories (note: will probably fail due to\n\
                                system restrictions, even for the superuser)\n\
  -f, --force                 remove existing destination files\n\
  -n, --no-dereference        treat destination that is a symlink to a\n\
                                directory as if it were a normal file\n\
  -i, --interactive           prompt whether to remove destinations\n\
  -s, --symbolic              make symbolic links instead of hard links\n\
  -S, --suffix=SUFFIX         override the usual backup suffix\n\
  -t, --target-directory=DIRECTORY  specify the DIRECTORY in which to create\n\
                                the links\n\
  -T, --no-target-directory   treat LINK_NAME as a normal file\n\
  -v, --verbose               print name of each linked file\n\
      --help     display this help and exit\n\
      --version  output version information and exit\n\
\n\
The backup suffix is `~', unless set with --suffix .\n\
The version control method may be selected via the --backup option or through\n";
char version[]="ln version 0.1\nWritten by Pham The Chung.\n\
					Contact pham.the.chung0@gmail.com\n";
char nofile[]="ln: Missing file argument.\nTry ln --help .\n";
char option[]="bdFfnisStTv";

error_exit(const char*to,int status){ 
	printf("%s\n",to);
	exit(status);
}
int main( int argc,char**argv )
{
	if(argc<2) error_exit(nofile,1);
	int ch=0;
	char fact=0,*suffixvalue="~";
	unsigned char backup=NO,v=NO,s=NO,i=NO,f=NO,T=NO,b=NO,S=NO,t=NO;
	while((ch =getopt(argc,argv,option)!=-1)){
		switch(ch) {
		  case 'v':v=YES;
			   printf("%c ",ch);break;
		  case '?': printf("unknown option");break;
		}
	}
	printf("%d\n",v);
}

