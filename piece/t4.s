#
#	hello world program
#	for bsd kernel
#	phamthechung0@gmail.com

.glolbal _start,strlen,puts
.data
msg:
    .ascii "Hello world!\n"
    len= . - msg
.text
strlen:
    xor %eax,%eax
    .LP0:
    movb (%edi),%cl
    cmpb $0,%cl
    je .LP1
    inc %edi
    inc %eax
    jne .LP0
    .LP1:
    ret
_start
	xor %eax,%eax
	movb $1,%al
	xor %ebx,%ebx
	int $0x80
	