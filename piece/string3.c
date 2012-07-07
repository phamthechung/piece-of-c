/*
	Written by Pham The Chung
	June 1 2010
*/

#define NULL (0)
/*
 *  copy from src to dst at len
 * */
char *cpyStringat(char *dst,char *src,int len){
	
}
/*
	swap 2 pointer
*/
void*swapPointer(void**a,void**b){void*t;t=*a;*a=*b;*b=t;return(a);}
/*
	swap 2 character in array of character
*/
int swapChar(char ar[],int x,int y){
	if(!ar) return 0;
	char te=ar[x];
	ar[x]=ar[y];
	ar[y]=te;
}
/*
	if two string are same return 0
	diff return !0
*/
static long cmps( const char *a, const char *b )
{
	if( (a==NULL)&&(b==NULL) ) return 0;
	const char *s = a;
	const char *d = b;
	for ( ; *a==*b ; a++,b++ ) 
		if( (*a == 0x0)&&(*b==0x0) ) 
			return (a-s) - (b-d);
	return (++a-s);
}
/*
	not tested
	must end with NULL pointer to proper copy
*/
char **cpyList( char *dest[],char *list[] ){
	if( dest==NULL||list==NULL) return dest;
	unsigned r=0;
	while( list[r]!=NULL ){
		_PC(strcpy,(dest[r],list[r]));
		r++;
	}
	return dest;
}
/*
	not test
	cat list to flat dest
*/
char *catList( char *dest,char *list[] ){
	if( dest==NULL||list==NULL) return dest;
	unsigned r=0;
	while( list[r]!=NULL ){
		cpyStringat( dest,list[r],strlen(dest));
		r++;
	}
	return dest;
}
/*
	not test
	search key in list
	return position in list
*/
char *isinList( const char *key,const char *list[] ) {
	if( key==NULL||list==NULL ) return NULL;
	unsigned r=0;
	while( list[r]!=NULL ){
		if( !cmps(key,list[r])) 
		  return (char*)list[r];
		r++;
	}
	return NULL;
}

struct str_wc{
	int nrline;
	int nrword;
	int nrcodeline;
};
long wc( const void *mem,struct str_wc *wc_ret ){
	if(mem==NULL) return -1;
	const char *pt=(const char*)mem;
	unsigned nline=0,nword=0,code_line=0;
	char in=0,out=1,cin=0,cout=1,cstate=0,comment_count=0,one=1,text=1;
	do{
		if( *pt=='/'&& *(pt+1)=='*' ) {
			one=0;
			cin=1;
			if( cin==1&&cout==1) {cstate=1;comment_count++;}
			cout=0;
		}
		if( *pt=='*'&&*(pt+1)=='/') {cin=0;
			if(cin==0&&cout==0) cstate=0;
			cout=1;
		}
		if( *pt==0xa&&cstate==0&&one==1 ) {code_line++;}
		if( *pt==0xa )	{nline++;one=1;}
		if( (*pt>=0x40&&*pt<=0x5f)||(*pt>=0x61&&*pt<=0x7a ) ) {
			in=1;
			if((in==1)&&(out==1)) ++nword;
			out=0;
		}
		if(*pt==0x20||*pt==0x09||*pt==0x0a) {
			in = 0;out= 1;		
		}
		pt++;
	}while( *pt!=NULL );
	if(wc_ret!=NULL){
		wc_ret->nrline=nline;
		wc_ret->nrword=nword;
		wc_ret->nrcodeline=code_line;
	}
	return nline;
}
