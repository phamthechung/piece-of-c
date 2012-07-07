#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <piece/c_lang.h>
#define MAX_CHAR_COMMAND_LINE	4096
void error(const char *string){
	printf(string);
	exit(1);
}
void die(const char *string){
	printf(string);
	exit(1);
}	
char *readline(const char *prompt){
	int count=0,chung=0;
	char *pt=malloc(MAX_CHAR_COMMAND_LINE);
	char *hold=pt;
	printf(prompt);
	while(chung!='\n'){
		if(count==MAX_CHAR_COMMAND_LINE) {
			char *npt=malloc(MAX_CHAR_COMMAND_LINE*2);
			memcpy(npt,pt,count);
			pt=npt+count;
		}
		chung=getchar();
		count++;
		*pt=chung;
		pt++;
	}
	return hold;
}
#define MAX_FILE_SIZE	1024*1024
void *readFile(const char *name){
	struct stat fod;
	if(stat(name,&fod)) return NULL;
	if(fod.st_size>MAX_FILE_SIZE) return NULL;
	void *mm=malloc(fod.st_size+1);
	int fd=open(name,O_RDONLY,0);
	int rd=read(fd,mm,fod.st_size);
	char *pt=(char*)mm;
	*(pt+fod.st_size)=0;
	return mm;
}
#define TRUE	1
#define FALSE	0
#ifdef NULL
#undef NULL
#endif
#define NULL	(0)

MAIN
{
	//path=/home/chung file=chung.txt
	char *pt="echo $path/$file";
	char *n=strchr(pt,'$'),*m;
	while(*n){
		if(isgraph(*n)||isspace(*n)) return n;
		n++;
	}
	printf("%s",n);
}