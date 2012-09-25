/*
	written by Pham The Chung
	create 1/3/2010
	phamthechung0@gmail.com
*/
#ifndef PIECE_DIRENT_H
#define PIECE_DIRENT_H
/*
	like linux_dirent64
*/
typedef struct dirent{
	unsigned long	d_ino;
	long		d_off;
	unsigned short	d_reclen;
	unsigned char	d_type;
	char		d_name[0];
}Dirent;
typedef struct DIR{
	int dfd;
	Dirent *dents;
	long sizedir;
	char *pos; /*pos pointer*/
	long next;
	long check; /*check whether it reach sizedir*/
}DIR;
//typedef Dir DIR;
/*
	Dir *dp=piece_opendir("/");
	Dirent *entp;
	while((entp=piece_readdir(dp))!=NULL)
		printf("%s \n",entp->d_name);
*/
extern DIR *opendir(const char *dirname);
extern DIR *fdopendir(int dfd);
extern struct dirent *readdir(DIR *dp);
extern int closedir(DIR *dp);
extern void rewinddir(DIR *dp);

/*
 * list name of entry in dirname
 * char **array = direntry(/);
 * while(array
 * */
extern char **direntry(const char *dirname);

#endif
