/*
	Written by Pham The Chung
	sha.c 2010
	is sha2 digest message
	this file for crc md5 sha
*/
/*
	piece of c native dont provide cbrt function to calculate
	sha will have two mode : fast or slow
	when compile with fast mode it have more performance
	slow mode for compatible, of course it slow
*/
#include <string.h>
#define BITFRAG	512
#define Public 
#define Private static
/*
		first 32 bit fractional part of square root of first 8 primes 2->19
		2 3 5 7 11 13 17 19
		sqrt of 2 4f5c8ca8 
	*/
Private dword h[8]={
		[0]= 0x6a09e667,[1]= 0xbb67ae85,[2]= 0x3c6ef372,[3]= 0xa54ff53a,
		[4]= 0x510e527f,[5]= 0x9b05688c,[6]= 0x1f83d9ab,[7]= 0x5be0cd19
};

/*
		first 32 bit fractional part of cube root of first 64 primes 2->311
		2 3 5 7 11 13 17 19
*/
Private dword k[64]={
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 
		0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 
		0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 
		0x5cb0a9dc, 0x76f988da,
		0xe49b69c1, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 
		0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 
		0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 
		0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 
		0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 
		0xbef9a3f7, 0xc67178f2
};
/*
	description sha2()
	+ append bit '1' to the message
	+ append k bits '0' where k is the minimum number >=0 such that
	the message length is congruent to 448
	+ append len of message 64 bit big edian
	break the message to 512 bit chunk
	for each chunk
	   break to 16 4bytes big endian word w[0..15]
	+ Extend the sixteen 32-bit words into sixty-four 32-bit words:
    for i from 16 to 63
        s0 := (w[i-15] rightrotate 7) xor (w[i-15] rightrotate 18) xor (w[i-15] rightshift 3)
        s1 := (w[i-2] rightrotate 17) xor (w[i-2] rightrotate 19) xor (w[i-2] rightshift 10)
        w[i] := w[i-16] + s0 + w[i-7] + s1
	+Initialize hash value for this chunk:
    a := h0
    b := h1
    c := h2
    d := h3
    e := h4
    f := h5
    g := h6
    h := h7
	+Main loop:
    for i from 0 to 63
        S0 := (a rightrotate 2) xor (a rightrotate 13) xor (a rightrotate 22)
        maj := (a and b) xor (a and c) xor (b and c)
        t2 := S0 + maj
        S1 := (e rightrotate 6) xor (e rightrotate 11) xor (e rightrotate 25)
        ch := (e and f) xor ((not e) and g)
        t1 := h + S1 + ch + k[i] + w[i]

        h := g
        g := f
        f := e
        e := d + t1
        d := c
        c := b
        b := a
        a := t1 + t2
	+Add this chunk's hash to result so far:
    h0 := h0 + a
    h1 := h1 + b
    h2 := h2 + c
    h3 := h3 + d
    h4 := h4 + e
    h5 := h5 + f
    h6 := h6 + g
    h7 := h7 + h
	+Produce the final hash value (big-endian):
digest = hash = h0 append h1 append h2 append h3 append h4 append h5 append h6 append h7
*/
/*
	subsequence of sha2()
*/
char *_sha2(char *p){
	int len=0,nrbit;
	len = strlen(p);
	nrbit=len*8;
	
	/*append bit 1 to message*/
	
}
/*
	I'm digest a message and return hex string that 
*/
Public char *sha2( char*m ){
	
}
#ifdef MAIN
#include <stdio.h>
int main(int argc,char **argv){
		
}
#endif


