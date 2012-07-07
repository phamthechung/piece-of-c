#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <piece/piece_code.h>
#include <piece/getopt.h>
char *opt="vh";
char strversion[]="pr version 0.1\n";
char help[]="pr is process expression\n";
typedef double (*mfun)(double);
typedef struct {
  char *name;
  mfun act;
}funr;

version(){
	puts(strversion);
	exit(0);
}
usage(){
	puts(help);
	exit (0);
}
error(char *v){
  puts(v);
  exit(1);
}
int inList(const char *key,const char **list){
	int r=0;
	while(list[r]!=NULL){
	  if(!_PC(strcmp,(list[r],key)))
		return r;
	  r++;
	}
	return -1;
}
int option(int c,char **v){
  if(c<2) error("no argument");
  int ch;
  while((ch=_PC(getopt,(c,v,opt)))){
	switch(ch){
	  case 'v':
		  version();break;
	  case 'h': usage();break;
	  default: continue;
	}
  }
}
seek(char **s){
  char *v=*s;
  while(isspace(*v)) v++;
  *s=v;
}

char isnum(char c){
  if((c>=0x30&&c<=0x39)|| c==0x2e)
	  return 1;
  return 0;
}
char idf(char c){
  if((c>=0x41&&c<=0x5a)||c==0x5f)
	  return 1;
  return 0;
}
char isa1(char c){
  if((c>=0x41&&c<=0x5a)||(c>=0x61&&c<=0x7a)||(c>=0x30&&c<=0x39))
	  return 1;
  return 0;
}
char isop(char c){
  if((c>=0x21&&c<=0x2f)||0x3a)
	  return 1;
  return 0;
}
double gnum(char **a){
  char buf[50];
  int r=0;
  char *v=*a;
  while(isnum(*v)){
	buf[r++]=*v;
	v++;
  }
  *a=v;
  buf[r]=0;
  double n=strtod(buf,0);
  return n;
}
/*==============*/
funr farr[]={
	{"sqrt",sqrt},
	{"cbrt",cbrt},
	{"log1p",log1p},
	{"log",log},
	{"log10",log10},
	{"sin",sin},
	{"cos",cos},
	{"tan",tan},
	{0,exit}
	};
char ismf(char *a){
  int r=0;
  while(1){
    if(!_PC(strcmp,(farr[r].name,a)))
	    return r;
    r++;
  }
  return -1;
}
double gfun(char **a){
  char *v=*a;
  char buf[64];
  int r=0;
  double ret=0;
  while(isa1(*v)){
	buf[r++]=*v;
	v++;
  }
  buf[r]=0;
  *a=v;
  if(ismf(buf)==-1) error("unknown function\n");
  seek(&v);
  if(*v=='(') {
	seek(&v);
	return farr[ismf(buf)].act(gnum(&v));
  }
  else error("not proper function\n");
  return ret;
}
double gop(char **a){
  char *v=*a;
  if(isnum(*v))
	  return gnum(a);
  else
	  return gfun(a);
  return 0.0;
}

int expr(char *v){
  int run=0;
  char p=0;
  double pair[2];
  while(*v){
    switch(*v){
	case '0' ... '9':
	{
	  pair[0]=gnum(&v);
	  p=(p==0?1:1);
	  break;
	}
	case '+': 
	{
	  v++;seek(&v);
	  pair[0]+=gop(&v);
	  break;
	}
	case '-': v++;seek(&v);
		  pair[0]-=gop(&v);
		  break;
	case '*': v++;seek(&v);
		  pair[0]*=gop(&v);
		  break;
	case '/': v++;seek(&v);
		  pair[0]/=gop(&v);
		  break;
	case '^':v++;seek(&v);
		 pair[0]=pow(pair[0],gop(&v));
		 break;
	case 'a' ... 'z':
		p=(p==0?1:1);
		pair[0]=gfun(&v);
		break;
	default:v++;break;
    }
  }
out:
  printf("%g\n",pair[0]);
}
int expre(char *v){
   int r=0;
   char t=0,e=0;
   double fp[2];
   long ip[2];
   char *p=v;
   /*
   while(*p){
       switch(*p){
            case '+': p++;t++;break;
	        case '-': p++;t++;break;
	        case '*': p++;t++;e++;break;
	        case '/': p++;t++;e++;
		          break;
		    default: printf("val %g\n",gop(&p));
		        
		}
   }*/
   printf("val %g %c\n",gop(&p),*p);
   printf("oper %d,pre %d \n",t,e);
}
void inc(char **a){
  char *v=*a;
  v++;
  *a=v;
}
int main(int argc,char **argv){
  option(argc,argv); 
  //expre(argv[1]);
  char *p=argv[1];
  printf("%f %s\n",gnum(&p),p);
}

