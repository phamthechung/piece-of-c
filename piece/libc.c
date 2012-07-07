#include <stdio.h>
#include <string.h>
char *size_toa(size_t a){
	char *str=(char*)malloc(100);
	char *end=str+99;
	*end--=NULL;
	char ch=0;
	size_t r=0,quo=a;
	do{
		ch=quo%10+0x30;
		quo/=10;
		*end--=ch;
		r++;
	}while(quo);
	return ++end;
}
char **str2array(const char *word,char sep){
  if(word==NULL) return NULL;
  while(*word==sep) word++;
  char *path=word;
  size_t len=strlen(path);
  size_t frag=0,r=0,count=0,msize;
  char **vpath;
  /*first count how many*/
  while(*path)	if(*path++==sep) frag++;
  vpath=(char **)malloc( (frag+2)*sizeof(char*)+len+frag );
  path=word;
  vpath[r]=vpath+frag+2;
  while(*path){
	*(vpath[r]+count++)=*path++;
	if(*path==sep) {
	  *(vpath[r]+count)=NULL;
	  vpath[r+1]=vpath[r]+count+1;
	  count=0,path++,r++;
	}
  }
  vpath[r+1]=NULL;
  return vpath;
}
