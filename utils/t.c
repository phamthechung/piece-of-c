#include <stdio.h>
#include <piece/dirent.h>
#include <piece/c_lang.h>
MAIN {
	if(argc<2) {printf("less arguement\n");exit(1);}
	Dir *dirp = opendir(argv[1]);
	if(dirp==NULL) return 1;
	Dirent *entp;
	while((entp=readdir(dirp)) ) {
	 printf("%s\n",entp->d_name);
	}
	exit(0);
}
