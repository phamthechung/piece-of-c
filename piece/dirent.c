/*
	Written Pham The Chung
	create 27/05/2010
	gcc -m64 -std=c99 -c dirent.c -Iinclude
	development status:
		has been test: opendir closedir readdir rewinddir direntry
	phamthechung0@gmail.com
*/

/*my dirent still depend on system malloc*/
#include <malloc.h>
#include <piece/kconnect.h>
#include <linux/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/fcntl.h>
#include <piece/dirent.h>
#include <piece/c_lang.h>
#ifdef __x86_32__
#error "this module can't compile in 32 bit mode"
#endif
/*
	getdent abstract functions to system call getdents64
*/

static long open_name(const char *name){
	int dfd=open(name,O_RDONLY,0);
	return dfd;
}
static inline long getdents64(int dfd,Dirent *entp,long size){
	asm volatile("syscall\n"::"a"(__NR_getdents64));
}
static struct dirent *listDir(long dfd,long *retsize){
	struct stat fod;
	struct dirent *dirp,*entp;
	if(fstat(dfd,&fod)) return (struct dirent *)NULL;
	if(dfd<0) return (struct dirent *)-1;
	int buf_size=fod.st_size+sizeof(Dirent);
	dirp=(struct dirent *)malloc(buf_size);      /*yes!I'm malloc*/
	long recsize=getdents64	(dfd,dirp,buf_size);
	if(recsize<0) return NULL;/*(Dirent *)recsize;*/
	*retsize=recsize;
	int byte=0;
	entp=dirp;
	char *pt=(char*)dirp;
	return (struct dirent *)dirp;
}

DIR *opendir(const char *dirname){
	int dfd=open(dirname,O_RDONLY,0);
	DIR *dirp;
	long syssize;
	dirp=(Dir*)malloc(sizeof(Dir));
	if(dirp==NULL) return NULL;
	dirp->dents=listDir(dfd,&syssize);
	if(dirp->dents<=0) return NULL;
	dirp->pos=(char*)dirp->dents;
	dirp->sizedir=syssize;
	dirp->next=0;
	dirp->check=0;
	dirp->dfd=dfd;
	return dirp;
}
/*	offer an fdopendir functions for convinience
	FIXME continue writting this functions
*/
DIR *fdopendir(int fd){
	DIR *dirp=(Dir*)malloc(sizeof(Dir));
	long syssize;
	if(dirp==NULL) return dirp;
	dirp->dents=listDir(fd,&syssize);
	if(dirp->dents<=0) return NULL;
	dirp->pos=(char*)dirp->dents;
	dirp->sizedir=syssize;
	dirp->next=0;
	dirp->check=0;
	dirp->dfd=fd;
	close(fd);
	return dirp;
}
/*
	yast ! It run good
*/
struct dirent *readdir(Dir *dp){
	struct dirent *entp,*idir;
	idir=dp->dents; /*init a pointer to frame*/
	if(dp->check==dp->sizedir) return NULL;
	dp->pos+=dp->next;
	entp=(Dirent *)dp->pos;
	dp->next=entp->d_reclen;
	dp->check+=dp->next;
	return (Dirent*)entp;
}
int closedir(DIR *dp){
	void *freethis=dp->dents;
	free(freethis);
	return close(dp->dfd);
}
void rewinddir(DIR *dp){
	Dir *dirp=dp;
	dirp->pos=(char*)dirp->dents;
	dirp->next=0;
	dirp->check=0;
}
int dirfd(Dir *dp){
	return dp->dfd;
}

/*
	understand the function
	return a pointer shape char** 
	vector of pointer to a malloc flat memory contain list of strings
*/

char **direntry(const char *dirname){
	Dir *dirp;
	Dirent *dent;
	dirp=opendir(dirname);
	int nitem=0,nbyte=0;
	if(dirp){
		while((dent=readdir,(dirp))){
			nitem++;
			nbyte+=strlen(dent->d_name);
		}
	}else return NULL;
	char *pt[nitem+1];
	pt[nitem]=NULL;
	int tnbyte=nbyte+nitem; // total number of  bytes in string
	void *field=malloc(tnbyte+1);
	if(!field) return NULL;
	char *buf=(char*)field;
	short len=0;
	rewinddir(dirp);
	int run=0;
	if(dirp)
	while((dent=readdir,(dirp))){
		strcpy(buf,dent->d_name);
		pt[run]=buf;
		len=1+strlen(dent->d_name);
		buf+=len;
		run++;
	}
	closedir(dirp);
	void *bufpt=malloc(sizeof (pt));
	void *retp=(void *)memcpy(bufpt,pt,sizeof pt);
	return (char**)retp;
}

long ndentry(const char *dirname){
	Dir *dirp;
	Dirent *dent;
	dirp=opendir(dirname);
	int entry=0,byte=0;
	if(dirp){
		while((dent=readdir(dirp))) entry++;
	}else return 0;
	closedir(dirp);
	return entry;
}

