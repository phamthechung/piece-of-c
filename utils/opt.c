#include <stdio.h>
#include <getopt.h>
int main(int argc,char **argv){
	int ch=0;
	while((ch=getopt(argc,argv,"abco:I:"))!=-1){
		switch(ch){
		case '-':printf("%s\n",argv[optind]);break;
		case '?':printf("Unknown option\n");break;
		}
	}
	printf("%s\n",argv[optind]);
	return 0;
}