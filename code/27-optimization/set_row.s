	.file	"set_row.c"
	.text
.globl set_row
	.type	set_row, @function
set_row:
.LFB2:
	testq	%rcx, %rcx
	jle	.L4
	movq	%rcx, %rax
	imulq	%rdx, %rax
	leaq	(%rdi,%rax,8), %rdx
	movl	$0, %r8d
.L3:
	movq	(%rsi,%r8,8), %rax
	movq	%rax, (%rdx)
	addq	$1, %r8
	addq	$8, %rdx
	cmpq	%r8, %rcx
	jg	.L3
.L4:
	rep
	ret
.LFE2:
	.size	set_row, .-set_row
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
	.ident	"GCC: (GNU) 4.3.5"
	.section	.note.GNU-stack,"",@progbits
