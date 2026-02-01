	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15, 4	sdk_version 10, 15, 4
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movl	$0, -4(%rbp)
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	L_.str.1(%rip), %rdi
	leaq	-8(%rbp), %rsi
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	leaq	L_.str.2(%rip), %rdi
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.1(%rip), %rdi
	leaq	-12(%rbp), %rsi
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	movss	-8(%rbp), %xmm0         ## xmm0 = mem[0],zero,zero,zero
	addss	-12(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	movss	-8(%rbp), %xmm0         ## xmm0 = mem[0],zero,zero,zero
	subss	-12(%rbp), %xmm0
	movss	%xmm0, -20(%rbp)
	movss	-8(%rbp), %xmm0         ## xmm0 = mem[0],zero,zero,zero
	mulss	-12(%rbp), %xmm0
	movss	%xmm0, -24(%rbp)
	leaq	L_.str.3(%rip), %rdi
	movl	%eax, -40(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movss	-8(%rbp), %xmm0         ## xmm0 = mem[0],zero,zero,zero
	cvtss2sd	%xmm0, %xmm0
	movss	-12(%rbp), %xmm1        ## xmm1 = mem[0],zero,zero,zero
	cvtss2sd	%xmm1, %xmm1
	movss	-16(%rbp), %xmm2        ## xmm2 = mem[0],zero,zero,zero
	cvtss2sd	%xmm2, %xmm2
	leaq	L_.str.4(%rip), %rdi
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	movb	$3, %al
	callq	_printf
	movss	-8(%rbp), %xmm0         ## xmm0 = mem[0],zero,zero,zero
	cvtss2sd	%xmm0, %xmm0
	movss	-12(%rbp), %xmm1        ## xmm1 = mem[0],zero,zero,zero
	cvtss2sd	%xmm1, %xmm1
	movss	-20(%rbp), %xmm2        ## xmm2 = mem[0],zero,zero,zero
	cvtss2sd	%xmm2, %xmm2
	leaq	L_.str.5(%rip), %rdi
	movl	%eax, -48(%rbp)         ## 4-byte Spill
	movb	$3, %al
	callq	_printf
	movss	-8(%rbp), %xmm0         ## xmm0 = mem[0],zero,zero,zero
	cvtss2sd	%xmm0, %xmm0
	movss	-12(%rbp), %xmm1        ## xmm1 = mem[0],zero,zero,zero
	cvtss2sd	%xmm1, %xmm1
	movss	-24(%rbp), %xmm2        ## xmm2 = mem[0],zero,zero,zero
	cvtss2sd	%xmm2, %xmm2
	leaq	L_.str.6(%rip), %rdi
	movl	%eax, -52(%rbp)         ## 4-byte Spill
	movb	$3, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -56(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Voer het eerste getal in: "

L_.str.1:                               ## @.str.1
	.asciz	"%f"

L_.str.2:                               ## @.str.2
	.asciz	"Voer het tweede getal in: "

L_.str.3:                               ## @.str.3
	.asciz	"\nResultaten:\n"

L_.str.4:                               ## @.str.4
	.asciz	"Som: %.2f + %.2f = %.2f\n"

L_.str.5:                               ## @.str.5
	.asciz	"Verschil: %.2f - %.2f = %.2f\n"

L_.str.6:                               ## @.str.6
	.asciz	"Product: %.2f * %.2f = %.2f\n"


.subsections_via_symbols
