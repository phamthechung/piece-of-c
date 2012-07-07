#ifndef _PIECE_STRING_EXT
#define _PIECE_STRING_EXT
#include "piece_code.h"
#include "itype.h"

struct str_wc{
	int nrline;
	int nrword; 
	int nrcodeline;
};
/*
	compare 2 string like strcmp
*/
//Link Public long cmps(const char *a,const char *b);
Link Public char **cpyList(char *dst[],char *list[]);
Link Public char *catList(char *dst,char *list[]); 
Link Public char *isinList(const char *key,const char *list[]);
Link Public long wc(const void *mem,struct str_wc *wc_ret);

#endif
