/*
 * written by Pham The Chung 
 * simple sh.c
 * just put command on input
 * compile: gcc -o sh sh.c
 * phamthechung0@gmail.com
 * copyright June 2012
 * */
 /*
	alias profile list file
	-variable test
	-expansion
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <dirent.h>
#include <sys/stat.h>
#include <piece/c_lang.h>
const char *version="sh.c version 1.0 beta\n\
Written by phamthechung0@gmail.com\
date:June 8 2012";
const char *usage="usage: sh [-vhc] file.sh";
extern char **__environ;
char shell_prompt[256];
char *PS1=NULL;
char *PS2=NULL;
char *input=NULL;
char *profile="/etc/profile";
char rc[260];
struct alias_cmd **Alias=NULL;
struct variable **Var=NULL;
int var_pos=-1;
int Alias_pos=-1;
int command_status=0;
char *file_mem_pt=NULL;
typedef int (*buitin_fp)(int ,char **);
typedef int (*Function)(int,char **);
struct builtin_cmd{
	char *name;
	buitin_fp action;
};
struct alias_cmd{
	char name[256];
	char *value;
};
struct variable{
	char *name;
	char *value;
};
struct block{
	int type;
	char *start;
	int len;
	Function action;
};
int tell_var_full=1;
#define NR_INIT_ALIAS	32
#define NR_INIT_VAR		32
#define MAX_FILE_SIZE	1024*1024
#define MAX_CHAR_COMMAND_LINE	4096
void *read_file(const char *name){
	struct stat fod;
	if(stat(name,&fod)) return NULL;
	if(fod.st_size>MAX_FILE_SIZE) return NULL;
	void *mm=malloc(fod.st_size+1);
	int fd=open(name,O_RDONLY,0);
	int rd=read(fd,mm,fod.st_size);
	char *pt=(char*)mm;
	*(pt+fod.st_size)=0;
	return mm;
}

int sh_exit ARG {
	exit(atoi(argv[1]));
}
int sh_cd ARG {
	if(argc>1) return chdir(argv[1]);
}
int sh_pwd ARG{
	printf("%s\n",getcwd(NULL,1024));
}
int tell_alias_full=1;
int sh_alias ARG {
	if(Alias_pos>=NR_INIT_ALIAS){
		size_t len = sizeof(struct alias_cmd)*tell_alias_full*NR_INIT_ALIAS;
		struct alias_cmd **old=Alias;
		tell_alias_full++;
		Alias=malloc(sizeof(struct alias_cmd)*tell_alias_full*NR_INIT_ALIAS);
		memcpy(Alias,old,len);
	}
	if(argv[1][0]=='-'||argc<2) {
		if(argv[1][1]=='p') {
			int r=0;
			while(Alias[r]){
				printf("%s=%s\n",Alias[r]->name,Alias[r]->value);
			}
		}else
		printf("alias:sh:unknown option\n");
	}
	char *here=strchr(argv[1],'=');
	if(here==NULL) goto xy;
	size_t value_len=strlen(here);
	Alias[Alias_pos]->value=malloc(value_len);
	size_t len=here-argv[1];
	strncpy(Alias[Alias_pos]->name,argv[1],len);
	strcpy(Alias[Alias_pos]->value,here+1);
	Alias_pos++;
	xy:
	return 0;
}
int sh_ls ARG {
	char *name=".";
	if(argc>1) name = argv[1];
	DIR *dirp;
	struct dirent *entp=NULL;
	dirp = opendir( name );
	if(dirp==NULL) return 1;
	while(entp = readdir(dirp)){
	  printf("%s\n",entp->d_name);
	}
	return 0;
}
int sh_unlink ARG {
	if(argc<2) {
		puts("unlink:missing argument");
		return 1;
	}
	while(argc--){
	  unlink(argv[argc]);
	}
	return 0;
}
/*FIXME:incomplete code need to*/
int sh_test ARG{
	int ch=0;
	while((ch=getopt(argc,argv,"ebcdfghkLprstuwx"))!=-1){
		switch(ch){
			case 'e': if(access(argv[optind],F_OK)) return 0;
			default: return 1;
		}
	}
}
struct builtin_cmd builtin_cmds[]={
	{	"exit",sh_exit},
	{	"cd",sh_cd},
	{	"pwd",sh_pwd},
	{	"alias",sh_alias},
	{	"test",sh_test},
	{	"ls",sh_ls},
	{	"unlink",sh_unlink},
	{	NULL,NULL}
};

void die(const char *string){
	printf(string);
	exit(EXIT_FAILURE);
}
void error(const char *string){
	perror(string);
	exit(1);
}
int countword(char *string){
	int count=0;
	while(*string==' ') string++;
	while(*string){
	  if(*string==0x20) count++;
	  string++;
	}
	return count;
}
char *first_word(char *string){
	while(isspace(*string)) string++;
	size_t len=strchr(string,' ')-string;
	char *ret=(char*)malloc(len+1);
	strncpy(ret,string,len);
	return ret;
}
char **str2array(const char *word,char sep){
  if(word==NULL) return NULL;
  while(*word==sep) word++;
  char *path=(char*)word;
  size_t len=strlen(path);
  size_t frag=0,r=0,count=0,msize;
  char **vpath;
  /*first count how many*/
  while(*path)	if(*path++==sep) frag++;
  vpath=(char **)malloc( (frag+2)*sizeof(char*)+len+frag );
  path=(char*)word;
  vpath[r]=vpath+frag+2;
  while(*path){
	*(vpath[r]+count++)=*path++;
	if(*path==sep) {
	  *(vpath[r]+count)=(char*)NULL;
	  vpath[r+1]=vpath[r]+count+1;
	  count=0,path++,r++;
	}
  }
  vpath[r+1]=NULL;
  return vpath;
}
char *which(const char *word){
  char **vpath=str2array(getenv("PATH"),':');
  char buf[300],*rpt=0;
  size_t r=0;
  while(vpath[r]){
	strcpy(buf,vpath[r]);
	strcat(buf,"/");
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
int check_builtin(char *string){
	int i=0;
	char *cmd=first_word(string);
	while(builtin_cmds[i].name){
		if(!strcmp(builtin_cmds[i++].name,cmd)) return i;
	}
	return 0;
}
int do_builtin(char *string){
	int argc=countword(string);
	char **argv=str2array(string,' ');
	int i=check_builtin(string);
	command_status= builtin_cmds[i-1].action PASS;
	free(argv);
}
int do_external(char *string){
	int argc=countword(string);
	char **argv = str2array(string,' ');
	char *name=first_word(string);
	char *pt = which(name);
	if(pt){
		int pid= vfork();
		if(pid==0) command_status =execve(pt,argv,NULL);
	}
	else {
		command_status=127;
		puts("sh: command not found\n");
	}
	free((void*)name);
	free((void*)argv);
	free((void*)pt);
	return command_status;
}
int check_alias(char*string){
	int r=0;
	while(Alias[r]){
		if(!strcmp(Alias[r]->name,string)) return r;
		r++;
	}
	return -1;
}
//list && || pipe > 
int do_command(char *string){
	char *cmd=first_word(string);
	char *real_cmd=NULL;
	int pos=check_alias(cmd);
	if(pos<0) real_cmd=Alias[pos]->value;
	else real_cmd=string;
	if(check_builtin(real_cmd)) 
		command_status=do_builtin(real_cmd);
	else command_status=do_external(real_cmd);
}
/*incorrect code*/
int do_list(char *ls_cmd){
	char *array=NULL,string=ls_cmd;
	array=strstr(string,"&&");
	if(array==NULL) {
		array=strstr(string,"||");
		if(array!=NULL){
			int len=array-string;
			char *pt=malloc(len+2);
			strncpy(pt,string,len);
			do_command(pt);
			free(pt);
			if(command_status==0) goto exit;
			else{
				char*next=string+len+2;
				do_command(next);
			}
		}else{
			do_command(string);
		}
	}
	else{
		int len=array-string;
		char *pt=malloc(len+2);
		strncpy(pt,string,len);
		do_command(pt);
		if(command_status==0)
		{
			char*next=string+len+2;
			do_command(next);
		}else goto exit;
		free(pt);
	}
	exit:
	return command_status;
}
//illusion about variable in shell
int variable(char *var){
	char *eq=strchr(var,'=');
	if(eq) {
		if(var_pos>=NR_INIT_VAR){
			struct variable **old=Var;
			size_t len= sizeof(struct variable)*NR_INIT_VAR*tell_var_full;
			tell_var_full++;
			Var=malloc(sizeof(struct variable)*NR_INIT_VAR*tell_var_full);
			memcpy((void*)Var,(void*)old,len);
		}
		int len=eq-var;
		Var[var_pos]->name=strncpy(malloc(len+1),var,len);
		int remain=strlen(var)-len;
		Var[var_pos]->value=strncpy(malloc(remain),var+len+1,remain);
		var_pos++;
	}
	return 0;
}
/*error incomplete here 
tell about command line is when variable or list
how to expand line by variable 
echo ${path}/${file}
*/
int cmd_conscious(char *line){
	char *eq=strchr(line,'=');
	if(eq) return variable(line);
	else {
		return do_list(line);
	}
}
char *readline(const char *prompt){
	int count=0,chung=0,r=2;
	char *pt=malloc(MAX_CHAR_COMMAND_LINE);
	char *hold=pt;
	printf(prompt);
	while(chung!='\n'){
		if(count==MAX_CHAR_COMMAND_LINE) {
			r++;
			char *npt=malloc(MAX_CHAR_COMMAND_LINE*r);
			memcpy(npt,pt,count);
			pt=npt+count;
		}
		chung=getchar();
		count++;
		*pt=chung;
		pt++;
	}
	return hold;
}

int arg ARG{
	int ch=0;
	if(argc>1){
		while((ch=getopt(argc,argv,"cvh"))!=-1){
			switch(ch){
				case 'v': printf(version); exit(0);break;
				case 'h': printf(usage);exit(0);break;
				case 'c': if(argc<3) die("not enough argument\n");
					char *where=which(first_word(argv[optind]));
					int pid;
					pid=vfork();
					if(pid==0){
						command_status=execve(where,argv+2,NULL);
						exit(0);
					}
					if(pid<0) die("sh:can't not fork\n");
					break;
				default: puts("sh: unknown option\n");break;
			}
		}
		char *file=argv[optind];
		char *fm=(char*)read_file(file);	
		file_mem_pt=fm;
	}
	return command_status;
}
int line_len(char *string){
	int len=0;
	while(*string!=NULL||*string!=0xa){
		len++;
	}
	return len;
}
char *read_line_in_file(){
	int r=0;
	r=line_len(file_mem_pt);
	if(r==0) return NULL;
	char *pt= (char*)malloc(r+2);
	strncpy(pt,file_mem_pt,r++);
	file_mem_pt+=r;
	return pt;
}
int process_file(void){
	char *p=(char*)NULL;
	while((p=read_line_in_file())!=NULL){
		cmd_conscious(p);
		free(p);
	}
	return command_status;
}
void shell_init(void){
	Var = (struct variable**)malloc(sizeof(struct variable)*NR_INIT_VAR);
	var_pos=0;
	Var[var_pos]=NULL;
	Alias = (struct alias_cmd**)malloc(sizeof(struct alias_cmd)*NR_INIT_ALIAS);
	Alias[0]=NULL;
	Alias_pos=0;
	file_mem_pt=(char*)read_file(profile);
	process_file();
	free(file_mem_pt);
	strcpy(rc,getenv("HOME"));
	strcat(rc,"/");
	strcat(rc,".shrc");
	file_mem_pt=(char*)read_file(rc);
	process_file();
}
int shell ARG{
	shell_init();
	arg PASS;
    sprintf(shell_prompt,"%s:%s $ ",getenv("USER"),getcwd(NULL,1024));
	while(TRUE){
	  input=readline(shell_prompt);
	  cmd_conscious(input);
	  free(input);
	}
	return command_status;
}
MAIN
{
	return shell PASS;
}
