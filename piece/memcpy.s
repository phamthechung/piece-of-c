memcpy:
	mov %rdi,%r14
	mov %rdx,%rax
	xor %rdx,%rdx
	mov $8,%r15
	div %r15
	.Lp1:
		cmp %rax,$0
		je .Lp2
		movq (%rai),%rbx
		movq %rbx,(%rdi)
		add %rdi,$8
		add %rsi,$8
		sub %rax,$1
		jmp .Lp1
	.Lp2:
		cmp %rdx,$0
		je .Lp3
		movb (%rsi),%r8b
		movb %r8b,(%rdi)
		add %rdi,$1
		add %rsi,$1
		sub %rdx,$1
		jmp .Lp2
	.Lp3:
		mov %r14,%rax
		ret