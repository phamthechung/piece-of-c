/*
	Written by Pham The Chung
	cp command do copy file or directory
	create June 27 2010
*/
/*
	compile command
	gcc cp.c stdio.o -I../include ../syscall_def.o string2.o stdlib.o iofile.o dirent.o
	CALL to call host library
	_PC to call piece_of_c library
*/

#include <piece/piece_stdio.h>
#include <piece/piece_code.h>
#include <piece/iofile.h>
#include <piece/syscall64.h>
#include <piece/piecetype.h>
char *usage="cp usage\n\
  cp [OPTION] src  dst\n\
  cp [OPTION] src ...  directory\n\
  copy source to destination or multiple source to directory\n\
\tlist of option :\n\
\t  --version	show version of this program\n\
\t  --usage     show usage \n\
\t  -v --verbose          show what happening\n\
\t  -r --recursive        copy recursive\n\
\t  -i --interactive      ask if exist destination\n \
\t  -f --force            don't ask replace the exist file\n\
\t  -L --dereference      follow link in source\n\
\t  -t --target-directory copy all source to directory\n\
\t  -p --preserve         preserve mode,owner,timestamp\n\
not implement long option now\n";

char *susage="cp [OPTION] src  dst\n\
cp [OPTION] src ...  directory\n\
copy source to destination or multiple source to directory\n\
use --usage option to see more\n";

char *version="cp version 0.1 test\n\
cp is part of piece-of-c project\n\
Written by pham.the.chung0@gmail.com\n";

#define OK    (0)
ver(){
    puts(version);
    exit(0);
}
help(){
  puts(usage);
  exit (0);
}
error(char *v){
  puts(v);
  exit(1);
}
int arg(int c,char **v){
  switch(c) {
	case 1:
	puts(susage);
	_PC(exit,(0));
	break;
	case 2:
		if(!_PC(strcmp,(v[1],"--version")))
         	  ver();
		if(!_PC(strcmp,(v[1],"--usage")))
		  help();
		  _PC(exit,(0));
		break;
	case 3:
		return 2;
	default:
		return 7;// it over 3
  }
}
char *opt="itrL";
int option(int c,char **v){
  char ch;
  int r=0;
  while((ch=_PC(getopt,(c,v,opt))) )
  {
    switch(ch){
	case 'r':r=SET_BIT(r,0);break;
	case 'v':r=SET_BIT(r,1);break;

    }
  }
}
int main(int argc,char **argv){
  int n=arg(argc,argv);
  if(n==2){
    if(!ifdir(argv[1]))
	_PC(copyfile,(argv[1],argv[2],getMode(argv[1])));
    else {
	int bit=option(argc,argv);
	if(GET_BIT(bit,0)) 
		_PC(copydir,(argv[1],argv[2]));
	else
	  error("target is directory\n");
    }
  }
}

