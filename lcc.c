#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include "lcc.h"
//
die(const char *s){
	puts(s);
	exit(1);
}
char *arg(int argc,char **argv){
	int ch=0;
	if(argc<2) die("lcc:no input file");
	while((ch=getopt(argc,argv,option))!=-1){
		switch(ch){
			case 'v':printf(version);break;
			case 'h':printf(help);break;
			default:printf("not implement\n");
		}
	}
	return argv[1];
}
File *readfile(const char *name){
	File *file=(File*)malloc(sizeof(File)+MAX_FILE_SIZE+1);
	file->name=name;
	int fd=open(name,O_RDONLY,0);
	if(fd<0) return NULL;
	struct stat fod;
	if(fstat(fd,&fod)) return NULL;
	file->size=fod.st_size;
	file->mode=fod.st_mode;
	if(file->size<=MAX_FILE_SIZE) read(fd,file->data,file->size);
	if(file->size>MAX_FILE_SIZE) return NULL;
	file->data[MAX_FILE_SIZE]=0;
	return file;
}
int is_id(char ch){
	if(isalpha(ch)||ch=='_') return 1;
	else return 0;
}
//check m is keyword or not
int is_keyword(char *m){
	int tf=0,r=0;
	while(keyword[r]!=NULL){
		if(!strcmp(keyword[r],m)) return 1;
		r++;
	}
	return 0;
}
int id_size(char *m){
	int c=0;
	while(*m!=NULL){
		if(is_id(*m)) c++;
		else break;
		m++;
	}
	return c;
}
// give address of next id
int next_is_id(char*m){
	while(isspace(*m)) m++;
	while(ispunct(*m)) m++;
	if(is_id(*m)) return 1;
	else return 0;
}
// count how many implementation function in C
int count_function(File*f){
	char *m=f->data;
	char next=0,true_form=0,ignore=0;
	int fun=0;
	while(*m!=NULL){
		if(isspace(*m)) m++;
		if(is_id(*m)&&next==0 ) {
			if(!is_keyword(m)){ 
				true_form++;
				m=id_size(m)+1;
			}else{
				if(next_is_id(m))ignore=0;
				else ignore=1;
			}
		}
		if(*m=='(') next++;
		if(*m==')') next++;
		if(*m==';') next=0;
		if(*m=='{') next++;
		if(*m=='}') next++;
		if(true_form==1&&next==4&&ignore==0)
		{fun++;next=0;true_form=0;ignore=0;}
		m++;
	}
	return fun;
}
int main(int argc,char **argv){
	char *file=arg(argc,argv);
	File *fp=readfile(file);
	printf("%d",count_function(fp));
	//printf("%d",isspace('*'));
}