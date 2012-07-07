#include <stdio.h>
//#include <linux/socket.h>
#include <linux/in.h>
#include <piece/piece_convention.h>
#include <piece/syscall64.h>
#include <piece/piece_code.h>
/*
 * server will receve SHAKE command
 * it return ACK,after ACK
 * can send LS
 * */
#define SHAKE 1
#define ACK   2
#define GETF  4
#define LS    5
#define PWD   6

struct rs{
	int cmd;
	int size;
	char data[0];
};


int main(int argc,char **argv){
	int slen,clen,cfd;
	struct sockaddr_in server_addr,client_addr;
	int sfd=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");	
	server_addr.sin_port=55;
	slen=sizeof(server_addr);
	bind(sfd,(struct sockaddr*)&server_addr,slen);
	int sl=listen(sfd,3);
	while (1) {
		cfd=accept(sfd,(struct sockaddr*)&client_addr,&clen);
		/*do something like read and write*/
		char send[sizeof(struct rs)];send[0]='C';
		char rev[sizeof(struct rs)];
		struct rs *revp=(struct rs*)rev;
		int s=read(cfd,rev,1);
		if(*rev=='A') {
			write(cfd,send,1);
			printf("client connect \n");
		}
		else{
			char *file="srv.c";
			int ofd=open(file,0,0);
			write(cfd,send,1);
		}
	}
	printf("client connect %d \n",cfd);
}

