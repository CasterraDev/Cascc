# Get it Up and Running

A very simple compiler that compiles simple equations into asm

This compiler can calculate the four basic operators `+`, `-`, `*`, and `/`.

It uses two functions to conform to the rules of PEMDAS.

In `expression.c`. There are two functions `multiplicativeExp()` and `addExp()`. `multiplicativeExp()` goes through the equation and looks for `*` and `/` and calculates the answer.

So `1 * 2 + 3 * 4` becames `2 + 12`

The `addExp()` then goes over the equation to get the final answer `14`.

## Basic Steps of a Compiler

There are 4 steps of a basic compiler

![Steps of a compiler](https://github.com/CasterraDev/Little-C/blob/main/Up-And-Running/basics-of-a-compiler.jpg)

+ [Lexical Scanning](https://en.wikipedia.org/wiki/Lexical_analysis): In many languages `=` is different from `==`, So you have to be sure to look ahead or else the file will be misread.

+ [Syntax Analysis](https://en.wikipedia.org/wiki/Parsing): Make sure the file conforms to the grammar of the language.

+ [Semantic Analysis](https://en.wikipedia.org/wiki/Semantic_analysis_(linguistics)): This is where it tries to understand what it is reading.

+ [Intermediate Code Generation](https://en.wikipedia.org/wiki/Code_generation_(compiler)): Translate the code into another language, generally a lower-level language from the starter one.

## Abstract Syntax Trees

Abstract Syntax Trees (ASTNodes) will be doing the semantic analysis. AST is going to make sure PEMDAS is used and the correct answer is calculated.

AST changes the understanding of the equation.

The Equation `1 * 2 + 3 * 4` should equal 14.

Without AST `Answer: 20`:
```
               *
	     /  \
	    /    \
	   /      \
         +         4
	/ \
       /   \
      /     \
    *        3
   / \
  /   \
 1     2
```

With AST `Answer: 14`:
```
         +
	/  \
       /    \
      /      \
    *          *
   / \        / \
  /   \     /    \
 1     2   3      4
```

## x86-64 Code Generator

I'm using registers in `cg.c` to translate c into assembly. Currently if their are no available registers the program will crash which I hopefully I will finish next version.

This simple compiler gives you the correct answer for the equation and puts the assembly output into `out.s`.

For the equation:

`2 + 8 * 5 - 10 / 2`

The assembly output will look like this:

```	.text
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
	ret
```
