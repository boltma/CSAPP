	.file	"subexpr.c"
	.text
.globl sum_neighbors
	.type	sum_neighbors, @function
sum_neighbors:
.LFB2:
	movq	%rcx, %r8
	imulq	%rsi, %r8
	addq	%rdx, %r8
	leaq	1(%rsi), %rax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	subq	$1, %rsi
	imulq	%rsi, %rcx
	addq	%rdx, %rcx
	movq	(%rdi,%rax,8), %rax
	addq	(%rdi,%rcx,8), %rax
	addq	-8(%rdi,%r8,8), %rax
	addq	8(%rdi,%r8,8), %rax
	ret
.LFE2:
	.size	sum_neighbors, .-sum_neighbors
.globl sum_neighbors_opt
	.type	sum_neighbors_opt, @function
sum_neighbors_opt:
.LFB3:
	imulq	%rcx, %rsi
	addq	%rdx, %rsi
	leaq	(%rsi,%rcx), %rax
	movq	%rsi, %rdx
	subq	%rcx, %rdx
	movq	(%rdi,%rax,8), %rax
	addq	(%rdi,%rdx,8), %rax
	addq	-8(%rdi,%rsi,8), %rax
	addq	8(%rdi,%rsi,8), %rax
	ret
.LFE3:
	.size	sum_neighbors_opt, .-sum_neighbors_opt
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zR"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x1
	.byte	0x3
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB2
	.long	.LFE2-.LFB2
	.uleb128 0x0
	.align 8
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB3
	.long	.LFE3-.LFB3
	.uleb128 0x0
	.align 8
.LEFDE3:
	.ident	"GCC: (GNU) 4.3.5"
	.section	.note.GNU-stack,"",@progbits
