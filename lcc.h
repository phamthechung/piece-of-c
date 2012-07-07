#ifndef LCC_H
#define LCC_H
#define MAX_FILE_SIZE	(1024*1024)
typedef struct {
	const char *name;
	long size;
	int mode;
	char data[0];
}File;
typedef struct {
	char *start;
	int len;
	
}Function;
const char *keyword[]=
{
"auto","break","case","char","const","continue","default","do","double",
"else","enum","extern","float","for","goto","if","int","long","register","return",
"short","signed","sizeof","static","struct","switch","typedef","union","unsigned",
"void","volatile","while","inline","restrict",
NULL
};
const char *punctuator[]={
	"[","]","(",")","{","}",".","->",
	"++","--","&","*","+","-","~","!","/","%",
	"<<",">>",">","<","<=",">=","==","!=","^","|","&&","||","=",
	"*=","/=","%=","+=","-=","<<=",">>=","&=","^=","|=",",","#","##",
	"<:",":>","<%","%>","%:","%:%:",
	NULL
};

const char *option="hvo:cSBI";
const char *version="lcc version 0.1\nWritten by phamthechung0@gmail.com";
const char *help="usage: lcc -hvcoSBI file.c";
#endif