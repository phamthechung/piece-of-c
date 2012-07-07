/*
	41c8 0000=0100 0001 1100 1000 0000 0000 0000 0000
	sign bit: 0
	exponent: 1000 0011=0x83=131
	significand: 1100 1000 0000 0000 0000 0000
	decode exponent: 131-127=4
	decode significand: 1+0.5+.0625=1.5625
	41c8 0000= 1.5625x2^4=25
	====================
	3f80 0000=0011 1111 1000 0000 0000 0000 0000 0000
	exponent 0111 1111 =7f
	significant 1000 0000 0000 0000 
*/

char *gcvt(double d,int size,char *buf){
	
}
