#include <stdio.h>
#include <piece/c_lang.h>
die(const char *s){
	puts(s);
	exit(1);
}
MAIN {
	if(argc<3) die("Missing argument");
	int fd_sold,fd_buy;
	fd_sold = open(argv[1],O_RDONLY);
	if(fd_sold<0) die("cant open file argv[1]");
	fd_buy = open(argv[2],O_WRONLY);
	if(fd_buy<0) die("cant open file argv[2]");
	struct stat fod;
	if(fstat(fd_sold)) die("cant stat fd_sold");
}
