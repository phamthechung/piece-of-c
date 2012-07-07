#include <stdio.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <sys/select.h>
/*

*/
typedef struct inotify_event *Event;
struct inotify_event E;
void handle(Event e){
	switch (e->mask &(IN_ALL_EVENTS | IN_UNMOUNT | IN_Q_OVERFLOW | IN_IGNORED))
    {
      /* File was accessed */
    case IN_ACCESS:
      printf ("ACCESS:\n");
      break;

      /* File was modified */
    case IN_MODIFY:
      printf ("MODIFY \n");
      break;

      /* File changed attributes */
    case IN_ATTRIB:
      printf ("ATTRIB: \n");
      break;

      /* File open for writing was closed */
    case IN_CLOSE_WRITE:
      printf ("CLOSE_WRITE:\n");
      break;

      /* File open read-only was closed */
    case IN_CLOSE_NOWRITE:
      printf ("CLOSE_NOWRITE:\n");
      break;

      /* File was opened */
    case IN_OPEN:
      printf ("OPEN:\n");
      break;

      /* File was moved from X */
    case IN_MOVED_FROM:
      printf ("MOVED_FROM: \n");
      break;

      /* File was moved to X */
    case IN_MOVED_TO:
      printf ("MOVED_TO:\n");
      break;
      /* Some unknown message received */
    default:
      printf ("UNKNOWN EVENT \n");
      break;
    }
}
int read_event(Event e,int fd){
	int rd=read(fd,e,sizeof(E));
	return rd;
}
int event_check(int fd){
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(fd,&rfds);
	return select(FD_SETSIZE,&rfds,NULL,NULL,NULL);
}
int process_inotify_event(Event q,int fd){
	while(1){
		if(event_check(fd)>0){
			int r=read_event(q,fd);
			if( r>0) handle(q);
		}
	}
}
int main(int argc,char **argv)
{
	char *name=argv[1];
	int wd=0,fd=inotify_init();
	if(fd>0){
		wd=inotify_add_watch(fd,name,IN_ALL_EVENTS);
		printf("add watch to %s wd %d\n",name,wd);
	}
	if(wd>0){
		struct inotify_event q;
		process_inotify_event((Event)&q,fd);
	}
	inotify_rm_watch(fd,wd);
	close(fd);
}
