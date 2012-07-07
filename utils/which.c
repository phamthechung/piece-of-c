#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
char **str2array(const char *word,char sep){
  if(word==NULL) return NULL;
  while(*word==sep) word++;
  char *path=word;
  size_t len=strlen(path);
  size_t frag=0,r=0,count=0,msize;
  char **vpath;
  /*first count how many*/
  while(*path)	if(*path++==sep) frag++;
  vpath=(char **)malloc( (frag+2)*sizeof(char*)+len+1 );
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
char *which(const char *word){
  char **vpath=str2array(getenv("PATH"),':');
  char buf[266],*rpt=0;
  size_t r=0;
  while(vpath[r]){
	strcpy(buf,vpath[r]);strcat(buf,"/");
	strcat(buf,word);
	if(access(buf,F_OK)==0) {
	  rpt=(char *)malloc(strlen(buf));
	  if(rpt)  strcpy(rpt,buf);
	  return rpt;
	}
	r++;
  }
  free((void *)vpath);
  return NULL;
}

int main(int argc,char **argv){
	if(argc<2) exit(1);
	char * where = which(argv[1]);
	if(where)
	printf("%s\n",where);
	else exit(1);
}
