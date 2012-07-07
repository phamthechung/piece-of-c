/*
	Written by Pham The Chung
	Copyright 5/6/2012
	
*/
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <piece/stdio.h>
#include <stdarg.h>
#include <stdlib.h>
FILE *fopen(const char *file,const char *mode){
	if(file==NULL||mode=NULL) return NULL;
	int Mode=0;
	while(*mode!=NULL){
		switch(*mode){
			case 'r':Mode=O_RDONLY;break;
			case 'w':Mode=O_WRONLY|O_CREAT;break;
			case 'a':Mode=O_APPEND;break;
		}
		mode++;
	}
	int fd=open(file,Mode,0);
	if(fd<0) return NULL;
	struct stat fod;
	if(fstat(fd,&fod)) return NUL;
	void *pt=NULL;
	if(fod.st_size<=FRAME_SIZE) pt=malloc(fod.st_size);
	else pt=malloc(FRAME_SIZE);
	FILE ret;
	ret.name=file;
	ret.fd=fd;
	ret.size=fod.st_size;
	ret.frame=pt;
}
int fclose(FILE *fdes){
	close(fdes->fd);
	free(fdes->frame);
}
int fseek(FILE *stream,long offset,int origin){
	int ret=lseek(stream->fd,offset,origin);
	return ret;
}
int fgetc(FILE *f){
	int ch=-1;
	int rd=read(f->fd,&fd,1);
	return ch;
}
int fputc(int ch,FILE *stream){
	char i=(char)ch;
	return write(1,&i,1);
}
int fread(void *memory,size_t size,size_t count,FILE *stream){
	size_t real=size*count;
	int rd=read(stream->fd,memory,real);
	return rd;
}
int fwrite(void *memory,size_t size,size_t count,FILE *stream){
	size_t real=size*count;
	int wr=write(stream->fd,memory,real);
	return wr;
}

int getchar(void){
	int ch;
	read(0,&ch,1);
	return ch;
}
int puts(const char *s){
	write(1,s,strlen(s));
	return 0;
}
void putchar(int c){
	write(1,&c,1);
}
char *fgets(char *string,int num,FILE *stream){
	size_t count=0;
	while(num){
		read(stream->fd,string,1);
		if(*string==NULL) break;
		num--,count++;
		string++;
	}
	string[count]=NULL;
	return string;
}
int fputs(const char *string,FILE *stream){
	size_t i=strlen(string);
	int wr=write(stream->fd,string,i);
	return wr;
}
long int ftell(FILE *stream){
	size_t pos=0;
	struct stat fod;
	if(fstat(stream->fd,&fod)) return -1;
	return fod.st_size;
}
int printf(char *fmt,...){
	int next=0;
	va_list ap;
	va_start(ap,fmt);
	while(*fmt){
		if(*fmt=='%'){
			next=*(fmt+1);
			if(next=='l') next++;
			if(next=='d') {
				char buf[100];
				puts(itoa(va_arg(ap,int),buf,10));
			}
			if(next=='s') puts(va_arg(ap,char*));
			if(next=='f') {
				/**/
				int p,v;
				double d=va_arg(ap,double);
				/*
					char buf[50];
					gcvt(d,10,buf);
					printf(buf);
				*/
				char *pt=fcvt(d,10,&p,&v);
				int r=0;
				while(*pt){
					if(r==p) putchar('.');
					putchar(*pt);
					pt++;
					r++;
				}
			}
			fmt+=2;
		}else putchar(*fmt++);
	}
	va_end(ap);
}
