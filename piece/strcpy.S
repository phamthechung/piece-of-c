#ifndef i386
#error	"compile just for x86_32"
#endif

strcpy:
	movl 4(%esp),%eax
	mov %eax,%edi
	movl 8(%esp),%edx
	.LPs0:
	movb (%edx),%cl
	cmpb $0,%cl
	je .LPs1
	movb %cl,(%eax)
	inc %eax
	inc %edx
	jmp .LPs0
	.LPs1:
	movb $0,(%eax)
	mov %edi,%eax
	ret
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
