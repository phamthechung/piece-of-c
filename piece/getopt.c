/*
 *	Written by Pham The Chung
 *
 *	This program is free software;
 *	you can redistribute it or modify it
 *	under the term of the GNU General Public License as
 *	published by Free Software Foundation
 *	create Jan 1 2010 
 *  last   Fri 09 Jul 2010 08:22:52 AM ICT 
 *
 * */

#include <piece/string.h>
#ifndef NULL
#define NULL (0x0)
#endif
#define ERROR -1
#define _PC(n,p) n p
char opt_buf[256]={NULL};
char val_buf[256]={NULL};
char *poopt=NULL;
/*popt is use for long option popt*/
char *popt=opt_buf;
/*if popt has value it will be pval*/
char *pval=val_buf;
int pos=1;
int elem=1;
char special=0;
int optfree=-1;
int optopt=NULL;
/*
 * tested; find char in string;  strchar like function
 * return -1 or 1 if null string or not found,
 * if found char return 0
 * */
static int strChar( const char *s,const char ch ){
	if( s==NULL ) return -1;
	unsigned r=0,run=0;
	while( *(s+r)!=NULL ) r++; 
	while( r--!=0 ) {
		if( s[run++]==ch ) return 0;
	}
	return 1;
}
/*
	return the position of char finded
	return NO=0 if not found
	return at least 1 if found
*/
static int posChar( const char *str,char ch ){
	if(str==NULL) return -1;
	int pos=0;
	while( *(str+pos)!=NULL )
	{
		if( *(str+pos)==ch ) return pos+1;
		pos++;
	}
	return 0;
}
/*	implementation	*/
static void resetOpt( void ) {
	popt = NULL;
	pval = NULL;
	pos  = 1;
	elem = 1;
	optfree=-1;
}
/*
	TESTED ~stable
	when optlist "vcxf:C:"
	f is option need value after it
	
	short and long option return 
	: need value
	- long option
	* free option (no short nor long option)
	? unknown option
*/
char getopt( int c, char *const *list,const char *optlist) {
	char ret=NULL,count=0,len=strlen(optlist);
	//__label__ rewind;
	rewind:
	if( pos<c ){
	  if( *list[pos]=='-' ){
		if( *(list[pos]+1)=='-' ){
			ret='-';
			char epos=0,*pt2=(char *)(list[pos]+2);
			poopt=list[pos];
			if( !strChar(list[pos],'=') ){
				epos=posChar(pt2,'=');
				pval=strcpy(val_buf,pt2+epos-- );    //
			}else{epos=strlen(pt2);pval=NULL;}
			popt=strncpy(opt_buf,pt2,epos);
			pos++;
			return ret;
		}
		else
		{
			char countshort=_PC(strlen,(list[pos]+1));
			poopt=list[pos];
			/*process option -style=c99*/
			if( !strChar(list[pos],'=' ) ){
				ret='-';
				popt=_PC(strncpy, 
				(opt_buf,list[pos]+1, 
				posChar(list[pos],'=')-2));
				pval=_PC(strcpy,
				(val_buf,list[pos]+posChar(list[pos],'=') ));
				pos++;
			}else{
			    /*process short option here*/
			  if( !strChar(optlist,*(list[pos]+elem)) ){
			    ret=*(list[pos]+elem);
				/*if it is special*/
			  int vp=posChar(optlist,*(list[pos]+elem));
			  if(*(optlist+vp)==':') {
			    special=*(list[pos]+elem);
			    if((elem>=countshort)&&(pos>=(c-1))) {
			        optopt=*(list[pos]+elem);
			        popt=list[pos]+elem;
			        pval=NULL;
			        ret=':';
			    }else{
			        /*get the value*/
			        if(elem<countshort){
			         pval=strcpy(val_buf,list[pos]+elem+1);
			          elem=0;
			          pos++;
			        }
			        else
			        if(pos<c){
			            pval=strcpy(val_buf,list[pos+1]);
			            elem=0;
			            pos+=2;
			        }
			    }
			  }
			}
			else {
			    ret='?';
			    popt=list[pos]+elem;
			    optopt=*(list[pos]+elem);
			}
			/*goto next arg in list*/
			if( elem>=countshort ) 
			{ 
			  pos++;elem=1;
			}
				else elem++;
			}
			return ret;
		}
	  }else{
		optfree=pos;
		pos++;
		/*uncomment below to make it ignore the free option*/
		//goto rewind;
		return '*';
	   }
	}
	resetOpt();
	return NULL;
}

/* TESTED
	check size of string value if zero return no
*/
char OpthasValue( void ){
	if( !strChar(poopt,'=') ) {
		int size=_PC(strlen,(poopt+posChar(poopt,'=')));
		if( size!=0 )	return 1;
	}
	pval=NULL;
	return 0;
}
char *getpopt(void){
	return popt;
}
char *getpval(void){
	return pval;
}
