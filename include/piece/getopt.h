/*
	getopt.h 2010
	Written by Pham The Chung
	CONTACT pham.the.chung0@gmail.com
	Create Jan 1 2010
*/
#ifndef _GETOPT_H
#define _GETOPT_H
/*get value when long option nor when unknown option*/
extern char *popt;
/*get value when long option has value*/
extern char *pval;
/*if no -1 it has value in argv*/
extern int optfree;
/*error option,unknown option*/
extern int optopt;
/* TESTED
 * int main(int argc,char **argv){
 * char ch;
 * while( (ch=piece_getopt(argc,argv,"abcf:v")) ){
 * 	switch(ch){
	   case '*': printf("free option %s \n",argv[optfree]);break;
	   case ':': printf("need value by %c\n",optopt);break;
	   case 'f': printf("file: %s \n",pval);break;
	   case '-': 
	      {
	            if( piece_OpthasValue() )
		        printf("long opt:%s=%s\n",popt,pval);
		    else 
		        printf("long opt:%s\n",popt);
		    break;
		    }
		    case '?': printf("unknown option: %c\n",*popt); break;
		    default:  printf("option:%c \n",ch);break;
	}
  }
}
*/

extern char getopt (int __argc,char *const *__argv,const char *__shopt);
/* TESTED
*/
extern int OpthasValue( void );
/* TESTED
	getpopt to get the value of opt when long option for file name
	use with getOpt getlongOpt function
*/
extern char *getpopt( void );
/*TESTED
	get string of value in long option has value --long=123
*/
extern char *getpval( void ) ;

#endif
