/*
	Written by Pham The Chung
	create March 1 2010
	piece_string2.c
	gcc [-m32/64] -c string2.c -Iinclude
	phamthechung0@gmail.com
*/
/*
	compile success
*/

#include <malloc.h>
#define _PI(type,name) type name


_PI(size_t, strlen)( const char *s ) {
	if( s==(0x0) ) return 0;
	unsigned long run=0;
	while( *(s+run)!=NULL ) run++;
	return run;
}

_PI(char *,strcpy) ( char *dest,const char *src ) {
	if( dest==NULL||src==NULL ) return dest;
	const char *this=src;
	unsigned r=0;
	while( *(this+r)!=NULL ) {
		*(dest+r) = *(this+r);
		r++;
	}
	*(dest+r)=NULL;
	return dest;
}
_PI(char *,strncpy) (char *dest,const char *src,size_t n){
	if( n<0 ) n=-n;
	if( dest==NULL||src==NULL ) return dest;
	const char *s= src;
	char *d= dest;
	unsigned r=0;
	while( n--!=0 ) *d++ = *(s+r++);
	*d=0x0;
	return dest;
}
/*
	
*/
_PI(long, strcmp)( const char *a,const char *b ){
	#define max(a,b) ((a)>(b)?(a):(b))
	// get the original of a and b
	const char *oa=a,*ob=b;  
	unsigned same=0,roa=0,rob=0;
	while( *(a+roa)!=NULL ) roa++;
	while( *(b+rob)!=NULL ) rob++;
	if ( roa!=rob ) return max(roa,rob);
	while( *a==*b ){
		same++;
		if( *a==NULL&&*b==NULL )
			return (a-oa) - (b-ob);
		a++;b++;
	}
	return max(roa,rob)-same;  // return at least 1
}
_PI(int,strncmp)(const char *sa,const char *sb,size_t n){
	const char *ss = sa;
	while( n-- ){
		if(*sa==*sb) {
			if( *sa==0x0&&*sb==0x0 )
				return 0;
			sa++,sb++;
		}
		else return sa-ss+1;
	}
	return 0;
}
_PI(char *,strcat) ( char *dst,const char *src ) {
	if( src ==0 ) return 0x0;
	const char *s=src; char *d=dst;
	int pos=0;
	while( *(d+pos)!=NULL ) pos++;
	while( *s!=NULL ){
		*(d+pos++) = *s++;
	}
	*(d+pos)=NULL;
	return dst;
}
_PI(char *,strncat) ( char *dest,const char *src,size_t n ) {
	if( n<0 ) n=-n;
	if( dest==NULL||src==NULL ) return dest;
	char *s= (char*)src; char *d = dest;
	int r=0;
	while( *++d!=0x0 );
	while( n--!=0 ) {
		*d++ = *( s+r++ );
	}
	return dest;
}
_PI(char *,cpyStringat)(char *this, const char *src,int pos) {
	if( src ==NULL||this==NULL ) return this;
	while( *src!= 0x0 ) 
		*(this+++pos) = *src++;
	*(this+pos) = 0x0;
	return this;
}
/*!TESTED
	search word in str
	return position of next character
*/
_PI(char *,strstr)(const char *_haystack, const char *needle) {
	const char *word=_needle;
	size_t run=0,len,same=0;
	while( *(word+len) ) len++;
	while( *(_haystack+run) != NULL ) {
		if( *(_haystack+run)==*word ) {
			same++;word++;
		}
		else 
		if( same>0 )	{
			same=0;word=needle;
		}
		if( same==len ) return _haystack+run;
		run++;
	}
	return NULL;
}
/*
	find first occurence c in s
	return pointer to that char in s
	if no return NULL
*/
_PI(char *,strchar)(const char *s,int c){
	if(s==NULL) return NULL;
	char ch=(char)c;
	int r=0;
	while( *(s+r) ){
	  if(*(s+r)==ch) return (char *)(s+r);
	  r++;
	}
	return NULL;
}
/*
	browse through string and record last occrence c in s
	return pointer to c,NULL if not found
*/
_PI(char *,strrchar)(const char *s,int c){
	if(s==NULL) return NULL;
	char ch=(char)c;
	char *pt=NULL;
	int r=0;
	while(*(s+r)){
	  if(*(s+r)==ch) {
	    pt=(char *)(s+r);
	  }
	  r++;
	}
	return pt;
}

/*!TESTED
	duplicate string and give a pointer to dup
*/
_PI(char *,strdup)(const char *pt){
	if(!pt) return NULL;
	int len=_PC(strlen,(pt));
	char *ret=NULL;
	if(len) ret=(char *) malloc(len+1);
	_PC(strcpy,(ret,pt));
	return ret;
}

_PI(void *,memcpy)(void *dest,const void *src,size_t n) {
	if( dest==NULL||src==NULL ) return dest;
	char *d,*s;
	d = (char *)dest;
	s = (char *)src;
	while( n--!=0 ) *d++ = *s++;
	return dest;
}

_PI(int, memcmp)(const void *a,const void *b, size_t n) {
	if( a==NULL&&b==NULL ) return 0;
	char flag=0;
	const char *x = (const char*) a;
	const char *y = (const char*) b;
	long run=0;
	while( n-- ){
		if( x[run]!=y[run++] ) return run;
	}
	return 0;
}
/*	memset set char */
_PI(void *,memset)(void *_vpt, int ch,size_t size){
	char abc=ch;
	char *cpt=(char *)_vpt;
	while(size--){
	  *cpt++=ch;
	}
	return _vpt;
}
/*
	if meet c in s return pointer to if none return NULL
*/
_PI(void *,memchr)(const void *_s,int c,size_t n){
	int r=0;
	char *pt=(char *)_s;
	char ch=(char)c;
	while(n--){
		if(pt[r]=ch) return (void*)(_s+r);
		r++;
	}
	return NULL;
}

_PI(char *,basename)(const char *path) {
	#define MAX_FILE_NAME	256
	size_t len=0,r=0;
	unsigned char *pt,sep;
	sep='/';
	while( *(path+len) ) ++len;
	size_t alen=len;
	size_t first=len-1;
	char *one= (char *)(path+len-1);
	do{
		if( *one--==sep )
			if( first==(len-1))
			{	first--;continue;	}
			else {break;}
	} while( --len );
	alen -= len;	// alen is string len of filename
	pt = malloc(MAX_FILE_NAME);
	char *gap=(char *)(path+len);
	while( *(gap)!=NULL )  *(pt+r++) = *(gap++);
 	if( *(pt+r-1)!=sep ) *(pt+r) = NULL;
	else *(pt+r-1) =NULL;
	return pt;
}
#define ASM __asm__
_PI(int,ffs)(int _i){
	ASM (
	  "bsfl %0,%%eax \n"
	  "incl %%eax \n"
	  ::"g"(_i)
	);
}
#ifdef __x86_64__
_PI(int,ffsl)(int _l){
	ASM (
	"bsf %rdx,%rax \n"
	"add $1,%rax \n"
	);
}
#endif
/*
	select bit at pos and return it value
*/
static char bt(int ch,int pos){
	ASM ( 
		"movl $0,%%eax \n"
		"btl %%ebx,%0 \n"
		"adcl $0,%%eax \n"
		::"g"(ch),"b"(pos)
	);
}
/*TESTED
	compare 2 string but ignore case
*/
_PI(int,strcasecmp)(const char *a,const char *b){
	int r=0;
	char *d=(char *)b,*c=(char *)a;
	while( (c!= NULL)&&(d!=NULL) ){
		c=(char *)(a+r);
		d=(char *)(b+r);
		if(*c!=*d){
			if((*c>=0x41&&*c<=0x7a)&&
				(*d>=0x41&&*d<=0x7a))
			{
			   if(bt(*c,5)==0)
			    if((*c+0x20)!=*d) return r+1;
			} else return r+1;
		}
		r++;
	}
	return 0;
}
/*
	return string tell meaning of error code
*/
_PI(char *,strerror)(int _errnum){
	
}

/*	*tested* return pathname if has different in some case
	like this: path/to/file return : path/to
	but this : path/to/file/ return path/to/file
	if wanted to change this case may modify code
*/
_PI(char *,pathname)(char *path) {
	short i,len=0,alen;
	char *pt,sep='/';
	while( *(path+len)!='\0' ) ++len;  //get lenght of path
	while( len!=0 ) {
		if( *(path+len)==sep ) break;
		len--;
	}
	len++;
	pt = (char*) malloc(len);
	_PC(strncpy,(pt,path,len));
	return pt;
}

/*!TESTED
	find needle in haystack, much like strstr
*/
_PI(void *,memem)
(  
	const void *__haystack,size_t __haystack_size,
	const void *__needle,  size_t __needle_size
)
{
	if(!__needle_size) return NULL;
	const char *hay = __haystack;
	const char *needle=__needle;
	const char *needle_run=needle;
	void *vpt;
	size_t hsize=__haystack_size,r=0,same=0;
	while(hsize--){
	  if(*hay++==*needle_run++) same++;
	  else
	  if(same>0) {
	    needle_run=needle;
		same=0;
	  }
	  if(same==__needle_size) {
		vpt=__haystack+r;
		return vpt;
	  }
	  r++;
	}
	return NULL;
}
/*!TESTED
	like memcpy,allow to overlap
*/
_PI(void *,memmove)
 (void *dest0, void const *source0, size_t length)
{
  char *dest = dest0;
  char const *source = source0;
  if (source < dest)
    /* Moving from low mem to hi mem; start at end.  */
    for (source += length, dest += length; length; --length)
      *--dest = *--source;
  else if (source != dest)
    {
      /* Moving from hi mem to low mem; start at beginning.  */
      for (; length; --length)
        *dest++ = *source++;
    }
  return dest0;
}
/*!TESTED
	string span
	return position that any char in set not in str
*/
_PI(size_t ,strspn) (const char *str,const char *set){
	size_t r=0,count=0;
	const char *set_run=set;
	size_t len=_PC(strlen,(set));
	while(*(str+r)){
	  while(*set_run){
		if( *(str+r)==*set_run++) { count=0;break;}
		count++;
	  }
	  if(count==len) return r;
	  set_run=set;
	  r++;
	}
	return 0;
}
/*INCOMPLETE
	span complement of string
*/
_PI(size_t,strcspn)(const char *str,const char *set){
	const char *set_run=set;
	size_t r=0,count=0;
	size_t len=_PC(strlen,(set));
	while(*(str+r)){
	  while(*set_run) {
	    if(*(str+r)==*set_run++) {count=0;return r;}
		count++;
	  }
	  r++;
	}
	return 0;
}
/*
	return pointer first occurence of any char in set match in str,NULL if no
*/
_PI(char *,strpbrk)(const char *str,const char *set){
	const char *set_run=set;
	size_t r=0;
	size_t len=_PC(strlen,(set));
	while(*(str+r)){
		while(*set_run){
		  if(*(str+r)==*set_run++) return str+r;
		}
		set_run=set;
		r++;
	}
	return NULL;
}
_PI(size_t,strlcpy)( char *dst,const char *src,size_t size){
	#define FAST_CP_SIZE	8
	const char *_src=src;
	char *_dst=dst;
	size_t r=0,rem;
	size_t *_d=(size_t *)dst,*_s=(size_t *)src;
	if(size>FAST_CP_SIZE){
	  rem=size;
	  while(rem-sizeof(size_t))
	  {
		*_d++=*_s++;
		r+=sizeof(size_t);
	  }
	  _dst=dst+r,_src=src+r;
	}
	while(rem--){
	  *_dst=*_src;
	  r++;
	}
	return r;
	#undef FAST_CP_SIZE
}
_PI(size_t,strlcat)(char *dst,const char *src,size_t size){
	size_t dst_len = _PC(strlen,(dst));
	return _PC(strlcpy,(dst+dst_len,src,size));
}

