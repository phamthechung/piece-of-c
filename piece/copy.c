/*
 * written by phamthechung0@gmail.com
 * Copyright 12/11/2011
 */
#include <stdio.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <dirent.h>
/*
	copy file
	path/to/src to /path/to/dst
*/
int copy(const char *src,const char *dst){
	#define CP_SIZE	4096
	char buf[CP_SIZE];
	struct stat fod,fod2;
	char exist=1;
	if(stat(src,&fod)) return -1;
	if(stat(src,&fod2)) exist=0;
	int frag=0,od=0;
	frag=fod.st_size/CP_SIZE;
	od=fod.st_size%CP_SIZE;
	int fdsrc=open(src,O_RDONLY,0);
	int fddst=0;
	if(exist) fddst=open(dst,O_RDWR,0);
	else fddst=open(dst,O_RDWR|O_CREAT,0750);
	while(frag){
		int slice=1;
		read(fdsrc,buf,CP_SIZE);
		write(fddst,buf,CP_SIZE);
		lseek(fdsrc,CP_SIZE*slice,0);
		lseek(fddst,CP_SIZE*slice,0);
		slice++,frag--;
	}
	if(od){
		read(fdsrc,buf,od);
		write(fddst,buf,od);
	}
	close(fdsrc);close(fddst);
	return 0;
	#undef CP_SIZE
}
/*
	
*/
int copydir(const char *src,const char *dst){
	int fd1=open(src,O_RDONLY,0);
	struct stat fod1,fod2;
	if(stat(src,&fod1)) return -1;
	if(stat(dst,&fod2)) {mkdir(dst);}
	int fd=open(src,O_RDONLY,0);
	DIR *dirp=opendir(src);
	struct dirent *dirent;
	while((dirent=readdir(dirp))!=NULL)
	{
		
	}
}
