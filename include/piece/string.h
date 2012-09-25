/*
	written by Pham The Chung
	June 1 2010
	last	Sep 21 2010
*/
#ifdef _STRING_H
#define _STRING_H

#define Link extern
#define _PP(t,n) t n

/*
	dont know what happen if overlap memory
*/
Link _PP(void *,memcpy)(void *dst,const void *src,size_t n);
Link _PP(int,memcmp)(const void *a,const void *b,size_t n);
/*
	like memcpy, but use when overlap memory
*/
Link  _PP(void *,memmove)(void *dst,const void *src, size_t __n);
Link  _PP(void *,memchar)(const void *__s,char c,size_t __n);
Link  _PP(void *,memset)(void *__s,int c,size_t n);
Link  _PP(void *,memmem)
(
	void *_haystack,size_t haylen,
	void *_needle,size_t needle_len
);
Link  _PP(size_t,strlen)(const char *s);
Link  _PP(char *,strcpy)(char *dst,const char *src);
Link  _PP(char *,strncpy)(char *dst,const *src,size_t n);
Link  _PP(int,strcmp)(const char *a,const char *b);
Link  _PP(int,strncmp) (const char *a,const char *b,size_t n);
Link  _PP(char *,strcat) (char *dst,const char *src);
Link  _PP(char *,strncat)(char *dst,const char src,size_t n);
Link  _PP(int,strstr)(const char *lstring,const char *src);

Link  _PP(char *,basename)(const char *path);
Link  _PP(char *,strchar)(const char *__s,int c);
Link  _PP(char *,strrchar)(const char *__s,int c);
Link  _PP(char *,strdup)(const char *__s);
/*
  return first occurence any char in set finded from str,NULL if not found
*/
Link  _PP(char *,strpbrk)(const char *str,const char *set);
/*	return the first position in str that not contain any character in set
	or return the number of character span
*/
Link  _PP(size_t ,strspn)(const char *str,const char *set);
/*
	return position the first occurence in str that contain any char in set
*/
_PP(size_t,strcspn)(const char *str,const char *set);
/*
	copy cat string from source to dest with only __size bytes, return lenght 
	of __src 
*/
Link 	size_t strlcat(char *__dst,const char *__src,size_t __size);
Link 	size_t strlcpy(char *__dst,const char *__src,size_t __size);
/*
	return first bit set or 0
	start value 1 
*/
Link  _PP(int,ffs)(int __i);

/*
  copy src to at dpos in dst for _bytes bytes
*/
Link  _PP(char *,cpynStringat)(char *dst,const char *src,size_t);


#endif
