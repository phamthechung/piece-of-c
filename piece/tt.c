#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
void die(const char *string){
	puts(string);
	exit(EXIT_FAILURE);
}
int printv(char **argv){
	while(*argv){
		printf("%s\n",*argv);
		argv++;
	}
}
const char *version="command version 1.0\nWritten by phamthechung0@gmail.com\
\ndate:7/6/2012";
const char *usage="cmd -cvh file file2";
int main(int argc,char **argv){
	int ch=0;
	if(argc<2) printf(usage);
	while((ch=getopt(argc,argv,"cvh"))!=-1){
		switch(ch){
			case 'v':printf(version);exit(0);
				break;
			case 'h':printf("usage: cmd -cvh file.sh");exit(0);
				break;
			case 'c': if(argc<3) die("not enough argument");
				printv(argv+2);
				break;
			default: puts("unknown argument");
				break;
		}
	}
}