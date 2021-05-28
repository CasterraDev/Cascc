#Get it Up and Running
A very simple compiler that compiles simple equations into asm

This simple compiler gives you the correct answer for the equation and puts the assembly output into `out.s`
For the equation:
`2 + 8 * 5 - 10 / 2`
The assembly output will look like:
`	.text
.LC0:
	.string	"%d\n"
printint:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	ret

	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$2, %r8
	movq	$8, %r9
	movq	$5, %r10
	imulq	%r9, %r10
	addq	%r8, %r10
	movq	$10, %r8
	movq	$2, %r9
	movq	%r8,%rax
	cqo
	idivq	%r9
	movq	%rax,%r8
	subq	%r8, %r10
	movq	%r10, %rdi
	call	printint
	movl $0, %eax
	popq %rbp
	ret`
