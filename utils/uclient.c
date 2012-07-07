/*
 * ftp client
*/
#include <stdio.h>
#include <sys/socket.h>
#define ipaddr "127.0.0.1"
#define port	55
#define BUFSIZE (64*1024)
#define set_bit(obj,th) (obj |= (1 >> th))
int sfd,len;
char recv_buf[BUFSIZE];
char send_buf[BUFSIZE]="START";

struct sockaddr_in im_client;
long connectSock(char *ipstr,short aport){
	int clen;
	sfd=socket( AF_INET,SOCK_STREAM,0);
	if(sfd<0) return sfd;
	im_client.sin_family=AF_INET;
	im_client.sin_addr.s_addr=inet_addr(ipstr);
	im_client.sin_port=port;
	clen=sizeof(im_client);
	int result=connect(sfd,(struct sockaddr*)&im_client,clen);
	if(result<0) return result;
	return sfd;
}

int main(argc,argv)
	const int argc;
	const char**argv;
{
	int con=connectSock(ipaddr,port);
	if(con<0) {
		printf("cant connect port %d %d %d\n",port,sfd,con);
		close(sfd);
		exit(1);
	}
	char sbuf[16];sbuf[0]='A';
	char rbuf[16];
	while(1){
		printf("\nenter to send: ");
		int ch=getchar();
		sbuf[0]=ch;
		write(sfd,sbuf,1);
		read(sfd,rbuf,1);
		printf("receive %c\n",*rbuf);
		if(*rbuf=='C'){
		}
	}
	close(sfd);
	exit(0);
}

