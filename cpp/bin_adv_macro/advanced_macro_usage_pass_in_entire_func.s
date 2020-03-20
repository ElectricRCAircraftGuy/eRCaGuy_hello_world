	.file	"advanced_macro_usage_pass_in_entire_func.cpp"
	.text
.Ltext0:
	.globl	_ZN3ns13ns27my_funcEii
	.type	_ZN3ns13ns27my_funcEii, @function
_ZN3ns13ns27my_funcEii:
.LFB0:
	.file 1 "advanced_macro_usage_pass_in_entire_func.cpp"
	.loc 1 41 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	.loc 1 42 0
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	.loc 1 43 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN3ns13ns27my_funcEii, .-_ZN3ns13ns27my_funcEii
	.section	.rodata
.LC0:
	.string	"Hello World"
.LC1:
	.string	"i1 = %i; i2 = %i; i3 = %i\n"
.LC2:
	.string	"i4 = %i; i5 = %i; i6 = %i\n"
	.align 8
.LC3:
	.string	"hey, I'm a code block being passed into the macro!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.loc 1 49 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	.loc 1 49 0
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 50 0
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	.loc 1 52 0
	movl	$0, -32(%rbp)
	.loc 1 53 0
	movl	$0, -28(%rbp)
	.loc 1 54 0
	movl	$0, -24(%rbp)
	.loc 1 57 0
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	-24(%rbp), %ecx
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 58 0
	movl	-32(%rbp), %eax
	addl	$7, %eax
	movl	%eax, -32(%rbp)
	movl	-28(%rbp), %eax
	addl	$5, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	_ZN3ns13ns27my_funcEii
	movl	%eax, -24(%rbp)
	.loc 1 63 0
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	-24(%rbp), %ecx
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 66 0
	movl	-32(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	.loc 1 67 0
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	.loc 1 68 0
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	.loc 1 69 0
	movl	$10, %edi
	call	putchar@PLT
	.loc 1 70 0
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	-24(%rbp), %ecx
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 71 0
	movl	-12(%rbp), %ecx
	movl	-16(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 72 0
	movl	-32(%rbp), %eax
	addl	$7, %eax
	movl	%eax, -32(%rbp)
	movl	-28(%rbp), %eax
	addl	$5, %eax
	movl	%eax, -28(%rbp)
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	_ZN3ns13ns27my_funcEii
	movl	%eax, -24(%rbp)
	movl	-16(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	_ZN3ns13ns27my_funcEii
	movl	%eax, -12(%rbp)
	.loc 1 83 0
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	-24(%rbp), %ecx
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 84 0
	movl	-12(%rbp), %ecx
	movl	-16(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 87 0
	movl	$0, %eax
	.loc 1 88 0
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h"
	.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 4 "/usr/include/x86_64-linux-gnu/bits/libio.h"
	.file 5 "/usr/include/stdio.h"
	.file 6 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x3e1
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF832
	.byte	0x4
	.long	.LASF833
	.long	.LASF834
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.long	.Ldebug_macro0
	.uleb128 0x2
	.long	.LASF784
	.byte	0x2
	.byte	0xd8
	.long	0x3c
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF777
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF778
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF779
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF780
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF781
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF782
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF783
	.uleb128 0x2
	.long	.LASF785
	.byte	0x3
	.byte	0x8c
	.long	0x6d
	.uleb128 0x2
	.long	.LASF786
	.byte	0x3
	.byte	0x8d
	.long	0x6d
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0x92
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF787
	.uleb128 0x7
	.long	0x92
	.uleb128 0x8
	.long	.LASF817
	.byte	0xd8
	.byte	0x4
	.byte	0xf5
	.long	0x21e
	.uleb128 0x9
	.long	.LASF788
	.byte	0x4
	.byte	0xf6
	.long	0x66
	.byte	0
	.uleb128 0x9
	.long	.LASF789
	.byte	0x4
	.byte	0xfb
	.long	0x8c
	.byte	0x8
	.uleb128 0x9
	.long	.LASF790
	.byte	0x4
	.byte	0xfc
	.long	0x8c
	.byte	0x10
	.uleb128 0x9
	.long	.LASF791
	.byte	0x4
	.byte	0xfd
	.long	0x8c
	.byte	0x18
	.uleb128 0x9
	.long	.LASF792
	.byte	0x4
	.byte	0xfe
	.long	0x8c
	.byte	0x20
	.uleb128 0x9
	.long	.LASF793
	.byte	0x4
	.byte	0xff
	.long	0x8c
	.byte	0x28
	.uleb128 0xa
	.long	.LASF794
	.byte	0x4
	.value	0x100
	.long	0x8c
	.byte	0x30
	.uleb128 0xa
	.long	.LASF795
	.byte	0x4
	.value	0x101
	.long	0x8c
	.byte	0x38
	.uleb128 0xa
	.long	.LASF796
	.byte	0x4
	.value	0x102
	.long	0x8c
	.byte	0x40
	.uleb128 0xa
	.long	.LASF797
	.byte	0x4
	.value	0x104
	.long	0x8c
	.byte	0x48
	.uleb128 0xa
	.long	.LASF798
	.byte	0x4
	.value	0x105
	.long	0x8c
	.byte	0x50
	.uleb128 0xa
	.long	.LASF799
	.byte	0x4
	.value	0x106
	.long	0x8c
	.byte	0x58
	.uleb128 0xa
	.long	.LASF800
	.byte	0x4
	.value	0x108
	.long	0x256
	.byte	0x60
	.uleb128 0xa
	.long	.LASF801
	.byte	0x4
	.value	0x10a
	.long	0x25c
	.byte	0x68
	.uleb128 0xa
	.long	.LASF802
	.byte	0x4
	.value	0x10c
	.long	0x66
	.byte	0x70
	.uleb128 0xa
	.long	.LASF803
	.byte	0x4
	.value	0x110
	.long	0x66
	.byte	0x74
	.uleb128 0xa
	.long	.LASF804
	.byte	0x4
	.value	0x112
	.long	0x74
	.byte	0x78
	.uleb128 0xa
	.long	.LASF805
	.byte	0x4
	.value	0x116
	.long	0x4a
	.byte	0x80
	.uleb128 0xa
	.long	.LASF806
	.byte	0x4
	.value	0x117
	.long	0x58
	.byte	0x82
	.uleb128 0xa
	.long	.LASF807
	.byte	0x4
	.value	0x118
	.long	0x262
	.byte	0x83
	.uleb128 0xa
	.long	.LASF808
	.byte	0x4
	.value	0x11c
	.long	0x272
	.byte	0x88
	.uleb128 0xa
	.long	.LASF809
	.byte	0x4
	.value	0x125
	.long	0x7f
	.byte	0x90
	.uleb128 0xa
	.long	.LASF810
	.byte	0x4
	.value	0x12d
	.long	0x8a
	.byte	0x98
	.uleb128 0xa
	.long	.LASF811
	.byte	0x4
	.value	0x12e
	.long	0x8a
	.byte	0xa0
	.uleb128 0xa
	.long	.LASF812
	.byte	0x4
	.value	0x12f
	.long	0x8a
	.byte	0xa8
	.uleb128 0xa
	.long	.LASF813
	.byte	0x4
	.value	0x130
	.long	0x8a
	.byte	0xb0
	.uleb128 0xa
	.long	.LASF814
	.byte	0x4
	.value	0x132
	.long	0x31
	.byte	0xb8
	.uleb128 0xa
	.long	.LASF815
	.byte	0x4
	.value	0x133
	.long	0x66
	.byte	0xc0
	.uleb128 0xa
	.long	.LASF816
	.byte	0x4
	.value	0x135
	.long	0x278
	.byte	0xc4
	.byte	0
	.uleb128 0xb
	.long	.LASF835
	.byte	0x4
	.byte	0x9a
	.uleb128 0x8
	.long	.LASF818
	.byte	0x18
	.byte	0x4
	.byte	0xa0
	.long	0x256
	.uleb128 0x9
	.long	.LASF819
	.byte	0x4
	.byte	0xa1
	.long	0x256
	.byte	0
	.uleb128 0x9
	.long	.LASF820
	.byte	0x4
	.byte	0xa2
	.long	0x25c
	.byte	0x8
	.uleb128 0x9
	.long	.LASF821
	.byte	0x4
	.byte	0xa6
	.long	0x66
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x225
	.uleb128 0x6
	.byte	0x8
	.long	0x9e
	.uleb128 0xc
	.long	0x92
	.long	0x272
	.uleb128 0xd
	.long	0x3c
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x21e
	.uleb128 0xc
	.long	0x92
	.long	0x288
	.uleb128 0xd
	.long	0x3c
	.byte	0x13
	.byte	0
	.uleb128 0xe
	.long	.LASF836
	.uleb128 0xf
	.long	.LASF822
	.byte	0x4
	.value	0x13f
	.long	0x288
	.uleb128 0xf
	.long	.LASF823
	.byte	0x4
	.value	0x140
	.long	0x288
	.uleb128 0xf
	.long	.LASF824
	.byte	0x4
	.value	0x141
	.long	0x288
	.uleb128 0x6
	.byte	0x8
	.long	0x99
	.uleb128 0x7
	.long	0x2b1
	.uleb128 0x10
	.long	.LASF825
	.byte	0x5
	.byte	0x87
	.long	0x25c
	.uleb128 0x10
	.long	.LASF826
	.byte	0x5
	.byte	0x88
	.long	0x25c
	.uleb128 0x10
	.long	.LASF827
	.byte	0x5
	.byte	0x89
	.long	0x25c
	.uleb128 0x10
	.long	.LASF828
	.byte	0x6
	.byte	0x1a
	.long	0x66
	.uleb128 0xc
	.long	0x2b7
	.long	0x2f3
	.uleb128 0x11
	.byte	0
	.uleb128 0x10
	.long	.LASF829
	.byte	0x6
	.byte	0x1b
	.long	0x2e8
	.uleb128 0x10
	.long	.LASF830
	.byte	0x6
	.byte	0x1e
	.long	0x66
	.uleb128 0x10
	.long	.LASF831
	.byte	0x6
	.byte	0x1f
	.long	0x2e8
	.uleb128 0x12
	.long	.LASF837
	.byte	0x1
	.byte	0x30
	.long	0x66
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x384
	.uleb128 0x13
	.string	"i1"
	.byte	0x1
	.byte	0x34
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x13
	.string	"i2"
	.byte	0x1
	.byte	0x35
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x13
	.string	"i3"
	.byte	0x1
	.byte	0x36
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x13
	.string	"i4"
	.byte	0x1
	.byte	0x42
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x13
	.string	"i5"
	.byte	0x1
	.byte	0x43
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x13
	.string	"i6"
	.byte	0x1
	.byte	0x44
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x14
	.string	"ns1"
	.byte	0x1
	.byte	0x24
	.long	0x3b2
	.uleb128 0x15
	.string	"ns2"
	.byte	0x1
	.byte	0x26
	.uleb128 0x16
	.long	.LASF838
	.byte	0x1
	.byte	0x28
	.long	.LASF839
	.long	0x66
	.uleb128 0x17
	.long	0x66
	.uleb128 0x17
	.long	0x66
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x18
	.long	0x396
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x19
	.string	"i1"
	.byte	0x1
	.byte	0x28
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x19
	.string	"i2"
	.byte	0x1
	.byte	0x28
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.uleb128 0x2119
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x39
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x39
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_macro,"",@progbits
.Ldebug_macro0:
	.value	0x4
	.byte	0x2
	.long	.Ldebug_line0
	.byte	0x3
	.uleb128 0
	.uleb128 0x1
	.byte	0x5
	.uleb128 0x1
	.long	.LASF0
	.byte	0x5
	.uleb128 0x2
	.long	.LASF1
	.byte	0x5
	.uleb128 0x3
	.long	.LASF2
	.byte	0x5
	.uleb128 0x4
	.long	.LASF3
	.byte	0x5
	.uleb128 0x5
	.long	.LASF4
	.byte	0x5
	.uleb128 0x6
	.long	.LASF5
	.byte	0x5
	.uleb128 0x7
	.long	.LASF6
	.byte	0x5
	.uleb128 0x8
	.long	.LASF7
	.byte	0x5
	.uleb128 0x9
	.long	.LASF8
	.byte	0x5
	.uleb128 0xa
	.long	.LASF9
	.byte	0x5
	.uleb128 0xb
	.long	.LASF10
	.byte	0x5
	.uleb128 0xc
	.long	.LASF11
	.byte	0x5
	.uleb128 0xd
	.long	.LASF12
	.byte	0x5
	.uleb128 0xe
	.long	.LASF13
	.byte	0x5
	.uleb128 0xf
	.long	.LASF14
	.byte	0x5
	.uleb128 0x10
	.long	.LASF15
	.byte	0x5
	.uleb128 0x11
	.long	.LASF16
	.byte	0x5
	.uleb128 0x12
	.long	.LASF17
	.byte	0x5
	.uleb128 0x13
	.long	.LASF18
	.byte	0x5
	.uleb128 0x14
	.long	.LASF19
	.byte	0x5
	.uleb128 0x15
	.long	.LASF20
	.byte	0x5
	.uleb128 0x16
	.long	.LASF21
	.byte	0x5
	.uleb128 0x17
	.long	.LASF22
	.byte	0x5
	.uleb128 0x18
	.long	.LASF23
	.byte	0x5
	.uleb128 0x19
	.long	.LASF24
	.byte	0x5
	.uleb128 0x1a
	.long	.LASF25
	.byte	0x5
	.uleb128 0x1b
	.long	.LASF26
	.byte	0x5
	.uleb128 0x1c
	.long	.LASF27
	.byte	0x5
	.uleb128 0x1d
	.long	.LASF28
	.byte	0x5
	.uleb128 0x1e
	.long	.LASF29
	.byte	0x5
	.uleb128 0x1f
	.long	.LASF30
	.byte	0x5
	.uleb128 0x20
	.long	.LASF31
	.byte	0x5
	.uleb128 0x21
	.long	.LASF32
	.byte	0x5
	.uleb128 0x22
	.long	.LASF33
	.byte	0x5
	.uleb128 0x23
	.long	.LASF34
	.byte	0x5
	.uleb128 0x24
	.long	.LASF35
	.byte	0x5
	.uleb128 0x25
	.long	.LASF36
	.byte	0x5
	.uleb128 0x26
	.long	.LASF37
	.byte	0x5
	.uleb128 0x27
	.long	.LASF38
	.byte	0x5
	.uleb128 0x28
	.long	.LASF39
	.byte	0x5
	.uleb128 0x29
	.long	.LASF40
	.byte	0x5
	.uleb128 0x2a
	.long	.LASF41
	.byte	0x5
	.uleb128 0x2b
	.long	.LASF42
	.byte	0x5
	.uleb128 0x2c
	.long	.LASF43
	.byte	0x5
	.uleb128 0x2d
	.long	.LASF44
	.byte	0x5
	.uleb128 0x2e
	.long	.LASF45
	.byte	0x5
	.uleb128 0x2f
	.long	.LASF46
	.byte	0x5
	.uleb128 0x30
	.long	.LASF47
	.byte	0x5
	.uleb128 0x31
	.long	.LASF48
	.byte	0x5
	.uleb128 0x32
	.long	.LASF49
	.byte	0x5
	.uleb128 0x33
	.long	.LASF50
	.byte	0x5
	.uleb128 0x34
	.long	.LASF51
	.byte	0x5
	.uleb128 0x35
	.long	.LASF52
	.byte	0x5
	.uleb128 0x36
	.long	.LASF53
	.byte	0x5
	.uleb128 0x37
	.long	.LASF54
	.byte	0x5
	.uleb128 0x38
	.long	.LASF55
	.byte	0x5
	.uleb128 0x39
	.long	.LASF56
	.byte	0x5
	.uleb128 0x3a
	.long	.LASF57
	.byte	0x5
	.uleb128 0x3b
	.long	.LASF58
	.byte	0x5
	.uleb128 0x3c
	.long	.LASF59
	.byte	0x5
	.uleb128 0x3d
	.long	.LASF60
	.byte	0x5
	.uleb128 0x3e
	.long	.LASF61
	.byte	0x5
	.uleb128 0x3f
	.long	.LASF62
	.byte	0x5
	.uleb128 0x40
	.long	.LASF63
	.byte	0x5
	.uleb128 0x41
	.long	.LASF64
	.byte	0x5
	.uleb128 0x42
	.long	.LASF65
	.byte	0x5
	.uleb128 0x43
	.long	.LASF66
	.byte	0x5
	.uleb128 0x44
	.long	.LASF67
	.byte	0x5
	.uleb128 0x45
	.long	.LASF68
	.byte	0x5
	.uleb128 0x46
	.long	.LASF69
	.byte	0x5
	.uleb128 0x47
	.long	.LASF70
	.byte	0x5
	.uleb128 0x48
	.long	.LASF71
	.byte	0x5
	.uleb128 0x49
	.long	.LASF72
	.byte	0x5
	.uleb128 0x4a
	.long	.LASF73
	.byte	0x5
	.uleb128 0x4b
	.long	.LASF74
	.byte	0x5
	.uleb128 0x4c
	.long	.LASF75
	.byte	0x5
	.uleb128 0x4d
	.long	.LASF76
	.byte	0x5
	.uleb128 0x4e
	.long	.LASF77
	.byte	0x5
	.uleb128 0x4f
	.long	.LASF78
	.byte	0x5
	.uleb128 0x50
	.long	.LASF79
	.byte	0x5
	.uleb128 0x51
	.long	.LASF80
	.byte	0x5
	.uleb128 0x52
	.long	.LASF81
	.byte	0x5
	.uleb128 0x53
	.long	.LASF82
	.byte	0x5
	.uleb128 0x54
	.long	.LASF83
	.byte	0x5
	.uleb128 0x55
	.long	.LASF84
	.byte	0x5
	.uleb128 0x56
	.long	.LASF85
	.byte	0x5
	.uleb128 0x57
	.long	.LASF86
	.byte	0x5
	.uleb128 0x58
	.long	.LASF87
	.byte	0x5
	.uleb128 0x59
	.long	.LASF88
	.byte	0x5
	.uleb128 0x5a
	.long	.LASF89
	.byte	0x5
	.uleb128 0x5b
	.long	.LASF90
	.byte	0x5
	.uleb128 0x5c
	.long	.LASF91
	.byte	0x5
	.uleb128 0x5d
	.long	.LASF92
	.byte	0x5
	.uleb128 0x5e
	.long	.LASF93
	.byte	0x5
	.uleb128 0x5f
	.long	.LASF94
	.byte	0x5
	.uleb128 0x60
	.long	.LASF95
	.byte	0x5
	.uleb128 0x61
	.long	.LASF96
	.byte	0x5
	.uleb128 0x62
	.long	.LASF97
	.byte	0x5
	.uleb128 0x63
	.long	.LASF98
	.byte	0x5
	.uleb128 0x64
	.long	.LASF99
	.byte	0x5
	.uleb128 0x65
	.long	.LASF100
	.byte	0x5
	.uleb128 0x66
	.long	.LASF101
	.byte	0x5
	.uleb128 0x67
	.long	.LASF102
	.byte	0x5
	.uleb128 0x68
	.long	.LASF103
	.byte	0x5
	.uleb128 0x69
	.long	.LASF104
	.byte	0x5
	.uleb128 0x6a
	.long	.LASF105
	.byte	0x5
	.uleb128 0x6b
	.long	.LASF106
	.byte	0x5
	.uleb128 0x6c
	.long	.LASF107
	.byte	0x5
	.uleb128 0x6d
	.long	.LASF108
	.byte	0x5
	.uleb128 0x6e
	.long	.LASF109
	.byte	0x5
	.uleb128 0x6f
	.long	.LASF110
	.byte	0x5
	.uleb128 0x70
	.long	.LASF111
	.byte	0x5
	.uleb128 0x71
	.long	.LASF112
	.byte	0x5
	.uleb128 0x72
	.long	.LASF113
	.byte	0x5
	.uleb128 0x73
	.long	.LASF114
	.byte	0x5
	.uleb128 0x74
	.long	.LASF115
	.byte	0x5
	.uleb128 0x75
	.long	.LASF116
	.byte	0x5
	.uleb128 0x76
	.long	.LASF117
	.byte	0x5
	.uleb128 0x77
	.long	.LASF118
	.byte	0x5
	.uleb128 0x78
	.long	.LASF119
	.byte	0x5
	.uleb128 0x79
	.long	.LASF120
	.byte	0x5
	.uleb128 0x7a
	.long	.LASF121
	.byte	0x5
	.uleb128 0x7b
	.long	.LASF122
	.byte	0x5
	.uleb128 0x7c
	.long	.LASF123
	.byte	0x5
	.uleb128 0x7d
	.long	.LASF124
	.byte	0x5
	.uleb128 0x7e
	.long	.LASF125
	.byte	0x5
	.uleb128 0x7f
	.long	.LASF126
	.byte	0x5
	.uleb128 0x80
	.long	.LASF127
	.byte	0x5
	.uleb128 0x81
	.long	.LASF128
	.byte	0x5
	.uleb128 0x82
	.long	.LASF129
	.byte	0x5
	.uleb128 0x83
	.long	.LASF130
	.byte	0x5
	.uleb128 0x84
	.long	.LASF131
	.byte	0x5
	.uleb128 0x85
	.long	.LASF132
	.byte	0x5
	.uleb128 0x86
	.long	.LASF133
	.byte	0x5
	.uleb128 0x87
	.long	.LASF134
	.byte	0x5
	.uleb128 0x88
	.long	.LASF135
	.byte	0x5
	.uleb128 0x89
	.long	.LASF136
	.byte	0x5
	.uleb128 0x8a
	.long	.LASF137
	.byte	0x5
	.uleb128 0x8b
	.long	.LASF138
	.byte	0x5
	.uleb128 0x8c
	.long	.LASF139
	.byte	0x5
	.uleb128 0x8d
	.long	.LASF140
	.byte	0x5
	.uleb128 0x8e
	.long	.LASF141
	.byte	0x5
	.uleb128 0x8f
	.long	.LASF142
	.byte	0x5
	.uleb128 0x90
	.long	.LASF143
	.byte	0x5
	.uleb128 0x91
	.long	.LASF144
	.byte	0x5
	.uleb128 0x92
	.long	.LASF145
	.byte	0x5
	.uleb128 0x93
	.long	.LASF146
	.byte	0x5
	.uleb128 0x94
	.long	.LASF147
	.byte	0x5
	.uleb128 0x95
	.long	.LASF148
	.byte	0x5
	.uleb128 0x96
	.long	.LASF149
	.byte	0x5
	.uleb128 0x97
	.long	.LASF150
	.byte	0x5
	.uleb128 0x98
	.long	.LASF151
	.byte	0x5
	.uleb128 0x99
	.long	.LASF152
	.byte	0x5
	.uleb128 0x9a
	.long	.LASF153
	.byte	0x5
	.uleb128 0x9b
	.long	.LASF154
	.byte	0x5
	.uleb128 0x9c
	.long	.LASF155
	.byte	0x5
	.uleb128 0x9d
	.long	.LASF156
	.byte	0x5
	.uleb128 0x9e
	.long	.LASF157
	.byte	0x5
	.uleb128 0x9f
	.long	.LASF158
	.byte	0x5
	.uleb128 0xa0
	.long	.LASF159
	.byte	0x5
	.uleb128 0xa1
	.long	.LASF160
	.byte	0x5
	.uleb128 0xa2
	.long	.LASF161
	.byte	0x5
	.uleb128 0xa3
	.long	.LASF162
	.byte	0x5
	.uleb128 0xa4
	.long	.LASF163
	.byte	0x5
	.uleb128 0xa5
	.long	.LASF164
	.byte	0x5
	.uleb128 0xa6
	.long	.LASF165
	.byte	0x5
	.uleb128 0xa7
	.long	.LASF166
	.byte	0x5
	.uleb128 0xa8
	.long	.LASF167
	.byte	0x5
	.uleb128 0xa9
	.long	.LASF168
	.byte	0x5
	.uleb128 0xaa
	.long	.LASF169
	.byte	0x5
	.uleb128 0xab
	.long	.LASF170
	.byte	0x5
	.uleb128 0xac
	.long	.LASF171
	.byte	0x5
	.uleb128 0xad
	.long	.LASF172
	.byte	0x5
	.uleb128 0xae
	.long	.LASF173
	.byte	0x5
	.uleb128 0xaf
	.long	.LASF174
	.byte	0x5
	.uleb128 0xb0
	.long	.LASF175
	.byte	0x5
	.uleb128 0xb1
	.long	.LASF176
	.byte	0x5
	.uleb128 0xb2
	.long	.LASF177
	.byte	0x5
	.uleb128 0xb3
	.long	.LASF178
	.byte	0x5
	.uleb128 0xb4
	.long	.LASF179
	.byte	0x5
	.uleb128 0xb5
	.long	.LASF180
	.byte	0x5
	.uleb128 0xb6
	.long	.LASF181
	.byte	0x5
	.uleb128 0xb7
	.long	.LASF182
	.byte	0x5
	.uleb128 0xb8
	.long	.LASF183
	.byte	0x5
	.uleb128 0xb9
	.long	.LASF184
	.byte	0x5
	.uleb128 0xba
	.long	.LASF185
	.byte	0x5
	.uleb128 0xbb
	.long	.LASF186
	.byte	0x5
	.uleb128 0xbc
	.long	.LASF187
	.byte	0x5
	.uleb128 0xbd
	.long	.LASF188
	.byte	0x5
	.uleb128 0xbe
	.long	.LASF189
	.byte	0x5
	.uleb128 0xbf
	.long	.LASF190
	.byte	0x5
	.uleb128 0xc0
	.long	.LASF191
	.byte	0x5
	.uleb128 0xc1
	.long	.LASF192
	.byte	0x5
	.uleb128 0xc2
	.long	.LASF193
	.byte	0x5
	.uleb128 0xc3
	.long	.LASF194
	.byte	0x5
	.uleb128 0xc4
	.long	.LASF195
	.byte	0x5
	.uleb128 0xc5
	.long	.LASF196
	.byte	0x5
	.uleb128 0xc6
	.long	.LASF197
	.byte	0x5
	.uleb128 0xc7
	.long	.LASF198
	.byte	0x5
	.uleb128 0xc8
	.long	.LASF199
	.byte	0x5
	.uleb128 0xc9
	.long	.LASF200
	.byte	0x5
	.uleb128 0xca
	.long	.LASF201
	.byte	0x5
	.uleb128 0xcb
	.long	.LASF202
	.byte	0x5
	.uleb128 0xcc
	.long	.LASF203
	.byte	0x5
	.uleb128 0xcd
	.long	.LASF204
	.byte	0x5
	.uleb128 0xce
	.long	.LASF205
	.byte	0x5
	.uleb128 0xcf
	.long	.LASF206
	.byte	0x5
	.uleb128 0xd0
	.long	.LASF207
	.byte	0x5
	.uleb128 0xd1
	.long	.LASF208
	.byte	0x5
	.uleb128 0xd2
	.long	.LASF209
	.byte	0x5
	.uleb128 0xd3
	.long	.LASF210
	.byte	0x5
	.uleb128 0xd4
	.long	.LASF211
	.byte	0x5
	.uleb128 0xd5
	.long	.LASF212
	.byte	0x5
	.uleb128 0xd6
	.long	.LASF213
	.byte	0x5
	.uleb128 0xd7
	.long	.LASF214
	.byte	0x5
	.uleb128 0xd8
	.long	.LASF215
	.byte	0x5
	.uleb128 0xd9
	.long	.LASF216
	.byte	0x5
	.uleb128 0xda
	.long	.LASF217
	.byte	0x5
	.uleb128 0xdb
	.long	.LASF218
	.byte	0x5
	.uleb128 0xdc
	.long	.LASF219
	.byte	0x5
	.uleb128 0xdd
	.long	.LASF220
	.byte	0x5
	.uleb128 0xde
	.long	.LASF221
	.byte	0x5
	.uleb128 0xdf
	.long	.LASF222
	.byte	0x5
	.uleb128 0xe0
	.long	.LASF223
	.byte	0x5
	.uleb128 0xe1
	.long	.LASF224
	.byte	0x5
	.uleb128 0xe2
	.long	.LASF225
	.byte	0x5
	.uleb128 0xe3
	.long	.LASF226
	.byte	0x5
	.uleb128 0xe4
	.long	.LASF227
	.byte	0x5
	.uleb128 0xe5
	.long	.LASF228
	.byte	0x5
	.uleb128 0xe6
	.long	.LASF229
	.byte	0x5
	.uleb128 0xe7
	.long	.LASF230
	.byte	0x5
	.uleb128 0xe8
	.long	.LASF231
	.byte	0x5
	.uleb128 0xe9
	.long	.LASF232
	.byte	0x5
	.uleb128 0xea
	.long	.LASF233
	.byte	0x5
	.uleb128 0xeb
	.long	.LASF234
	.byte	0x5
	.uleb128 0xec
	.long	.LASF235
	.byte	0x5
	.uleb128 0xed
	.long	.LASF236
	.byte	0x5
	.uleb128 0xee
	.long	.LASF237
	.byte	0x5
	.uleb128 0xef
	.long	.LASF238
	.byte	0x5
	.uleb128 0xf0
	.long	.LASF239
	.byte	0x5
	.uleb128 0xf1
	.long	.LASF240
	.byte	0x5
	.uleb128 0xf2
	.long	.LASF241
	.byte	0x5
	.uleb128 0xf3
	.long	.LASF242
	.byte	0x5
	.uleb128 0xf4
	.long	.LASF243
	.byte	0x5
	.uleb128 0xf5
	.long	.LASF244
	.byte	0x5
	.uleb128 0xf6
	.long	.LASF245
	.byte	0x5
	.uleb128 0xf7
	.long	.LASF246
	.byte	0x5
	.uleb128 0xf8
	.long	.LASF247
	.byte	0x5
	.uleb128 0xf9
	.long	.LASF248
	.byte	0x5
	.uleb128 0xfa
	.long	.LASF249
	.byte	0x5
	.uleb128 0xfb
	.long	.LASF250
	.byte	0x5
	.uleb128 0xfc
	.long	.LASF251
	.byte	0x5
	.uleb128 0xfd
	.long	.LASF252
	.byte	0x5
	.uleb128 0xfe
	.long	.LASF253
	.byte	0x5
	.uleb128 0xff
	.long	.LASF254
	.byte	0x5
	.uleb128 0x100
	.long	.LASF255
	.byte	0x5
	.uleb128 0x101
	.long	.LASF256
	.byte	0x5
	.uleb128 0x102
	.long	.LASF257
	.byte	0x5
	.uleb128 0x103
	.long	.LASF258
	.byte	0x5
	.uleb128 0x104
	.long	.LASF259
	.byte	0x5
	.uleb128 0x105
	.long	.LASF260
	.byte	0x5
	.uleb128 0x106
	.long	.LASF261
	.byte	0x5
	.uleb128 0x107
	.long	.LASF262
	.byte	0x5
	.uleb128 0x108
	.long	.LASF263
	.byte	0x5
	.uleb128 0x109
	.long	.LASF264
	.byte	0x5
	.uleb128 0x10a
	.long	.LASF265
	.byte	0x5
	.uleb128 0x10b
	.long	.LASF266
	.byte	0x5
	.uleb128 0x10c
	.long	.LASF267
	.byte	0x5
	.uleb128 0x10d
	.long	.LASF268
	.byte	0x5
	.uleb128 0x10e
	.long	.LASF269
	.byte	0x5
	.uleb128 0x10f
	.long	.LASF270
	.byte	0x5
	.uleb128 0x110
	.long	.LASF271
	.byte	0x5
	.uleb128 0x111
	.long	.LASF272
	.byte	0x5
	.uleb128 0x112
	.long	.LASF273
	.byte	0x5
	.uleb128 0x113
	.long	.LASF274
	.byte	0x5
	.uleb128 0x114
	.long	.LASF275
	.byte	0x5
	.uleb128 0x115
	.long	.LASF276
	.byte	0x5
	.uleb128 0x116
	.long	.LASF277
	.byte	0x5
	.uleb128 0x117
	.long	.LASF278
	.byte	0x5
	.uleb128 0x118
	.long	.LASF279
	.byte	0x5
	.uleb128 0x119
	.long	.LASF280
	.byte	0x5
	.uleb128 0x11a
	.long	.LASF281
	.byte	0x5
	.uleb128 0x11b
	.long	.LASF282
	.byte	0x5
	.uleb128 0x11c
	.long	.LASF283
	.byte	0x5
	.uleb128 0x11d
	.long	.LASF284
	.byte	0x5
	.uleb128 0x11e
	.long	.LASF285
	.byte	0x5
	.uleb128 0x11f
	.long	.LASF286
	.byte	0x5
	.uleb128 0x120
	.long	.LASF287
	.byte	0x5
	.uleb128 0x121
	.long	.LASF288
	.byte	0x5
	.uleb128 0x122
	.long	.LASF289
	.byte	0x5
	.uleb128 0x123
	.long	.LASF290
	.byte	0x5
	.uleb128 0x124
	.long	.LASF291
	.byte	0x5
	.uleb128 0x125
	.long	.LASF292
	.byte	0x5
	.uleb128 0x126
	.long	.LASF293
	.byte	0x5
	.uleb128 0x127
	.long	.LASF294
	.byte	0x5
	.uleb128 0x128
	.long	.LASF295
	.byte	0x5
	.uleb128 0x129
	.long	.LASF296
	.byte	0x5
	.uleb128 0x12a
	.long	.LASF297
	.byte	0x5
	.uleb128 0x12b
	.long	.LASF298
	.byte	0x5
	.uleb128 0x12c
	.long	.LASF299
	.byte	0x5
	.uleb128 0x12d
	.long	.LASF300
	.byte	0x5
	.uleb128 0x12e
	.long	.LASF301
	.byte	0x5
	.uleb128 0x12f
	.long	.LASF302
	.byte	0x5
	.uleb128 0x130
	.long	.LASF303
	.byte	0x5
	.uleb128 0x131
	.long	.LASF304
	.byte	0x5
	.uleb128 0x132
	.long	.LASF305
	.byte	0x5
	.uleb128 0x133
	.long	.LASF306
	.byte	0x5
	.uleb128 0x134
	.long	.LASF307
	.byte	0x5
	.uleb128 0x135
	.long	.LASF308
	.byte	0x5
	.uleb128 0x136
	.long	.LASF309
	.byte	0x5
	.uleb128 0x137
	.long	.LASF310
	.byte	0x5
	.uleb128 0x138
	.long	.LASF311
	.byte	0x5
	.uleb128 0x139
	.long	.LASF312
	.byte	0x5
	.uleb128 0x13a
	.long	.LASF313
	.byte	0x5
	.uleb128 0x13b
	.long	.LASF314
	.byte	0x5
	.uleb128 0x13c
	.long	.LASF315
	.byte	0x5
	.uleb128 0x13d
	.long	.LASF316
	.byte	0x5
	.uleb128 0x13e
	.long	.LASF317
	.byte	0x5
	.uleb128 0x13f
	.long	.LASF318
	.byte	0x5
	.uleb128 0x140
	.long	.LASF319
	.byte	0x5
	.uleb128 0x141
	.long	.LASF320
	.byte	0x5
	.uleb128 0x142
	.long	.LASF321
	.byte	0x5
	.uleb128 0x143
	.long	.LASF322
	.byte	0x5
	.uleb128 0x144
	.long	.LASF323
	.byte	0x5
	.uleb128 0x145
	.long	.LASF324
	.byte	0x5
	.uleb128 0x146
	.long	.LASF325
	.byte	0x5
	.uleb128 0x147
	.long	.LASF326
	.byte	0x5
	.uleb128 0x148
	.long	.LASF327
	.byte	0x5
	.uleb128 0x149
	.long	.LASF328
	.byte	0x5
	.uleb128 0x14a
	.long	.LASF329
	.byte	0x5
	.uleb128 0x14b
	.long	.LASF330
	.byte	0x5
	.uleb128 0x14c
	.long	.LASF331
	.byte	0x5
	.uleb128 0x14d
	.long	.LASF332
	.byte	0x5
	.uleb128 0x14e
	.long	.LASF333
	.byte	0x5
	.uleb128 0x14f
	.long	.LASF334
	.byte	0x5
	.uleb128 0x150
	.long	.LASF335
	.byte	0x5
	.uleb128 0x151
	.long	.LASF336
	.byte	0x5
	.uleb128 0x152
	.long	.LASF337
	.byte	0x5
	.uleb128 0x153
	.long	.LASF338
	.byte	0x5
	.uleb128 0x154
	.long	.LASF339
	.byte	0x5
	.uleb128 0x155
	.long	.LASF340
	.byte	0x5
	.uleb128 0x156
	.long	.LASF341
	.byte	0x5
	.uleb128 0x157
	.long	.LASF342
	.byte	0x5
	.uleb128 0x158
	.long	.LASF343
	.byte	0x5
	.uleb128 0x159
	.long	.LASF344
	.byte	0x5
	.uleb128 0x15a
	.long	.LASF345
	.byte	0x5
	.uleb128 0x15b
	.long	.LASF346
	.byte	0x5
	.uleb128 0x15c
	.long	.LASF347
	.byte	0x5
	.uleb128 0x15d
	.long	.LASF348
	.byte	0x5
	.uleb128 0x15e
	.long	.LASF349
	.byte	0x5
	.uleb128 0x15f
	.long	.LASF350
	.byte	0x5
	.uleb128 0x160
	.long	.LASF351
	.byte	0x5
	.uleb128 0x161
	.long	.LASF352
	.byte	0x5
	.uleb128 0x162
	.long	.LASF353
	.byte	0x5
	.uleb128 0x163
	.long	.LASF354
	.byte	0x5
	.uleb128 0x164
	.long	.LASF355
	.byte	0x5
	.uleb128 0x165
	.long	.LASF356
	.byte	0x5
	.uleb128 0x166
	.long	.LASF357
	.byte	0x5
	.uleb128 0x167
	.long	.LASF358
	.byte	0x5
	.uleb128 0x168
	.long	.LASF359
	.byte	0x5
	.uleb128 0x169
	.long	.LASF360
	.byte	0x5
	.uleb128 0x16a
	.long	.LASF361
	.byte	0x5
	.uleb128 0x16b
	.long	.LASF362
	.byte	0x5
	.uleb128 0x16c
	.long	.LASF363
	.byte	0x5
	.uleb128 0x16d
	.long	.LASF364
	.byte	0x5
	.uleb128 0x16e
	.long	.LASF365
	.byte	0x5
	.uleb128 0x16f
	.long	.LASF366
	.byte	0x5
	.uleb128 0x170
	.long	.LASF367
	.byte	0x5
	.uleb128 0x171
	.long	.LASF368
	.byte	0x5
	.uleb128 0x172
	.long	.LASF369
	.byte	0x5
	.uleb128 0x173
	.long	.LASF370
	.byte	0x5
	.uleb128 0x174
	.long	.LASF371
	.byte	0x5
	.uleb128 0x175
	.long	.LASF372
	.byte	0x5
	.uleb128 0x176
	.long	.LASF373
	.byte	0x5
	.uleb128 0x177
	.long	.LASF374
	.byte	0x5
	.uleb128 0x178
	.long	.LASF375
	.byte	0x5
	.uleb128 0x179
	.long	.LASF376
	.byte	0x5
	.uleb128 0x17a
	.long	.LASF377
	.byte	0x5
	.uleb128 0x17b
	.long	.LASF378
	.byte	0x5
	.uleb128 0x17c
	.long	.LASF379
	.byte	0x5
	.uleb128 0x17d
	.long	.LASF380
	.byte	0x5
	.uleb128 0x17e
	.long	.LASF381
	.byte	0x5
	.uleb128 0x17f
	.long	.LASF382
	.byte	0x5
	.uleb128 0x180
	.long	.LASF383
	.byte	0x5
	.uleb128 0x181
	.long	.LASF384
	.byte	0x5
	.uleb128 0x182
	.long	.LASF385
	.byte	0x5
	.uleb128 0x183
	.long	.LASF386
	.byte	0x5
	.uleb128 0x184
	.long	.LASF387
	.byte	0x5
	.uleb128 0x185
	.long	.LASF388
	.byte	0x5
	.uleb128 0x186
	.long	.LASF389
	.byte	0x5
	.uleb128 0x187
	.long	.LASF390
	.byte	0x5
	.uleb128 0x188
	.long	.LASF391
	.byte	0x5
	.uleb128 0x189
	.long	.LASF392
	.byte	0x5
	.uleb128 0x18a
	.long	.LASF393
	.byte	0x5
	.uleb128 0x18b
	.long	.LASF394
	.byte	0x5
	.uleb128 0x18c
	.long	.LASF395
	.byte	0x5
	.uleb128 0x18d
	.long	.LASF396
	.byte	0x5
	.uleb128 0x1
	.long	.LASF397
	.file 7 "/usr/include/stdc-predef.h"
	.byte	0x3
	.uleb128 0x2
	.uleb128 0x7
	.byte	0x7
	.long	.Ldebug_macro1
	.byte	0x4
	.byte	0x3
	.uleb128 0x19
	.uleb128 0x5
	.byte	0x7
	.long	.Ldebug_macro2
	.file 8 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h"
	.byte	0x3
	.uleb128 0x1b
	.uleb128 0x8
	.byte	0x6
	.uleb128 0x1f
	.long	.LASF405
	.file 9 "/usr/include/features.h"
	.byte	0x3
	.uleb128 0x21
	.uleb128 0x9
	.byte	0x7
	.long	.Ldebug_macro3
	.file 10 "/usr/include/x86_64-linux-gnu/sys/cdefs.h"
	.byte	0x3
	.uleb128 0x1a8
	.uleb128 0xa
	.byte	0x7
	.long	.Ldebug_macro4
	.file 11 "/usr/include/x86_64-linux-gnu/bits/wordsize.h"
	.byte	0x3
	.uleb128 0x1ab
	.uleb128 0xb
	.byte	0x7
	.long	.Ldebug_macro5
	.byte	0x4
	.file 12 "/usr/include/x86_64-linux-gnu/bits/long-double.h"
	.byte	0x3
	.uleb128 0x1ac
	.uleb128 0xc
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro6
	.byte	0x4
	.file 13 "/usr/include/x86_64-linux-gnu/gnu/stubs.h"
	.byte	0x3
	.uleb128 0x1c0
	.uleb128 0xd
	.file 14 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h"
	.byte	0x3
	.uleb128 0xa
	.uleb128 0xe
	.byte	0x7
	.long	.Ldebug_macro7
	.byte	0x4
	.byte	0x4
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro8
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro9
	.byte	0x3
	.uleb128 0x21
	.uleb128 0x2
	.byte	0x7
	.long	.Ldebug_macro10
	.byte	0x4
	.byte	0x3
	.uleb128 0x23
	.uleb128 0x3
	.byte	0x5
	.uleb128 0x18
	.long	.LASF595
	.byte	0x3
	.uleb128 0x1b
	.uleb128 0xb
	.byte	0x7
	.long	.Ldebug_macro5
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro11
	.file 15 "/usr/include/x86_64-linux-gnu/bits/typesizes.h"
	.byte	0x3
	.uleb128 0x82
	.uleb128 0xf
	.byte	0x7
	.long	.Ldebug_macro12
	.byte	0x4
	.byte	0x6
	.uleb128 0xcc
	.long	.LASF650
	.byte	0x4
	.file 16 "/usr/include/x86_64-linux-gnu/bits/types/__FILE.h"
	.byte	0x3
	.uleb128 0x24
	.uleb128 0x10
	.byte	0x5
	.uleb128 0x2
	.long	.LASF651
	.byte	0x4
	.file 17 "/usr/include/x86_64-linux-gnu/bits/types/FILE.h"
	.byte	0x3
	.uleb128 0x25
	.uleb128 0x11
	.byte	0x5
	.uleb128 0x2
	.long	.LASF652
	.byte	0x4
	.byte	0x5
	.uleb128 0x27
	.long	.LASF653
	.byte	0x3
	.uleb128 0x29
	.uleb128 0x4
	.byte	0x5
	.uleb128 0x1d
	.long	.LASF654
	.file 18 "/usr/include/x86_64-linux-gnu/bits/_G_config.h"
	.byte	0x3
	.uleb128 0x23
	.uleb128 0x12
	.byte	0x7
	.long	.Ldebug_macro13
	.byte	0x3
	.uleb128 0x13
	.uleb128 0x2
	.byte	0x7
	.long	.Ldebug_macro14
	.byte	0x4
	.file 19 "/usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h"
	.byte	0x3
	.uleb128 0x15
	.uleb128 0x13
	.byte	0x5
	.uleb128 0x2
	.long	.LASF656
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro15
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro16
	.file 20 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h"
	.byte	0x3
	.uleb128 0x35
	.uleb128 0x14
	.byte	0x7
	.long	.Ldebug_macro17
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro18
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro19
	.file 21 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h"
	.byte	0x3
	.uleb128 0x83
	.uleb128 0x15
	.byte	0x7
	.long	.Ldebug_macro20
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro21
	.byte	0x3
	.uleb128 0x30d
	.uleb128 0x6
	.byte	0x4
	.byte	0x4
	.byte	0x5
	.uleb128 0x1b
	.long	.LASF776
	.byte	0x4
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdcpredef.h.19.006d14bbbe0dc07ba9b1ce3fdc8e40d3,comdat
.Ldebug_macro1:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x13
	.long	.LASF398
	.byte	0x5
	.uleb128 0x26
	.long	.LASF399
	.byte	0x5
	.uleb128 0x2e
	.long	.LASF400
	.byte	0x5
	.uleb128 0x3a
	.long	.LASF401
	.byte	0x5
	.uleb128 0x3d
	.long	.LASF402
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdio.h.24.5c1b97eef3c86b7a2549420f69f4f128,comdat
.Ldebug_macro2:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x18
	.long	.LASF403
	.byte	0x5
	.uleb128 0x1a
	.long	.LASF404
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.features.h.19.fcbbd60f008424b1aa85bde6e4f4660c,comdat
.Ldebug_macro3:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x13
	.long	.LASF406
	.byte	0x6
	.uleb128 0x77
	.long	.LASF407
	.byte	0x6
	.uleb128 0x78
	.long	.LASF408
	.byte	0x6
	.uleb128 0x79
	.long	.LASF409
	.byte	0x6
	.uleb128 0x7a
	.long	.LASF410
	.byte	0x6
	.uleb128 0x7b
	.long	.LASF411
	.byte	0x6
	.uleb128 0x7c
	.long	.LASF412
	.byte	0x6
	.uleb128 0x7d
	.long	.LASF413
	.byte	0x6
	.uleb128 0x7e
	.long	.LASF414
	.byte	0x6
	.uleb128 0x7f
	.long	.LASF415
	.byte	0x6
	.uleb128 0x80
	.long	.LASF416
	.byte	0x6
	.uleb128 0x81
	.long	.LASF417
	.byte	0x6
	.uleb128 0x82
	.long	.LASF418
	.byte	0x6
	.uleb128 0x83
	.long	.LASF419
	.byte	0x6
	.uleb128 0x84
	.long	.LASF420
	.byte	0x6
	.uleb128 0x85
	.long	.LASF421
	.byte	0x6
	.uleb128 0x86
	.long	.LASF422
	.byte	0x6
	.uleb128 0x87
	.long	.LASF423
	.byte	0x6
	.uleb128 0x88
	.long	.LASF424
	.byte	0x6
	.uleb128 0x89
	.long	.LASF425
	.byte	0x6
	.uleb128 0x8a
	.long	.LASF426
	.byte	0x6
	.uleb128 0x8b
	.long	.LASF427
	.byte	0x6
	.uleb128 0x8c
	.long	.LASF428
	.byte	0x6
	.uleb128 0x8d
	.long	.LASF429
	.byte	0x6
	.uleb128 0x8e
	.long	.LASF430
	.byte	0x5
	.uleb128 0x93
	.long	.LASF431
	.byte	0x5
	.uleb128 0x9e
	.long	.LASF432
	.byte	0x5
	.uleb128 0xac
	.long	.LASF433
	.byte	0x5
	.uleb128 0xb0
	.long	.LASF434
	.byte	0x6
	.uleb128 0xbf
	.long	.LASF435
	.byte	0x5
	.uleb128 0xc0
	.long	.LASF436
	.byte	0x6
	.uleb128 0xc1
	.long	.LASF437
	.byte	0x5
	.uleb128 0xc2
	.long	.LASF438
	.byte	0x6
	.uleb128 0xc3
	.long	.LASF439
	.byte	0x5
	.uleb128 0xc4
	.long	.LASF440
	.byte	0x6
	.uleb128 0xc5
	.long	.LASF441
	.byte	0x5
	.uleb128 0xc6
	.long	.LASF442
	.byte	0x6
	.uleb128 0xc7
	.long	.LASF443
	.byte	0x5
	.uleb128 0xc8
	.long	.LASF444
	.byte	0x6
	.uleb128 0xc9
	.long	.LASF445
	.byte	0x5
	.uleb128 0xca
	.long	.LASF446
	.byte	0x6
	.uleb128 0xcb
	.long	.LASF447
	.byte	0x5
	.uleb128 0xcc
	.long	.LASF448
	.byte	0x6
	.uleb128 0xcd
	.long	.LASF449
	.byte	0x5
	.uleb128 0xce
	.long	.LASF450
	.byte	0x6
	.uleb128 0xcf
	.long	.LASF451
	.byte	0x5
	.uleb128 0xd0
	.long	.LASF452
	.byte	0x6
	.uleb128 0xd1
	.long	.LASF453
	.byte	0x5
	.uleb128 0xd2
	.long	.LASF454
	.byte	0x6
	.uleb128 0xdc
	.long	.LASF451
	.byte	0x5
	.uleb128 0xdd
	.long	.LASF452
	.byte	0x5
	.uleb128 0xe3
	.long	.LASF455
	.byte	0x5
	.uleb128 0xe9
	.long	.LASF456
	.byte	0x5
	.uleb128 0xef
	.long	.LASF457
	.byte	0x5
	.uleb128 0xf5
	.long	.LASF455
	.byte	0x5
	.uleb128 0xfa
	.long	.LASF458
	.byte	0x5
	.uleb128 0xfb
	.long	.LASF456
	.byte	0x6
	.uleb128 0x106
	.long	.LASF441
	.byte	0x5
	.uleb128 0x107
	.long	.LASF442
	.byte	0x6
	.uleb128 0x108
	.long	.LASF443
	.byte	0x5
	.uleb128 0x109
	.long	.LASF444
	.byte	0x5
	.uleb128 0x12c
	.long	.LASF459
	.byte	0x5
	.uleb128 0x130
	.long	.LASF460
	.byte	0x5
	.uleb128 0x134
	.long	.LASF461
	.byte	0x5
	.uleb128 0x138
	.long	.LASF462
	.byte	0x5
	.uleb128 0x13c
	.long	.LASF463
	.byte	0x6
	.uleb128 0x13d
	.long	.LASF409
	.byte	0x5
	.uleb128 0x13e
	.long	.LASF457
	.byte	0x6
	.uleb128 0x13f
	.long	.LASF408
	.byte	0x5
	.uleb128 0x140
	.long	.LASF456
	.byte	0x5
	.uleb128 0x144
	.long	.LASF464
	.byte	0x6
	.uleb128 0x145
	.long	.LASF453
	.byte	0x5
	.uleb128 0x146
	.long	.LASF454
	.byte	0x5
	.uleb128 0x14a
	.long	.LASF465
	.byte	0x5
	.uleb128 0x14c
	.long	.LASF466
	.byte	0x5
	.uleb128 0x14d
	.long	.LASF467
	.byte	0x6
	.uleb128 0x14e
	.long	.LASF468
	.byte	0x5
	.uleb128 0x14f
	.long	.LASF469
	.byte	0x5
	.uleb128 0x152
	.long	.LASF464
	.byte	0x5
	.uleb128 0x153
	.long	.LASF470
	.byte	0x5
	.uleb128 0x155
	.long	.LASF463
	.byte	0x5
	.uleb128 0x156
	.long	.LASF471
	.byte	0x6
	.uleb128 0x157
	.long	.LASF409
	.byte	0x5
	.uleb128 0x158
	.long	.LASF457
	.byte	0x6
	.uleb128 0x159
	.long	.LASF408
	.byte	0x5
	.uleb128 0x15a
	.long	.LASF456
	.byte	0x5
	.uleb128 0x164
	.long	.LASF472
	.byte	0x5
	.uleb128 0x168
	.long	.LASF473
	.byte	0x5
	.uleb128 0x170
	.long	.LASF474
	.byte	0x5
	.uleb128 0x174
	.long	.LASF475
	.byte	0x5
	.uleb128 0x178
	.long	.LASF476
	.byte	0x5
	.uleb128 0x183
	.long	.LASF477
	.byte	0x5
	.uleb128 0x18b
	.long	.LASF478
	.byte	0x6
	.uleb128 0x19a
	.long	.LASF479
	.byte	0x5
	.uleb128 0x19b
	.long	.LASF480
	.byte	0x5
	.uleb128 0x19f
	.long	.LASF481
	.byte	0x5
	.uleb128 0x1a0
	.long	.LASF482
	.byte	0x5
	.uleb128 0x1a2
	.long	.LASF483
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.cdefs.h.19.edb893a725d0069cfe6faf28993ef282,comdat
.Ldebug_macro4:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x13
	.long	.LASF484
	.byte	0x2
	.uleb128 0x22
	.string	"__P"
	.byte	0x6
	.uleb128 0x23
	.long	.LASF485
	.byte	0x5
	.uleb128 0x2a
	.long	.LASF486
	.byte	0x5
	.uleb128 0x2b
	.long	.LASF487
	.byte	0x5
	.uleb128 0x3d
	.long	.LASF488
	.byte	0x5
	.uleb128 0x3e
	.long	.LASF489
	.byte	0x5
	.uleb128 0x3f
	.long	.LASF490
	.byte	0x5
	.uleb128 0x40
	.long	.LASF491
	.byte	0x5
	.uleb128 0x59
	.long	.LASF492
	.byte	0x5
	.uleb128 0x5e
	.long	.LASF493
	.byte	0x5
	.uleb128 0x5f
	.long	.LASF494
	.byte	0x5
	.uleb128 0x64
	.long	.LASF495
	.byte	0x5
	.uleb128 0x65
	.long	.LASF496
	.byte	0x5
	.uleb128 0x68
	.long	.LASF497
	.byte	0x5
	.uleb128 0x6d
	.long	.LASF498
	.byte	0x5
	.uleb128 0x6e
	.long	.LASF499
	.byte	0x5
	.uleb128 0x76
	.long	.LASF500
	.byte	0x5
	.uleb128 0x77
	.long	.LASF501
	.byte	0x5
	.uleb128 0x7a
	.long	.LASF502
	.byte	0x5
	.uleb128 0x7c
	.long	.LASF503
	.byte	0x5
	.uleb128 0x7d
	.long	.LASF504
	.byte	0x5
	.uleb128 0x8f
	.long	.LASF505
	.byte	0x5
	.uleb128 0x90
	.long	.LASF506
	.byte	0x5
	.uleb128 0xa9
	.long	.LASF507
	.byte	0x5
	.uleb128 0xab
	.long	.LASF508
	.byte	0x5
	.uleb128 0xad
	.long	.LASF509
	.byte	0x5
	.uleb128 0xb5
	.long	.LASF510
	.byte	0x5
	.uleb128 0xb6
	.long	.LASF511
	.byte	0x5
	.uleb128 0xcb
	.long	.LASF512
	.byte	0x5
	.uleb128 0xd3
	.long	.LASF513
	.byte	0x5
	.uleb128 0xdd
	.long	.LASF514
	.byte	0x5
	.uleb128 0xe4
	.long	.LASF515
	.byte	0x5
	.uleb128 0xed
	.long	.LASF516
	.byte	0x5
	.uleb128 0xee
	.long	.LASF517
	.byte	0x5
	.uleb128 0xf6
	.long	.LASF518
	.byte	0x5
	.uleb128 0x100
	.long	.LASF519
	.byte	0x5
	.uleb128 0x10d
	.long	.LASF520
	.byte	0x5
	.uleb128 0x117
	.long	.LASF521
	.byte	0x5
	.uleb128 0x120
	.long	.LASF522
	.byte	0x5
	.uleb128 0x128
	.long	.LASF523
	.byte	0x5
	.uleb128 0x131
	.long	.LASF524
	.byte	0x6
	.uleb128 0x139
	.long	.LASF525
	.byte	0x5
	.uleb128 0x13a
	.long	.LASF526
	.byte	0x5
	.uleb128 0x143
	.long	.LASF527
	.byte	0x5
	.uleb128 0x155
	.long	.LASF528
	.byte	0x5
	.uleb128 0x156
	.long	.LASF529
	.byte	0x5
	.uleb128 0x15f
	.long	.LASF530
	.byte	0x5
	.uleb128 0x165
	.long	.LASF531
	.byte	0x5
	.uleb128 0x166
	.long	.LASF532
	.byte	0x5
	.uleb128 0x17d
	.long	.LASF533
	.byte	0x5
	.uleb128 0x189
	.long	.LASF534
	.byte	0x5
	.uleb128 0x18a
	.long	.LASF535
	.byte	0x5
	.uleb128 0x1a0
	.long	.LASF536
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.wordsize.h.4.baf119258a1e53d8dba67ceac44ab6bc,comdat
.Ldebug_macro5:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x4
	.long	.LASF537
	.byte	0x5
	.uleb128 0xc
	.long	.LASF538
	.byte	0x5
	.uleb128 0xe
	.long	.LASF539
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.cdefs.h.450.d85bc201b7adaa54aede3b15a722ee22,comdat
.Ldebug_macro6:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x1c2
	.long	.LASF540
	.byte	0x5
	.uleb128 0x1c3
	.long	.LASF541
	.byte	0x5
	.uleb128 0x1c4
	.long	.LASF542
	.byte	0x5
	.uleb128 0x1c5
	.long	.LASF543
	.byte	0x5
	.uleb128 0x1c6
	.long	.LASF544
	.byte	0x5
	.uleb128 0x1c8
	.long	.LASF545
	.byte	0x5
	.uleb128 0x1c9
	.long	.LASF546
	.byte	0x5
	.uleb128 0x1d4
	.long	.LASF547
	.byte	0x5
	.uleb128 0x1d5
	.long	.LASF548
	.byte	0x5
	.uleb128 0x1e9
	.long	.LASF549
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stubs64.h.10.918ceb5fa58268542bf143e4c1efbcf3,comdat
.Ldebug_macro7:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0xa
	.long	.LASF550
	.byte	0x5
	.uleb128 0xb
	.long	.LASF551
	.byte	0x5
	.uleb128 0xc
	.long	.LASF552
	.byte	0x5
	.uleb128 0xd
	.long	.LASF553
	.byte	0x5
	.uleb128 0xe
	.long	.LASF554
	.byte	0x5
	.uleb128 0xf
	.long	.LASF555
	.byte	0x5
	.uleb128 0x10
	.long	.LASF556
	.byte	0x5
	.uleb128 0x11
	.long	.LASF557
	.byte	0x5
	.uleb128 0x12
	.long	.LASF558
	.byte	0x5
	.uleb128 0x13
	.long	.LASF559
	.byte	0x5
	.uleb128 0x14
	.long	.LASF560
	.byte	0x5
	.uleb128 0x15
	.long	.LASF561
	.byte	0x5
	.uleb128 0x16
	.long	.LASF562
	.byte	0x5
	.uleb128 0x17
	.long	.LASF563
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.libcheaderstart.h.37.4783d5b827b19ea444d0c15885193a21,comdat
.Ldebug_macro8:
	.value	0x4
	.byte	0
	.byte	0x6
	.uleb128 0x25
	.long	.LASF564
	.byte	0x5
	.uleb128 0x28
	.long	.LASF565
	.byte	0x6
	.uleb128 0x2f
	.long	.LASF566
	.byte	0x5
	.uleb128 0x31
	.long	.LASF567
	.byte	0x6
	.uleb128 0x38
	.long	.LASF568
	.byte	0x5
	.uleb128 0x3a
	.long	.LASF569
	.byte	0x6
	.uleb128 0x41
	.long	.LASF570
	.byte	0x5
	.uleb128 0x43
	.long	.LASF571
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdio.h.31.e39a94e203ad4e1d978c0fc68ce016ee,comdat
.Ldebug_macro9:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x1f
	.long	.LASF572
	.byte	0x5
	.uleb128 0x20
	.long	.LASF573
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stddef.h.187.422da5f95ac1285e95faf42258f23242,comdat
.Ldebug_macro10:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0xbb
	.long	.LASF574
	.byte	0x5
	.uleb128 0xbc
	.long	.LASF575
	.byte	0x5
	.uleb128 0xbd
	.long	.LASF576
	.byte	0x5
	.uleb128 0xbe
	.long	.LASF577
	.byte	0x5
	.uleb128 0xbf
	.long	.LASF578
	.byte	0x5
	.uleb128 0xc0
	.long	.LASF579
	.byte	0x5
	.uleb128 0xc1
	.long	.LASF580
	.byte	0x5
	.uleb128 0xc2
	.long	.LASF581
	.byte	0x5
	.uleb128 0xc3
	.long	.LASF582
	.byte	0x5
	.uleb128 0xc4
	.long	.LASF583
	.byte	0x5
	.uleb128 0xc5
	.long	.LASF584
	.byte	0x5
	.uleb128 0xc6
	.long	.LASF585
	.byte	0x5
	.uleb128 0xc7
	.long	.LASF586
	.byte	0x5
	.uleb128 0xc8
	.long	.LASF587
	.byte	0x5
	.uleb128 0xc9
	.long	.LASF588
	.byte	0x5
	.uleb128 0xca
	.long	.LASF589
	.byte	0x5
	.uleb128 0xd2
	.long	.LASF590
	.byte	0x6
	.uleb128 0xee
	.long	.LASF591
	.byte	0x6
	.uleb128 0x191
	.long	.LASF592
	.byte	0x5
	.uleb128 0x193
	.long	.LASF593
	.byte	0x6
	.uleb128 0x19c
	.long	.LASF594
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.types.h.98.2414c985b07b6bc05c8aeed70b12c683,comdat
.Ldebug_macro11:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x62
	.long	.LASF596
	.byte	0x5
	.uleb128 0x63
	.long	.LASF597
	.byte	0x5
	.uleb128 0x64
	.long	.LASF598
	.byte	0x5
	.uleb128 0x65
	.long	.LASF599
	.byte	0x5
	.uleb128 0x66
	.long	.LASF600
	.byte	0x5
	.uleb128 0x67
	.long	.LASF601
	.byte	0x5
	.uleb128 0x75
	.long	.LASF602
	.byte	0x5
	.uleb128 0x76
	.long	.LASF603
	.byte	0x5
	.uleb128 0x77
	.long	.LASF604
	.byte	0x5
	.uleb128 0x78
	.long	.LASF605
	.byte	0x5
	.uleb128 0x79
	.long	.LASF606
	.byte	0x5
	.uleb128 0x7a
	.long	.LASF607
	.byte	0x5
	.uleb128 0x7b
	.long	.LASF608
	.byte	0x5
	.uleb128 0x7c
	.long	.LASF609
	.byte	0x5
	.uleb128 0x7e
	.long	.LASF610
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.typesizes.h.24.292526668b3d7d0c797f011b553fed17,comdat
.Ldebug_macro12:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x18
	.long	.LASF611
	.byte	0x5
	.uleb128 0x22
	.long	.LASF612
	.byte	0x5
	.uleb128 0x23
	.long	.LASF613
	.byte	0x5
	.uleb128 0x26
	.long	.LASF614
	.byte	0x5
	.uleb128 0x27
	.long	.LASF615
	.byte	0x5
	.uleb128 0x28
	.long	.LASF616
	.byte	0x5
	.uleb128 0x29
	.long	.LASF617
	.byte	0x5
	.uleb128 0x2a
	.long	.LASF618
	.byte	0x5
	.uleb128 0x2b
	.long	.LASF619
	.byte	0x5
	.uleb128 0x2d
	.long	.LASF620
	.byte	0x5
	.uleb128 0x2e
	.long	.LASF621
	.byte	0x5
	.uleb128 0x33
	.long	.LASF622
	.byte	0x5
	.uleb128 0x34
	.long	.LASF623
	.byte	0x5
	.uleb128 0x35
	.long	.LASF624
	.byte	0x5
	.uleb128 0x36
	.long	.LASF625
	.byte	0x5
	.uleb128 0x37
	.long	.LASF626
	.byte	0x5
	.uleb128 0x38
	.long	.LASF627
	.byte	0x5
	.uleb128 0x39
	.long	.LASF628
	.byte	0x5
	.uleb128 0x3a
	.long	.LASF629
	.byte	0x5
	.uleb128 0x3b
	.long	.LASF630
	.byte	0x5
	.uleb128 0x3c
	.long	.LASF631
	.byte	0x5
	.uleb128 0x3d
	.long	.LASF632
	.byte	0x5
	.uleb128 0x3e
	.long	.LASF633
	.byte	0x5
	.uleb128 0x3f
	.long	.LASF634
	.byte	0x5
	.uleb128 0x40
	.long	.LASF635
	.byte	0x5
	.uleb128 0x41
	.long	.LASF636
	.byte	0x5
	.uleb128 0x42
	.long	.LASF637
	.byte	0x5
	.uleb128 0x43
	.long	.LASF638
	.byte	0x5
	.uleb128 0x44
	.long	.LASF639
	.byte	0x5
	.uleb128 0x45
	.long	.LASF640
	.byte	0x5
	.uleb128 0x46
	.long	.LASF641
	.byte	0x5
	.uleb128 0x47
	.long	.LASF642
	.byte	0x5
	.uleb128 0x48
	.long	.LASF643
	.byte	0x5
	.uleb128 0x49
	.long	.LASF644
	.byte	0x5
	.uleb128 0x4a
	.long	.LASF645
	.byte	0x5
	.uleb128 0x50
	.long	.LASF646
	.byte	0x5
	.uleb128 0x53
	.long	.LASF647
	.byte	0x5
	.uleb128 0x56
	.long	.LASF648
	.byte	0x5
	.uleb128 0x5c
	.long	.LASF649
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4._G_config.h.5.13ce51c385dcc835f259e1016a4e99c8,comdat
.Ldebug_macro13:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x5
	.long	.LASF655
	.byte	0x5
	.uleb128 0xe
	.long	.LASF572
	.byte	0x5
	.uleb128 0x12
	.long	.LASF573
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stddef.h.238.05c1f32ae5cf7bdacd6b0a8ed417a07f,comdat
.Ldebug_macro14:
	.value	0x4
	.byte	0
	.byte	0x6
	.uleb128 0xee
	.long	.LASF591
	.byte	0x6
	.uleb128 0x191
	.long	.LASF592
	.byte	0x5
	.uleb128 0x193
	.long	.LASF593
	.byte	0x6
	.uleb128 0x19c
	.long	.LASF594
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4._G_config.h.51.34b843a0419f1549acdb14c3c66edb4e,comdat
.Ldebug_macro15:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x33
	.long	.LASF657
	.byte	0x5
	.uleb128 0x35
	.long	.LASF658
	.byte	0x5
	.uleb128 0x36
	.long	.LASF659
	.byte	0x5
	.uleb128 0x38
	.long	.LASF660
	.byte	0x5
	.uleb128 0x3b
	.long	.LASF661
	.byte	0x5
	.uleb128 0x3d
	.long	.LASF662
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.libio.h.37.a10f23ff0c406c3c402d761ed92ba872,comdat
.Ldebug_macro16:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x25
	.long	.LASF663
	.byte	0x5
	.uleb128 0x26
	.long	.LASF664
	.byte	0x5
	.uleb128 0x27
	.long	.LASF665
	.byte	0x5
	.uleb128 0x28
	.long	.LASF666
	.byte	0x5
	.uleb128 0x29
	.long	.LASF667
	.byte	0x5
	.uleb128 0x2a
	.long	.LASF668
	.byte	0x5
	.uleb128 0x2b
	.long	.LASF669
	.byte	0x5
	.uleb128 0x2c
	.long	.LASF670
	.byte	0x5
	.uleb128 0x2d
	.long	.LASF671
	.byte	0x5
	.uleb128 0x2e
	.long	.LASF672
	.byte	0x5
	.uleb128 0x2f
	.long	.LASF673
	.byte	0x5
	.uleb128 0x30
	.long	.LASF674
	.byte	0x5
	.uleb128 0x31
	.long	.LASF675
	.byte	0x5
	.uleb128 0x34
	.long	.LASF676
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdarg.h.34.3a23a216c0c293b3d2ea2e89281481e6,comdat
.Ldebug_macro17:
	.value	0x4
	.byte	0
	.byte	0x6
	.uleb128 0x22
	.long	.LASF677
	.byte	0x5
	.uleb128 0x27
	.long	.LASF678
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.libio.h.55.2264ffedaa8d3f567283a630afe6e738,comdat
.Ldebug_macro18:
	.value	0x4
	.byte	0
	.byte	0x6
	.uleb128 0x37
	.long	.LASF679
	.byte	0x5
	.uleb128 0x38
	.long	.LASF680
	.byte	0x5
	.uleb128 0x3f
	.long	.LASF681
	.byte	0x5
	.uleb128 0x42
	.long	.LASF682
	.byte	0x5
	.uleb128 0x51
	.long	.LASF683
	.byte	0x5
	.uleb128 0x52
	.long	.LASF684
	.byte	0x5
	.uleb128 0x53
	.long	.LASF685
	.byte	0x5
	.uleb128 0x54
	.long	.LASF686
	.byte	0x5
	.uleb128 0x55
	.long	.LASF687
	.byte	0x5
	.uleb128 0x56
	.long	.LASF688
	.byte	0x5
	.uleb128 0x57
	.long	.LASF689
	.byte	0x5
	.uleb128 0x58
	.long	.LASF690
	.byte	0x5
	.uleb128 0x60
	.long	.LASF691
	.byte	0x5
	.uleb128 0x61
	.long	.LASF692
	.byte	0x5
	.uleb128 0x62
	.long	.LASF693
	.byte	0x5
	.uleb128 0x63
	.long	.LASF694
	.byte	0x5
	.uleb128 0x64
	.long	.LASF695
	.byte	0x5
	.uleb128 0x65
	.long	.LASF696
	.byte	0x5
	.uleb128 0x66
	.long	.LASF697
	.byte	0x5
	.uleb128 0x67
	.long	.LASF698
	.byte	0x5
	.uleb128 0x68
	.long	.LASF699
	.byte	0x5
	.uleb128 0x69
	.long	.LASF700
	.byte	0x5
	.uleb128 0x6a
	.long	.LASF701
	.byte	0x5
	.uleb128 0x6b
	.long	.LASF702
	.byte	0x5
	.uleb128 0x6c
	.long	.LASF703
	.byte	0x5
	.uleb128 0x6d
	.long	.LASF704
	.byte	0x5
	.uleb128 0x6e
	.long	.LASF705
	.byte	0x5
	.uleb128 0x6f
	.long	.LASF706
	.byte	0x5
	.uleb128 0x70
	.long	.LASF707
	.byte	0x5
	.uleb128 0x71
	.long	.LASF708
	.byte	0x5
	.uleb128 0x72
	.long	.LASF709
	.byte	0x5
	.uleb128 0x74
	.long	.LASF710
	.byte	0x5
	.uleb128 0x75
	.long	.LASF711
	.byte	0x5
	.uleb128 0x79
	.long	.LASF712
	.byte	0x5
	.uleb128 0x82
	.long	.LASF713
	.byte	0x5
	.uleb128 0x83
	.long	.LASF714
	.byte	0x5
	.uleb128 0x84
	.long	.LASF715
	.byte	0x5
	.uleb128 0x85
	.long	.LASF716
	.byte	0x5
	.uleb128 0x86
	.long	.LASF717
	.byte	0x5
	.uleb128 0x87
	.long	.LASF718
	.byte	0x5
	.uleb128 0x88
	.long	.LASF719
	.byte	0x5
	.uleb128 0x89
	.long	.LASF720
	.byte	0x5
	.uleb128 0x8a
	.long	.LASF721
	.byte	0x5
	.uleb128 0x8b
	.long	.LASF722
	.byte	0x5
	.uleb128 0x8c
	.long	.LASF723
	.byte	0x5
	.uleb128 0x8d
	.long	.LASF724
	.byte	0x5
	.uleb128 0x8e
	.long	.LASF725
	.byte	0x5
	.uleb128 0x8f
	.long	.LASF726
	.byte	0x5
	.uleb128 0x90
	.long	.LASF727
	.byte	0x5
	.uleb128 0x91
	.long	.LASF728
	.byte	0x5
	.uleb128 0x92
	.long	.LASF729
	.byte	0x5
	.uleb128 0xf7
	.long	.LASF730
	.byte	0x5
	.uleb128 0x114
	.long	.LASF731
	.byte	0x5
	.uleb128 0x143
	.long	.LASF732
	.byte	0x5
	.uleb128 0x144
	.long	.LASF733
	.byte	0x5
	.uleb128 0x145
	.long	.LASF734
	.byte	0x5
	.uleb128 0x18f
	.long	.LASF735
	.byte	0x5
	.uleb128 0x194
	.long	.LASF736
	.byte	0x5
	.uleb128 0x197
	.long	.LASF737
	.byte	0x5
	.uleb128 0x19b
	.long	.LASF738
	.byte	0x5
	.uleb128 0x1ae
	.long	.LASF739
	.byte	0x5
	.uleb128 0x1af
	.long	.LASF740
	.byte	0x5
	.uleb128 0x1b9
	.long	.LASF741
	.byte	0x5
	.uleb128 0x1c0
	.long	.LASF742
	.byte	0x5
	.uleb128 0x1c1
	.long	.LASF743
	.byte	0x5
	.uleb128 0x1c2
	.long	.LASF744
	.byte	0x5
	.uleb128 0x1c3
	.long	.LASF745
	.byte	0x5
	.uleb128 0x1c5
	.long	.LASF746
	.byte	0x5
	.uleb128 0x1c8
	.long	.LASF747
	.byte	0x5
	.uleb128 0x1cb
	.long	.LASF748
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdio.h.47.b79cbfbbc19b41fda8fa1fa256cf1782,comdat
.Ldebug_macro19:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x2f
	.long	.LASF749
	.byte	0x5
	.uleb128 0x3d
	.long	.LASF750
	.byte	0x5
	.uleb128 0x41
	.long	.LASF751
	.byte	0x5
	.uleb128 0x48
	.long	.LASF752
	.byte	0x5
	.uleb128 0x57
	.long	.LASF753
	.byte	0x5
	.uleb128 0x58
	.long	.LASF754
	.byte	0x5
	.uleb128 0x59
	.long	.LASF755
	.byte	0x5
	.uleb128 0x5e
	.long	.LASF756
	.byte	0x5
	.uleb128 0x6b
	.long	.LASF757
	.byte	0x5
	.uleb128 0x6c
	.long	.LASF758
	.byte	0x5
	.uleb128 0x6d
	.long	.LASF759
	.byte	0x5
	.uleb128 0x6f
	.long	.LASF760
	.byte	0x5
	.uleb128 0x70
	.long	.LASF761
	.byte	0x5
	.uleb128 0x76
	.long	.LASF762
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdio_lim.h.19.86760ef34d2b7513aac6ce30cb73c6f8,comdat
.Ldebug_macro20:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x13
	.long	.LASF763
	.byte	0x5
	.uleb128 0x19
	.long	.LASF764
	.byte	0x5
	.uleb128 0x1a
	.long	.LASF765
	.byte	0x5
	.uleb128 0x1b
	.long	.LASF766
	.byte	0x5
	.uleb128 0x1e
	.long	.LASF767
	.byte	0x5
	.uleb128 0x20
	.long	.LASF768
	.byte	0x6
	.uleb128 0x24
	.long	.LASF769
	.byte	0x5
	.uleb128 0x25
	.long	.LASF770
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdio.h.139.81d529aa6b2372d0b323a208652caa26,comdat
.Ldebug_macro21:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x8b
	.long	.LASF771
	.byte	0x5
	.uleb128 0x8c
	.long	.LASF772
	.byte	0x5
	.uleb128 0x8d
	.long	.LASF773
	.byte	0x5
	.uleb128 0x1e8
	.long	.LASF774
	.byte	0x5
	.uleb128 0x210
	.long	.LASF775
	.byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF103:
	.string	"__cpp_aggregate_nsdmi 201304"
.LASF753:
	.string	"_IOFBF 0"
.LASF447:
	.string	"_XOPEN_SOURCE_EXTENDED"
.LASF610:
	.string	"__STD_TYPE typedef"
.LASF538:
	.string	"__WORDSIZE_TIME64_COMPAT32 1"
.LASF283:
	.string	"__FLT128_MIN_10_EXP__ (-4931)"
.LASF341:
	.string	"__DEC128_EPSILON__ 1E-33DL"
.LASF687:
	.string	"_IOS_TRUNC 16"
.LASF662:
	.string	"_G_BUFSIZ 8192"
.LASF54:
	.string	"__UINT32_TYPE__ unsigned int"
.LASF356:
	.string	"__GCC_ATOMIC_WCHAR_T_LOCK_FREE 2"
.LASF166:
	.string	"__UINT32_MAX__ 0xffffffffU"
.LASF784:
	.string	"size_t"
.LASF63:
	.string	"__UINT_LEAST64_TYPE__ long unsigned int"
.LASF119:
	.string	"__cpp_deduction_guides 201606"
.LASF278:
	.string	"__FLT64_HAS_INFINITY__ 1"
.LASF1:
	.string	"__cplusplus 201703L"
.LASF764:
	.string	"L_tmpnam 20"
.LASF151:
	.string	"__SIZE_WIDTH__ 64"
.LASF340:
	.string	"__DEC128_MAX__ 9.999999999999999999999999999999999E6144DL"
.LASF21:
	.string	"__LP64__ 1"
.LASF746:
	.string	"_IO_cleanup_region_start(_fct,_fp) "
.LASF561:
	.string	"__stub_sigreturn "
.LASF122:
	.string	"__cpp_structured_bindings 201606"
.LASF508:
	.string	"__REDIRECT_NTH(name,proto,alias) name proto __THROW __asm__ (__ASMNAME (#alias))"
.LASF272:
	.string	"__FLT64_DECIMAL_DIG__ 17"
.LASF14:
	.string	"__ATOMIC_CONSUME 1"
.LASF540:
	.string	"__LDBL_REDIR1(name,proto,alias) name proto"
.LASF505:
	.string	"__flexarr []"
.LASF824:
	.string	"_IO_2_1_stderr_"
.LASF760:
	.string	"SEEK_DATA 3"
.LASF393:
	.string	"__unix 1"
.LASF479:
	.string	"__GNU_LIBRARY__"
.LASF197:
	.string	"__UINT_FAST16_MAX__ 0xffffffffffffffffUL"
.LASF228:
	.string	"__DBL_MAX_10_EXP__ 308"
.LASF680:
	.string	"_IO_va_list __gnuc_va_list"
.LASF667:
	.string	"_IO_off_t __off_t"
.LASF719:
	.string	"_IO_HEX 0100"
.LASF466:
	.string	"__USE_XOPEN_EXTENDED 1"
.LASF799:
	.string	"_IO_save_end"
.LASF194:
	.string	"__INT_FAST64_MAX__ 0x7fffffffffffffffL"
.LASF476:
	.string	"__USE_GNU 1"
.LASF34:
	.string	"__ORDER_PDP_ENDIAN__ 3412"
.LASF331:
	.string	"__DEC64_MAX_EXP__ 385"
.LASF548:
	.string	"__glibc_macro_warning(message) __glibc_macro_warning1 (GCC warning message)"
.LASF220:
	.string	"__FLT_HAS_DENORM__ 1"
.LASF48:
	.string	"__INT8_TYPE__ signed char"
.LASF121:
	.string	"__cpp_template_auto 201606"
.LASF231:
	.string	"__DBL_MIN__ double(2.22507385850720138309023271733240406e-308L)"
.LASF258:
	.string	"__FLT32_DECIMAL_DIG__ 9"
.LASF2:
	.string	"__STDC_UTF_16__ 1"
.LASF39:
	.string	"__SIZE_TYPE__ long unsigned int"
.LASF98:
	.string	"__cpp_alias_templates 200704"
.LASF126:
	.string	"__STDCPP_DEFAULT_NEW_ALIGNMENT__ 16"
.LASF181:
	.string	"__UINT8_C(c) c"
.LASF49:
	.string	"__INT16_TYPE__ short int"
.LASF593:
	.string	"NULL __null"
.LASF390:
	.string	"__gnu_linux__ 1"
.LASF792:
	.string	"_IO_write_base"
.LASF517:
	.string	"__attribute_noinline__ __attribute__ ((__noinline__))"
.LASF348:
	.string	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 1"
.LASF4:
	.string	"__STDC_HOSTED__ 1"
.LASF650:
	.string	"__STD_TYPE"
.LASF372:
	.string	"__x86_64 1"
.LASF493:
	.string	"__P(args) args"
.LASF808:
	.string	"_lock"
.LASF575:
	.string	"__SIZE_T__ "
.LASF260:
	.string	"__FLT32_MIN__ 1.17549435082228750796873653722224568e-38F32"
.LASF817:
	.string	"_IO_FILE"
.LASF676:
	.string	"__need___va_list "
.LASF163:
	.string	"__INT64_MAX__ 0x7fffffffffffffffL"
.LASF623:
	.string	"__OFF64_T_TYPE __SQUAD_TYPE"
.LASF111:
	.string	"__cpp_fold_expressions 201603"
.LASF254:
	.string	"__FLT32_MIN_EXP__ (-125)"
.LASF237:
	.string	"__LDBL_MANT_DIG__ 64"
.LASF740:
	.string	"_IO_ferror_unlocked(__fp) (((__fp)->_flags & _IO_ERR_SEEN) != 0)"
.LASF797:
	.string	"_IO_save_base"
.LASF686:
	.string	"_IOS_APPEND 8"
.LASF269:
	.string	"__FLT64_MIN_10_EXP__ (-307)"
.LASF590:
	.string	"__size_t "
.LASF648:
	.string	"__RLIM_T_MATCHES_RLIM64_T 1"
.LASF257:
	.string	"__FLT32_MAX_10_EXP__ 38"
.LASF607:
	.string	"__ULONG32_TYPE unsigned int"
.LASF483:
	.string	"__GLIBC_PREREQ(maj,min) ((__GLIBC__ << 16) + __GLIBC_MINOR__ >= ((maj) << 16) + (min))"
.LASF507:
	.string	"__REDIRECT(name,proto,alias) name proto __asm__ (__ASMNAME (#alias))"
.LASF579:
	.string	"_T_SIZE "
.LASF663:
	.string	"_IO_fpos_t _G_fpos_t"
.LASF33:
	.string	"__ORDER_BIG_ENDIAN__ 4321"
.LASF339:
	.string	"__DEC128_MIN__ 1E-6143DL"
.LASF76:
	.string	"__GXX_WEAK__ 1"
.LASF243:
	.string	"__DECIMAL_DIG__ 21"
.LASF293:
	.string	"__FLT128_HAS_QUIET_NAN__ 1"
.LASF424:
	.string	"__USE_FILE_OFFSET64"
.LASF268:
	.string	"__FLT64_MIN_EXP__ (-1021)"
.LASF694:
	.string	"_IO_USER_BUF 1"
.LASF805:
	.string	"_cur_column"
.LASF828:
	.string	"sys_nerr"
.LASF411:
	.string	"__USE_POSIX"
.LASF327:
	.string	"__DEC32_EPSILON__ 1E-6DF"
.LASF761:
	.string	"SEEK_HOLE 4"
.LASF592:
	.string	"NULL"
.LASF313:
	.string	"__FLT64X_MAX_10_EXP__ 4932"
.LASF768:
	.string	"L_cuserid 9"
.LASF707:
	.string	"_IO_IS_FILEBUF 0x2000"
.LASF721:
	.string	"_IO_SHOWPOINT 0400"
.LASF734:
	.string	"_IO_stderr ((_IO_FILE*)(&_IO_2_1_stderr_))"
.LASF759:
	.string	"SEEK_END 2"
.LASF553:
	.string	"__stub_fchflags "
.LASF232:
	.string	"__DBL_EPSILON__ double(2.22044604925031308084726333618164062e-16L)"
.LASF362:
	.string	"__GCC_ATOMIC_POINTER_LOCK_FREE 2"
.LASF43:
	.string	"__INTMAX_TYPE__ long int"
.LASF632:
	.string	"__FSFILCNT64_T_TYPE __UQUAD_TYPE"
.LASF830:
	.string	"_sys_nerr"
.LASF245:
	.string	"__LDBL_MAX__ 1.18973149535723176502126385303097021e+4932L"
.LASF432:
	.string	"__GNUC_PREREQ(maj,min) ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))"
.LASF415:
	.string	"__USE_XOPEN"
.LASF196:
	.string	"__UINT_FAST8_MAX__ 0xff"
.LASF314:
	.string	"__FLT64X_DECIMAL_DIG__ 21"
.LASF420:
	.string	"__USE_XOPEN2K8"
.LASF306:
	.string	"__FLT32X_HAS_INFINITY__ 1"
.LASF525:
	.string	"__always_inline"
.LASF577:
	.string	"_SYS_SIZE_T_H "
.LASF60:
	.string	"__UINT_LEAST8_TYPE__ unsigned char"
.LASF376:
	.string	"__ATOMIC_HLE_ACQUIRE 65536"
.LASF481:
	.string	"__GLIBC__ 2"
.LASF783:
	.string	"long int"
.LASF570:
	.string	"__GLIBC_USE_IEC_60559_TYPES_EXT"
.LASF104:
	.string	"__cpp_variable_templates 201304"
.LASF342:
	.string	"__DEC128_SUBNORMAL_MIN__ 0.000000000000000000000000000000001E-6143DL"
.LASF300:
	.string	"__FLT32X_DECIMAL_DIG__ 17"
.LASF307:
	.string	"__FLT32X_HAS_QUIET_NAN__ 1"
.LASF433:
	.string	"__glibc_clang_prereq(maj,min) 0"
.LASF464:
	.string	"__USE_XOPEN2K8 1"
.LASF640:
	.string	"__CLOCKID_T_TYPE __S32_TYPE"
.LASF458:
	.string	"__USE_ISOCXX11 1"
.LASF337:
	.string	"__DEC128_MIN_EXP__ (-6142)"
.LASF717:
	.string	"_IO_DEC 020"
.LASF574:
	.string	"__size_t__ "
.LASF282:
	.string	"__FLT128_MIN_EXP__ (-16381)"
.LASF71:
	.string	"__UINT_FAST64_TYPE__ long unsigned int"
.LASF82:
	.string	"__cpp_hex_float 201603"
.LASF56:
	.string	"__INT_LEAST8_TYPE__ signed char"
.LASF37:
	.string	"__SIZEOF_POINTER__ 8"
.LASF352:
	.string	"__GCC_ATOMIC_BOOL_LOCK_FREE 2"
.LASF649:
	.string	"__FD_SETSIZE 1024"
.LASF319:
	.string	"__FLT64X_HAS_DENORM__ 1"
.LASF751:
	.string	"__off64_t_defined "
.LASF818:
	.string	"_IO_marker"
.LASF637:
	.string	"__SUSECONDS_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF256:
	.string	"__FLT32_MAX_EXP__ 128"
.LASF491:
	.string	"__NTHNL(fct) fct throw ()"
.LASF837:
	.string	"main"
.LASF770:
	.string	"FOPEN_MAX 16"
.LASF732:
	.string	"_IO_stdin ((_IO_FILE*)(&_IO_2_1_stdin_))"
.LASF70:
	.string	"__UINT_FAST32_TYPE__ long unsigned int"
.LASF631:
	.string	"__FSFILCNT_T_TYPE __SYSCALL_ULONG_TYPE"
.LASF731:
	.string	"__HAVE_COLUMN "
.LASF297:
	.string	"__FLT32X_MIN_10_EXP__ (-307)"
.LASF523:
	.string	"__attribute_warn_unused_result__ __attribute__ ((__warn_unused_result__))"
.LASF586:
	.string	"_SIZE_T_DECLARED "
.LASF495:
	.string	"__CONCAT(x,y) x ## y"
.LASF489:
	.string	"__THROWNL throw ()"
.LASF772:
	.string	"stdout stdout"
.LASF444:
	.string	"_POSIX_C_SOURCE 200809L"
.LASF289:
	.string	"__FLT128_EPSILON__ 1.92592994438723585305597794258492732e-34F128"
.LASF213:
	.string	"__FLT_MAX_EXP__ 128"
.LASF399:
	.string	"__STDC_IEC_559__ 1"
.LASF23:
	.string	"__SIZEOF_LONG__ 8"
.LASF514:
	.string	"__attribute_pure__ __attribute__ ((__pure__))"
.LASF27:
	.string	"__SIZEOF_DOUBLE__ 8"
.LASF87:
	.string	"__cpp_lambdas 200907"
.LASF95:
	.string	"__cpp_nsdmi 200809"
.LASF242:
	.string	"__LDBL_MAX_10_EXP__ 4932"
.LASF404:
	.string	"__GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION "
.LASF398:
	.string	"_STDC_PREDEF_H 1"
.LASF178:
	.string	"__INT64_C(c) c ## L"
.LASF18:
	.string	"__PIE__ 2"
.LASF276:
	.string	"__FLT64_DENORM_MIN__ 4.94065645841246544176568792868221372e-324F64"
.LASF333:
	.string	"__DEC64_MAX__ 9.999999999999999E384DD"
.LASF474:
	.string	"__USE_MISC 1"
.LASF634:
	.string	"__CLOCK_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF565:
	.string	"__GLIBC_USE_LIB_EXT2 1"
.LASF212:
	.string	"__FLT_MIN_10_EXP__ (-37)"
.LASF758:
	.string	"SEEK_CUR 1"
.LASF215:
	.string	"__FLT_DECIMAL_DIG__ 9"
.LASF654:
	.string	"_BITS_LIBIO_H 1"
.LASF781:
	.string	"signed char"
.LASF699:
	.string	"_IO_ERR_SEEN 0x20"
.LASF115:
	.string	"__cpp_if_constexpr 201606"
.LASF597:
	.string	"__U16_TYPE unsigned short int"
.LASF262:
	.string	"__FLT32_DENORM_MIN__ 1.40129846432481707092372958328991613e-45F32"
.LASF497:
	.string	"__ptr_t void *"
.LASF345:
	.string	"__GNUC_STDC_INLINE__ 1"
.LASF765:
	.string	"TMP_MAX 238328"
.LASF222:
	.string	"__FLT_HAS_QUIET_NAN__ 1"
.LASF645:
	.string	"__CPU_MASK_TYPE __SYSCALL_ULONG_TYPE"
.LASF612:
	.string	"__SYSCALL_SLONG_TYPE __SLONGWORD_TYPE"
.LASF559:
	.string	"__stub_revoke "
.LASF150:
	.string	"__PTRDIFF_WIDTH__ 64"
.LASF182:
	.string	"__UINT_LEAST16_MAX__ 0xffff"
.LASF738:
	.string	"_IO_putc_unlocked(_ch,_fp) (_IO_BE ((_fp)->_IO_write_ptr >= (_fp)->_IO_write_end, 0) ? __overflow (_fp, (unsigned char) (_ch)) : (unsigned char) (*(_fp)->_IO_write_ptr++ = (_ch)))"
.LASF101:
	.string	"__cpp_generic_lambdas 201304"
.LASF499:
	.string	"__END_DECLS }"
.LASF628:
	.string	"__BLKCNT64_T_TYPE __SQUAD_TYPE"
.LASF679:
	.string	"_IO_va_list"
.LASF304:
	.string	"__FLT32X_DENORM_MIN__ 4.94065645841246544176568792868221372e-324F32x"
.LASF271:
	.string	"__FLT64_MAX_10_EXP__ 308"
.LASF750:
	.string	"__off_t_defined "
.LASF191:
	.string	"__INT_FAST16_WIDTH__ 64"
.LASF105:
	.string	"__cpp_digit_separators 201309"
.LASF630:
	.string	"__FSBLKCNT64_T_TYPE __UQUAD_TYPE"
.LASF587:
	.string	"___int_size_t_h "
.LASF3:
	.string	"__STDC_UTF_32__ 1"
.LASF456:
	.string	"__USE_ISOC99 1"
.LASF261:
	.string	"__FLT32_EPSILON__ 1.19209289550781250000000000000000000e-7F32"
.LASF214:
	.string	"__FLT_MAX_10_EXP__ 38"
.LASF494:
	.string	"__PMT(args) args"
.LASF338:
	.string	"__DEC128_MAX_EXP__ 6145"
.LASF744:
	.string	"_IO_funlockfile(_fp) "
.LASF702:
	.string	"_IO_IN_BACKUP 0x100"
.LASF203:
	.string	"__GCC_IEC_559 2"
.LASF310:
	.string	"__FLT64X_MIN_EXP__ (-16381)"
.LASF10:
	.string	"__ATOMIC_SEQ_CST 5"
.LASF472:
	.string	"__USE_LARGEFILE 1"
.LASF165:
	.string	"__UINT16_MAX__ 0xffff"
.LASF185:
	.string	"__UINT32_C(c) c ## U"
.LASF387:
	.string	"__SSE2_MATH__ 1"
.LASF153:
	.string	"__INTMAX_C(c) c ## L"
.LASF241:
	.string	"__LDBL_MAX_EXP__ 16384"
.LASF618:
	.string	"__INO64_T_TYPE __UQUAD_TYPE"
.LASF25:
	.string	"__SIZEOF_SHORT__ 2"
.LASF836:
	.string	"_IO_FILE_plus"
.LASF550:
	.string	"__stub___compat_bdflush "
.LASF347:
	.string	"__STRICT_ANSI__ 1"
.LASF583:
	.string	"_SIZE_T_DEFINED_ "
.LASF502:
	.string	"__warndecl(name,msg) extern void name (void) __attribute__((__warning__ (msg)))"
.LASF638:
	.string	"__DADDR_T_TYPE __S32_TYPE"
.LASF288:
	.string	"__FLT128_MIN__ 3.36210314311209350626267781732175260e-4932F128"
.LASF478:
	.string	"__GLIBC_USE_DEPRECATED_GETS 0"
.LASF364:
	.string	"__PRAGMA_REDEFINE_EXTNAME 1"
.LASF787:
	.string	"char"
.LASF253:
	.string	"__FLT32_DIG__ 6"
.LASF349:
	.string	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 1"
.LASF92:
	.string	"__cpp_variadic_templates 200704"
.LASF67:
	.string	"__INT_FAST64_TYPE__ long int"
.LASF567:
	.string	"__GLIBC_USE_IEC_60559_BFP_EXT 1"
.LASF572:
	.string	"__need_size_t "
.LASF600:
	.string	"__SLONGWORD_TYPE long int"
.LASF622:
	.string	"__OFF_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF429:
	.string	"__KERNEL_STRICT_NAMES"
.LASF31:
	.string	"__BIGGEST_ALIGNMENT__ 16"
.LASF530:
	.string	"__fortify_function __extern_always_inline __attribute_artificial__"
.LASF698:
	.string	"_IO_EOF_SEEN 0x10"
.LASF373:
	.string	"__x86_64__ 1"
.LASF835:
	.string	"_IO_lock_t"
.LASF718:
	.string	"_IO_OCT 040"
.LASF418:
	.string	"__USE_XOPEN2K"
.LASF482:
	.string	"__GLIBC_MINOR__ 27"
.LASF557:
	.string	"__stub_lchmod "
.LASF164:
	.string	"__UINT8_MAX__ 0xff"
.LASF397:
	.string	"_GNU_SOURCE 1"
.LASF218:
	.string	"__FLT_EPSILON__ 1.19209289550781250000000000000000000e-7F"
.LASF311:
	.string	"__FLT64X_MIN_10_EXP__ (-4931)"
.LASF528:
	.string	"__extern_inline extern __inline __attribute__ ((__gnu_inline__))"
.LASF568:
	.string	"__GLIBC_USE_IEC_60559_FUNCS_EXT"
.LASF446:
	.string	"_XOPEN_SOURCE 700"
.LASF234:
	.string	"__DBL_HAS_DENORM__ 1"
.LASF756:
	.string	"BUFSIZ _IO_BUFSIZ"
.LASF461:
	.string	"__USE_POSIX199309 1"
.LASF388:
	.string	"__SEG_FS 1"
.LASF711:
	.string	"_IO_FLAGS2_NOTCANCEL 2"
.LASF131:
	.string	"__GXX_ABI_VERSION 1011"
.LASF171:
	.string	"__INT_LEAST16_MAX__ 0x7fff"
.LASF838:
	.string	"my_func"
.LASF789:
	.string	"_IO_read_ptr"
.LASF284:
	.string	"__FLT128_MAX_EXP__ 16384"
.LASF112:
	.string	"__cpp_nontype_template_args 201411"
.LASF413:
	.string	"__USE_POSIX199309"
.LASF401:
	.string	"__STDC_ISO_10646__ 201706L"
.LASF757:
	.string	"SEEK_SET 0"
.LASF75:
	.string	"__has_include_next(STR) __has_include_next__(STR)"
.LASF773:
	.string	"stderr stderr"
.LASF652:
	.string	"__FILE_defined 1"
.LASF130:
	.string	"__cpp_exceptions 199711"
.LASF821:
	.string	"_pos"
.LASF825:
	.string	"stdin"
.LASF417:
	.string	"__USE_UNIX98"
.LASF64:
	.string	"__INT_FAST8_TYPE__ signed char"
.LASF431:
	.string	"__KERNEL_STRICT_NAMES "
.LASF829:
	.string	"sys_errlist"
.LASF113:
	.string	"__cpp_range_based_for 201603"
.LASF616:
	.string	"__GID_T_TYPE __U32_TYPE"
.LASF709:
	.string	"_IO_USER_LOCK 0x8000"
.LASF357:
	.string	"__GCC_ATOMIC_SHORT_LOCK_FREE 2"
.LASF51:
	.string	"__INT64_TYPE__ long int"
.LASF601:
	.string	"__ULONGWORD_TYPE unsigned long int"
.LASF361:
	.string	"__GCC_ATOMIC_TEST_AND_SET_TRUEVAL 1"
.LASF800:
	.string	"_markers"
.LASF395:
	.string	"__ELF__ 1"
.LASF749:
	.string	"_VA_LIST_DEFINED "
.LASF138:
	.string	"__WCHAR_MIN__ (-__WCHAR_MAX__ - 1)"
.LASF265:
	.string	"__FLT32_HAS_QUIET_NAN__ 1"
.LASF748:
	.string	"_IO_need_lock(_fp) (((_fp)->_flags2 & _IO_FLAGS2_NEED_LOCK) != 0)"
.LASF766:
	.string	"FILENAME_MAX 4096"
.LASF250:
	.string	"__LDBL_HAS_INFINITY__ 1"
.LASF560:
	.string	"__stub_setlogin "
.LASF326:
	.string	"__DEC32_MAX__ 9.999999E96DF"
.LASF647:
	.string	"__INO_T_MATCHES_INO64_T 1"
.LASF660:
	.string	"_G_IO_IO_FILE_VERSION 0x20001"
.LASF745:
	.string	"_IO_ftrylockfile(_fp) "
.LASF678:
	.string	"__GNUC_VA_LIST "
.LASF109:
	.string	"__cpp_enumerator_attributes 201411"
.LASF124:
	.string	"__cpp_sized_deallocation 201309"
.LASF158:
	.string	"__SIG_ATOMIC_MIN__ (-__SIG_ATOMIC_MAX__ - 1)"
.LASF180:
	.string	"__UINT_LEAST8_MAX__ 0xff"
.LASF330:
	.string	"__DEC64_MIN_EXP__ (-382)"
.LASF88:
	.string	"__cpp_decltype 200707"
.LASF668:
	.string	"_IO_off64_t __off64_t"
.LASF320:
	.string	"__FLT64X_HAS_INFINITY__ 1"
.LASF763:
	.string	"_BITS_STDIO_LIM_H 1"
.LASF653:
	.string	"_STDIO_USES_IOSTREAM "
.LASF693:
	.string	"_IO_MAGIC_MASK 0xFFFF0000"
.LASF498:
	.string	"__BEGIN_DECLS extern \"C\" {"
.LASF673:
	.string	"_IO_BUFSIZ _G_BUFSIZ"
.LASF656:
	.string	"____mbstate_t_defined 1"
.LASF173:
	.string	"__INT_LEAST16_WIDTH__ 16"
.LASF207:
	.string	"__DEC_EVAL_METHOD__ 2"
.LASF785:
	.string	"__off_t"
.LASF335:
	.string	"__DEC64_SUBNORMAL_MIN__ 0.000000000000001E-383DD"
.LASF555:
	.string	"__stub_getmsg "
.LASF594:
	.string	"__need_NULL"
.LASF205:
	.string	"__FLT_EVAL_METHOD__ 0"
.LASF462:
	.string	"__USE_POSIX199506 1"
.LASF59:
	.string	"__INT_LEAST64_TYPE__ long int"
.LASF453:
	.string	"_ATFILE_SOURCE"
.LASF606:
	.string	"__SLONG32_TYPE int"
.LASF670:
	.string	"_IO_uid_t __uid_t"
.LASF168:
	.string	"__INT_LEAST8_MAX__ 0x7f"
.LASF714:
	.string	"_IO_LEFT 02"
.LASF627:
	.string	"__BLKCNT_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF11:
	.string	"__ATOMIC_ACQUIRE 2"
.LASF405:
	.string	"__GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION"
.LASF407:
	.string	"__USE_ISOC11"
.LASF539:
	.string	"__SYSCALL_WORDSIZE 64"
.LASF737:
	.string	"_IO_peekc_unlocked(_fp) (_IO_BE ((_fp)->_IO_read_ptr >= (_fp)->_IO_read_end, 0) && __underflow (_fp) == EOF ? EOF : *(unsigned char *) (_fp)->_IO_read_ptr)"
.LASF519:
	.string	"__attribute_deprecated_msg__(msg) __attribute__ ((__deprecated__ (msg)))"
.LASF298:
	.string	"__FLT32X_MAX_EXP__ 1024"
.LASF74:
	.string	"__has_include(STR) __has_include__(STR)"
.LASF657:
	.string	"_G_va_list __gnuc_va_list"
.LASF715:
	.string	"_IO_RIGHT 04"
.LASF179:
	.string	"__INT_LEAST64_WIDTH__ 64"
.LASF221:
	.string	"__FLT_HAS_INFINITY__ 1"
.LASF400:
	.string	"__STDC_IEC_559_COMPLEX__ 1"
.LASF473:
	.string	"__USE_LARGEFILE64 1"
.LASF685:
	.string	"_IOS_ATEND 4"
.LASF160:
	.string	"__INT8_MAX__ 0x7f"
.LASF629:
	.string	"__FSBLKCNT_T_TYPE __SYSCALL_ULONG_TYPE"
.LASF822:
	.string	"_IO_2_1_stdin_"
.LASF595:
	.string	"_BITS_TYPES_H 1"
.LASF224:
	.string	"__DBL_DIG__ 15"
.LASF487:
	.string	"__LEAF_ATTR __attribute__ ((__leaf__))"
.LASF204:
	.string	"__GCC_IEC_559_COMPLEX 2"
.LASF5:
	.string	"__GNUC__ 7"
.LASF17:
	.string	"__pie__ 2"
.LASF53:
	.string	"__UINT16_TYPE__ short unsigned int"
.LASF441:
	.string	"_POSIX_SOURCE"
.LASF457:
	.string	"__USE_ISOC95 1"
.LASF84:
	.string	"__cpp_raw_strings 200710"
.LASF247:
	.string	"__LDBL_EPSILON__ 1.08420217248550443400745280086994171e-19L"
.LASF324:
	.string	"__DEC32_MAX_EXP__ 97"
.LASF578:
	.string	"_T_SIZE_ "
.LASF206:
	.string	"__FLT_EVAL_METHOD_TS_18661_3__ 0"
.LASF414:
	.string	"__USE_POSIX199506"
.LASF143:
	.string	"__SCHAR_WIDTH__ 8"
.LASF669:
	.string	"_IO_pid_t __pid_t"
.LASF506:
	.string	"__glibc_c99_flexarr_available 1"
.LASF791:
	.string	"_IO_read_base"
.LASF435:
	.string	"_ISOC95_SOURCE"
.LASF380:
	.string	"__k8__ 1"
.LASF20:
	.string	"_LP64 1"
.LASF189:
	.string	"__INT_FAST8_WIDTH__ 8"
.LASF286:
	.string	"__FLT128_DECIMAL_DIG__ 36"
.LASF573:
	.string	"__need_NULL "
.LASF406:
	.string	"_FEATURES_H 1"
.LASF452:
	.string	"_DEFAULT_SOURCE 1"
.LASF816:
	.string	"_unused2"
.LASF252:
	.string	"__FLT32_MANT_DIG__ 24"
.LASF486:
	.string	"__LEAF , __leaf__"
.LASF422:
	.string	"__USE_LARGEFILE"
.LASF713:
	.string	"_IO_SKIPWS 01"
.LASF516:
	.string	"__attribute_used__ __attribute__ ((__used__))"
.LASF701:
	.string	"_IO_LINKED 0x80"
.LASF230:
	.string	"__DBL_MAX__ double(1.79769313486231570814527423731704357e+308L)"
.LASF354:
	.string	"__GCC_ATOMIC_CHAR16_T_LOCK_FREE 2"
.LASF227:
	.string	"__DBL_MAX_EXP__ 1024"
.LASF611:
	.string	"_BITS_TYPESIZES_H 1"
.LASF12:
	.string	"__ATOMIC_RELEASE 3"
.LASF305:
	.string	"__FLT32X_HAS_DENORM__ 1"
.LASF209:
	.string	"__FLT_MANT_DIG__ 24"
.LASF89:
	.string	"__cpp_attributes 200809"
.LASF723:
	.string	"_IO_SHOWPOS 02000"
.LASF730:
	.string	"_IO_file_flags _flags"
.LASF467:
	.string	"__USE_UNIX98 1"
.LASF727:
	.string	"_IO_STDIO 040000"
.LASF468:
	.string	"_LARGEFILE_SOURCE"
.LASF152:
	.string	"__INTMAX_MAX__ 0x7fffffffffffffffL"
.LASF554:
	.string	"__stub_fdetach "
.LASF274:
	.string	"__FLT64_MIN__ 2.22507385850720138309023271733240406e-308F64"
.LASF774:
	.string	"getc(_fp) _IO_getc (_fp)"
.LASF804:
	.string	"_old_offset"
.LASF488:
	.string	"__THROW throw ()"
.LASF154:
	.string	"__UINTMAX_MAX__ 0xffffffffffffffffUL"
.LASF83:
	.string	"__cpp_runtime_arrays 198712"
.LASF383:
	.string	"__SSE__ 1"
.LASF156:
	.string	"__INTMAX_WIDTH__ 64"
.LASF665:
	.string	"_IO_size_t size_t"
.LASF351:
	.string	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 1"
.LASF449:
	.string	"_LARGEFILE64_SOURCE"
.LASF646:
	.string	"__OFF_T_MATCHES_OFF64_T 1"
.LASF174:
	.string	"__INT_LEAST32_MAX__ 0x7fffffff"
.LASF542:
	.string	"__LDBL_REDIR1_NTH(name,proto,alias) name proto __THROW"
.LASF299:
	.string	"__FLT32X_MAX_10_EXP__ 308"
.LASF412:
	.string	"__USE_POSIX2"
.LASF695:
	.string	"_IO_UNBUFFERED 2"
.LASF359:
	.string	"__GCC_ATOMIC_LONG_LOCK_FREE 2"
.LASF591:
	.string	"__need_size_t"
.LASF581:
	.string	"_SIZE_T_ "
.LASF208:
	.string	"__FLT_RADIX__ 2"
.LASF46:
	.string	"__CHAR32_TYPE__ unsigned int"
.LASF739:
	.string	"_IO_feof_unlocked(__fp) (((__fp)->_flags & _IO_EOF_SEEN) != 0)"
.LASF251:
	.string	"__LDBL_HAS_QUIET_NAN__ 1"
.LASF248:
	.string	"__LDBL_DENORM_MIN__ 3.64519953188247460252840593361941982e-4951L"
.LASF371:
	.string	"__amd64__ 1"
.LASF147:
	.string	"__LONG_LONG_WIDTH__ 64"
.LASF16:
	.string	"__PIC__ 2"
.LASF128:
	.string	"__cpp_threadsafe_static_init 200806"
.LASF190:
	.string	"__INT_FAST16_MAX__ 0x7fffffffffffffffL"
.LASF360:
	.string	"__GCC_ATOMIC_LLONG_LOCK_FREE 2"
.LASF712:
	.string	"_IO_FLAGS2_USER_WBUF 8"
.LASF741:
	.string	"_IO_PENDING_OUTPUT_COUNT(_fp) ((_fp)->_IO_write_ptr - (_fp)->_IO_write_base)"
.LASF522:
	.string	"__nonnull(params) __attribute__ ((__nonnull__ params))"
.LASF270:
	.string	"__FLT64_MAX_EXP__ 1024"
.LASF192:
	.string	"__INT_FAST32_MAX__ 0x7fffffffffffffffL"
.LASF44:
	.string	"__UINTMAX_TYPE__ long unsigned int"
.LASF445:
	.string	"_XOPEN_SOURCE"
.LASF794:
	.string	"_IO_write_end"
.LASF30:
	.string	"__CHAR_BIT__ 8"
.LASF520:
	.string	"__attribute_format_arg__(x) __attribute__ ((__format_arg__ (x)))"
.LASF367:
	.string	"__SIZEOF_WCHAR_T__ 4"
.LASF188:
	.string	"__INT_FAST8_MAX__ 0x7f"
.LASF485:
	.string	"__PMT"
.LASF108:
	.string	"__cpp_namespace_attributes 201411"
.LASF706:
	.string	"_IO_IS_APPENDING 0x1000"
.LASF365:
	.string	"__SSP_STRONG__ 3"
.LASF198:
	.string	"__UINT_FAST32_MAX__ 0xffffffffffffffffUL"
.LASF94:
	.string	"__cpp_delegating_constructors 200604"
.LASF633:
	.string	"__ID_T_TYPE __U32_TYPE"
.LASF454:
	.string	"_ATFILE_SOURCE 1"
.LASF80:
	.string	"__GXX_EXPERIMENTAL_CXX0X__ 1"
.LASF602:
	.string	"__SQUAD_TYPE long int"
.LASF767:
	.string	"L_ctermid 9"
.LASF35:
	.string	"__BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__"
.LASF175:
	.string	"__INT32_C(c) c"
.LASF688:
	.string	"_IOS_NOCREATE 32"
.LASF41:
	.string	"__WCHAR_TYPE__ int"
.LASF419:
	.string	"__USE_XOPEN2KXSI"
.LASF73:
	.string	"__UINTPTR_TYPE__ long unsigned int"
.LASF428:
	.string	"__USE_FORTIFY_LEVEL"
.LASF682:
	.string	"EOF (-1)"
.LASF344:
	.string	"__USER_LABEL_PREFIX__ "
.LASF42:
	.string	"__WINT_TYPE__ unsigned int"
.LASF318:
	.string	"__FLT64X_DENORM_MIN__ 3.64519953188247460252840593361941982e-4951F64x"
.LASF839:
	.string	"_ZN3ns13ns27my_funcEii"
.LASF379:
	.string	"__k8 1"
.LASF120:
	.string	"__cpp_noexcept_function_type 201510"
.LASF547:
	.string	"__glibc_macro_warning1(message) _Pragma (#message)"
.LASF795:
	.string	"_IO_buf_base"
.LASF803:
	.string	"_flags2"
.LASF691:
	.string	"_IO_MAGIC 0xFBAD0000"
.LASF62:
	.string	"__UINT_LEAST32_TYPE__ unsigned int"
.LASF780:
	.string	"unsigned int"
.LASF66:
	.string	"__INT_FAST32_TYPE__ long int"
.LASF558:
	.string	"__stub_putmsg "
.LASF211:
	.string	"__FLT_MIN_EXP__ (-125)"
.LASF279:
	.string	"__FLT64_HAS_QUIET_NAN__ 1"
.LASF425:
	.string	"__USE_MISC"
.LASF301:
	.string	"__FLT32X_MAX__ 1.79769313486231570814527423731704357e+308F32x"
.LASF277:
	.string	"__FLT64_HAS_DENORM__ 1"
.LASF210:
	.string	"__FLT_DIG__ 6"
.LASF728:
	.string	"_IO_DONT_CLOSE 0100000"
.LASF463:
	.string	"__USE_XOPEN2K 1"
.LASF455:
	.string	"__USE_ISOC11 1"
.LASF775:
	.string	"putc(_ch,_fp) _IO_putc (_ch, _fp)"
.LASF639:
	.string	"__KEY_T_TYPE __S32_TYPE"
.LASF216:
	.string	"__FLT_MAX__ 3.40282346638528859811704183484516925e+38F"
.LASF132:
	.string	"__SCHAR_MAX__ 0x7f"
.LASF811:
	.string	"__pad2"
.LASF812:
	.string	"__pad3"
.LASF93:
	.string	"__cpp_initializer_lists 200806"
.LASF814:
	.string	"__pad5"
.LASF599:
	.string	"__U32_TYPE unsigned int"
.LASF820:
	.string	"_sbuf"
.LASF146:
	.string	"__LONG_WIDTH__ 64"
.LASF513:
	.string	"__attribute_alloc_size__(params) __attribute__ ((__alloc_size__ params))"
.LASF285:
	.string	"__FLT128_MAX_10_EXP__ 4932"
.LASF142:
	.string	"__SIZE_MAX__ 0xffffffffffffffffUL"
.LASF735:
	.string	"_IO_BE(expr,res) __builtin_expect ((expr), res)"
.LASF155:
	.string	"__UINTMAX_C(c) c ## UL"
.LASF535:
	.string	"__glibc_likely(cond) __builtin_expect ((cond), 1)"
.LASF556:
	.string	"__stub_gtty "
.LASF0:
	.string	"__STDC__ 1"
.LASF369:
	.string	"__SIZEOF_PTRDIFF_T__ 8"
.LASF636:
	.string	"__USECONDS_T_TYPE __U32_TYPE"
.LASF127:
	.string	"__cpp_template_template_args 201611"
.LASF36:
	.string	"__FLOAT_WORD_ORDER__ __ORDER_LITTLE_ENDIAN__"
.LASF52:
	.string	"__UINT8_TYPE__ unsigned char"
.LASF613:
	.string	"__SYSCALL_ULONG_TYPE __ULONGWORD_TYPE"
.LASF524:
	.string	"__wur "
.LASF470:
	.string	"__USE_XOPEN2K8XSI 1"
.LASF24:
	.string	"__SIZEOF_LONG_LONG__ 8"
.LASF90:
	.string	"__cpp_rvalue_reference 200610"
.LASF144:
	.string	"__SHRT_WIDTH__ 16"
.LASF776:
	.string	"MY_MACRO(int1,int2,func_call_or_code_block) do { (int1) += 7; (int2) += 5; (func_call_or_code_block); } while (0)"
.LASF336:
	.string	"__DEC128_MANT_DIG__ 34"
.LASF788:
	.string	"_flags"
.LASF605:
	.string	"__UWORD_TYPE unsigned long int"
.LASF381:
	.string	"__code_model_small__ 1"
.LASF480:
	.string	"__GNU_LIBRARY__ 6"
.LASF615:
	.string	"__UID_T_TYPE __U32_TYPE"
.LASF296:
	.string	"__FLT32X_MIN_EXP__ (-1021)"
.LASF353:
	.string	"__GCC_ATOMIC_CHAR_LOCK_FREE 2"
.LASF815:
	.string	"_mode"
.LASF624:
	.string	"__PID_T_TYPE __S32_TYPE"
.LASF541:
	.string	"__LDBL_REDIR(name,proto) name proto"
.LASF117:
	.string	"__cpp_inline_variables 201606"
.LASF496:
	.string	"__STRING(x) #x"
.LASF566:
	.string	"__GLIBC_USE_IEC_60559_BFP_EXT"
.LASF778:
	.string	"unsigned char"
.LASF255:
	.string	"__FLT32_MIN_10_EXP__ (-37)"
.LASF78:
	.string	"__GXX_RTTI 1"
.LASF96:
	.string	"__cpp_inheriting_constructors 201511"
.LASF8:
	.string	"__VERSION__ \"7.4.0\""
.LASF219:
	.string	"__FLT_DENORM_MIN__ 1.40129846432481707092372958328991613e-45F"
.LASF322:
	.string	"__DEC32_MANT_DIG__ 7"
.LASF771:
	.string	"stdin stdin"
.LASF544:
	.string	"__LDBL_REDIR_DECL(name) "
.LASF546:
	.string	"__REDIRECT_NTH_LDBL(name,proto,alias) __REDIRECT_NTH (name, proto, alias)"
.LASF576:
	.string	"_SIZE_T "
.LASF754:
	.string	"_IOLBF 1"
.LASF696:
	.string	"_IO_NO_READS 4"
.LASF755:
	.string	"_IONBF 2"
.LASF651:
	.string	"____FILE_defined 1"
.LASF136:
	.string	"__LONG_LONG_MAX__ 0x7fffffffffffffffLL"
.LASF806:
	.string	"_vtable_offset"
.LASF149:
	.string	"__WINT_WIDTH__ 32"
.LASF510:
	.string	"__ASMNAME(cname) __ASMNAME2 (__USER_LABEL_PREFIX__, cname)"
.LASF536:
	.string	"__attribute_nonstring__ "
.LASF671:
	.string	"_IO_iconv_t _G_iconv_t"
.LASF672:
	.string	"_IO_HAVE_ST_BLKSIZE _G_HAVE_ST_BLKSIZE"
.LASF321:
	.string	"__FLT64X_HAS_QUIET_NAN__ 1"
.LASF281:
	.string	"__FLT128_DIG__ 33"
.LASF169:
	.string	"__INT8_C(c) c"
.LASF697:
	.string	"_IO_NO_WRITES 8"
.LASF259:
	.string	"__FLT32_MAX__ 3.40282346638528859811704183484516925e+38F32"
.LASF779:
	.string	"short unsigned int"
.LASF681:
	.string	"_IO_UNIFIED_JUMPTABLES 1"
.LASF225:
	.string	"__DBL_MIN_EXP__ (-1021)"
.LASF580:
	.string	"__SIZE_T "
.LASF50:
	.string	"__INT32_TYPE__ int"
.LASF329:
	.string	"__DEC64_MANT_DIG__ 16"
.LASF355:
	.string	"__GCC_ATOMIC_CHAR32_T_LOCK_FREE 2"
.LASF643:
	.string	"__FSID_T_TYPE struct { int __val[2]; }"
.LASF409:
	.string	"__USE_ISOC95"
.LASF716:
	.string	"_IO_INTERNAL 010"
.LASF421:
	.string	"__USE_XOPEN2K8XSI"
.LASF408:
	.string	"__USE_ISOC99"
.LASF416:
	.string	"__USE_XOPEN_EXTENDED"
.LASF102:
	.string	"__cpp_decltype_auto 201304"
.LASF809:
	.string	"_offset"
.LASF249:
	.string	"__LDBL_HAS_DENORM__ 1"
.LASF526:
	.string	"__always_inline __inline __attribute__ ((__always_inline__))"
.LASF350:
	.string	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1"
.LASF302:
	.string	"__FLT32X_MIN__ 2.22507385850720138309023271733240406e-308F32x"
.LASF720:
	.string	"_IO_SHOWBASE 0200"
.LASF403:
	.string	"_STDIO_H 1"
.LASF97:
	.string	"__cpp_ref_qualifiers 200710"
.LASF465:
	.string	"__USE_XOPEN 1"
.LASF145:
	.string	"__INT_WIDTH__ 32"
.LASF32:
	.string	"__ORDER_LITTLE_ENDIAN__ 1234"
.LASF79:
	.string	"__cpp_rtti 199711"
.LASF642:
	.string	"__BLKSIZE_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF308:
	.string	"__FLT64X_MANT_DIG__ 64"
.LASF666:
	.string	"_IO_ssize_t __ssize_t"
.LASF436:
	.string	"_ISOC95_SOURCE 1"
.LASF133:
	.string	"__SHRT_MAX__ 0x7fff"
.LASF410:
	.string	"__USE_ISOCXX11"
.LASF584:
	.string	"_SIZE_T_DEFINED "
.LASF689:
	.string	"_IOS_NOREPLACE 64"
.LASF752:
	.string	"__ssize_t_defined "
.LASF609:
	.string	"__U64_TYPE unsigned long int"
.LASF315:
	.string	"__FLT64X_MAX__ 1.18973149535723176502126385303097021e+4932F64x"
.LASF72:
	.string	"__INTPTR_TYPE__ long int"
.LASF801:
	.string	"_chain"
.LASF777:
	.string	"long unsigned int"
.LASF118:
	.string	"__cpp_aggregate_bases 201603"
.LASF81:
	.string	"__cpp_binary_literals 201304"
.LASF116:
	.string	"__cpp_capture_star_this 201603"
.LASF61:
	.string	"__UINT_LEAST16_TYPE__ short unsigned int"
.LASF45:
	.string	"__CHAR16_TYPE__ short unsigned int"
.LASF742:
	.string	"_IO_peekc(_fp) _IO_peekc_unlocked (_fp)"
.LASF295:
	.string	"__FLT32X_DIG__ 15"
.LASF430:
	.string	"__GLIBC_USE_DEPRECATED_GETS"
.LASF448:
	.string	"_XOPEN_SOURCE_EXTENDED 1"
.LASF200:
	.string	"__INTPTR_MAX__ 0x7fffffffffffffffL"
.LASF19:
	.string	"__FINITE_MATH_ONLY__ 0"
.LASF703:
	.string	"_IO_LINE_BUF 0x200"
.LASF374:
	.string	"__SIZEOF_FLOAT80__ 16"
.LASF832:
	.string	"GNU C++14 7.4.0 -mtune=generic -march=x86-64 -g3 -std=c++1z -fstack-protector-strong"
.LASF385:
	.string	"__FXSR__ 1"
.LASF664:
	.string	"_IO_fpos64_t _G_fpos64_t"
.LASF700:
	.string	"_IO_DELETE_DONT_CLOSE 0x40"
.LASF77:
	.string	"__DEPRECATED 1"
.LASF747:
	.string	"_IO_cleanup_region_end(_Doit) "
.LASF86:
	.string	"__cpp_user_defined_literals 200809"
.LASF366:
	.string	"__SIZEOF_INT128__ 16"
.LASF15:
	.string	"__pic__ 2"
.LASF563:
	.string	"__stub_stty "
.LASF40:
	.string	"__PTRDIFF_TYPE__ long int"
.LASF328:
	.string	"__DEC32_SUBNORMAL_MIN__ 0.000001E-95DF"
.LASF503:
	.string	"__warnattr(msg) __attribute__((__warning__ (msg)))"
.LASF177:
	.string	"__INT_LEAST64_MAX__ 0x7fffffffffffffffL"
.LASF608:
	.string	"__S64_TYPE long int"
.LASF233:
	.string	"__DBL_DENORM_MIN__ double(4.94065645841246544176568792868221372e-324L)"
.LASF582:
	.string	"_BSD_SIZE_T_ "
.LASF501:
	.string	"__bos0(ptr) __builtin_object_size (ptr, 0)"
.LASF684:
	.string	"_IOS_OUTPUT 2"
.LASF710:
	.string	"_IO_FLAGS2_MMAP 1"
.LASF382:
	.string	"__MMX__ 1"
.LASF729:
	.string	"_IO_BOOLALPHA 0200000"
.LASF598:
	.string	"__S32_TYPE int"
.LASF798:
	.string	"_IO_backup_base"
.LASF807:
	.string	"_shortbuf"
.LASF725:
	.string	"_IO_FIXED 010000"
.LASF187:
	.string	"__UINT64_C(c) c ## UL"
.LASF217:
	.string	"__FLT_MIN__ 1.17549435082228750796873653722224568e-38F"
.LASF823:
	.string	"_IO_2_1_stdout_"
.LASF47:
	.string	"__SIG_ATOMIC_TYPE__ int"
.LASF85:
	.string	"__cpp_unicode_literals 200710"
.LASF475:
	.string	"__USE_ATFILE 1"
.LASF834:
	.string	"/home/gabriel.staples/GS--p/dev--p/eRCaGuy_hello_world/cpp"
.LASF705:
	.string	"_IO_CURRENTLY_PUTTING 0x800"
.LASF316:
	.string	"__FLT64X_MIN__ 3.36210314311209350626267781732175260e-4932F64x"
.LASF562:
	.string	"__stub_sstk "
.LASF708:
	.string	"_IO_BAD_SEEN 0x4000"
.LASF692:
	.string	"_OLD_STDIO_MAGIC 0xFABC0000"
.LASF819:
	.string	"_next"
.LASF137:
	.string	"__WCHAR_MAX__ 0x7fffffff"
.LASF786:
	.string	"__off64_t"
.LASF58:
	.string	"__INT_LEAST32_TYPE__ int"
.LASF317:
	.string	"__FLT64X_EPSILON__ 1.08420217248550443400745280086994171e-19F64x"
.LASF6:
	.string	"__GNUC_MINOR__ 4"
.LASF240:
	.string	"__LDBL_MIN_10_EXP__ (-4931)"
.LASF358:
	.string	"__GCC_ATOMIC_INT_LOCK_FREE 2"
.LASF125:
	.string	"__cpp_aligned_new 201606"
.LASF292:
	.string	"__FLT128_HAS_INFINITY__ 1"
.LASF303:
	.string	"__FLT32X_EPSILON__ 2.22044604925031308084726333618164062e-16F32x"
.LASF551:
	.string	"__stub_chflags "
.LASF427:
	.string	"__USE_GNU"
.LASF589:
	.string	"_SIZET_ "
.LASF641:
	.string	"__TIMER_T_TYPE void *"
.LASF236:
	.string	"__DBL_HAS_QUIET_NAN__ 1"
.LASF655:
	.string	"_BITS_G_CONFIG_H 1"
.LASF384:
	.string	"__SSE2__ 1"
.LASF290:
	.string	"__FLT128_DENORM_MIN__ 6.47517511943802511092443895822764655e-4966F128"
.LASF796:
	.string	"_IO_buf_end"
.LASF635:
	.string	"__TIME_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF545:
	.string	"__REDIRECT_LDBL(name,proto,alias) __REDIRECT (name, proto, alias)"
.LASF529:
	.string	"__extern_always_inline extern __always_inline __attribute__ ((__gnu_inline__))"
.LASF343:
	.string	"__REGISTER_PREFIX__ "
.LASF439:
	.string	"_ISOC11_SOURCE"
.LASF91:
	.string	"__cpp_rvalue_references 200610"
.LASF106:
	.string	"__cpp_unicode_characters 201411"
.LASF38:
	.string	"__GNUG__ 7"
.LASF521:
	.string	"__attribute_format_strfmon__(a,b) __attribute__ ((__format__ (__strfmon__, a, b)))"
.LASF29:
	.string	"__SIZEOF_SIZE_T__ 8"
.LASF110:
	.string	"__cpp_nested_namespace_definitions 201411"
.LASF659:
	.string	"_G_HAVE_MREMAP 1"
.LASF275:
	.string	"__FLT64_EPSILON__ 2.22044604925031308084726333618164062e-16F64"
.LASF626:
	.string	"__RLIM64_T_TYPE __UQUAD_TYPE"
.LASF389:
	.string	"__SEG_GS 1"
.LASF396:
	.string	"__DECIMAL_BID_FORMAT__ 1"
.LASF769:
	.string	"FOPEN_MAX"
.LASF377:
	.string	"__ATOMIC_HLE_RELEASE 131072"
.LASF68:
	.string	"__UINT_FAST8_TYPE__ unsigned char"
.LASF167:
	.string	"__UINT64_MAX__ 0xffffffffffffffffUL"
.LASF827:
	.string	"stderr"
.LASF386:
	.string	"__SSE_MATH__ 1"
.LASF782:
	.string	"short int"
.LASF484:
	.string	"_SYS_CDEFS_H 1"
.LASF114:
	.string	"__cpp_constexpr 201603"
.LASF183:
	.string	"__UINT16_C(c) c"
.LASF537:
	.string	"__WORDSIZE 64"
.LASF434:
	.string	"__GLIBC_USE(F) __GLIBC_USE_ ## F"
.LASF532:
	.string	"__va_arg_pack_len() __builtin_va_arg_pack_len ()"
.LASF346:
	.string	"__NO_INLINE__ 1"
.LASF199:
	.string	"__UINT_FAST64_MAX__ 0xffffffffffffffffUL"
.LASF9:
	.string	"__ATOMIC_RELAXED 0"
.LASF511:
	.string	"__ASMNAME2(prefix,cname) __STRING (prefix) cname"
.LASF235:
	.string	"__DBL_HAS_INFINITY__ 1"
.LASF157:
	.string	"__SIG_ATOMIC_MAX__ 0x7fffffff"
.LASF266:
	.string	"__FLT64_MANT_DIG__ 53"
.LASF69:
	.string	"__UINT_FAST16_TYPE__ long unsigned int"
.LASF7:
	.string	"__GNUC_PATCHLEVEL__ 0"
.LASF65:
	.string	"__INT_FAST16_TYPE__ long int"
.LASF675:
	.string	"_IO_wint_t wint_t"
.LASF603:
	.string	"__UQUAD_TYPE unsigned long int"
.LASF26:
	.string	"__SIZEOF_FLOAT__ 4"
.LASF332:
	.string	"__DEC64_MIN__ 1E-383DD"
.LASF99:
	.string	"__cpp_return_type_deduction 201304"
.LASF229:
	.string	"__DBL_DECIMAL_DIG__ 17"
.LASF831:
	.string	"_sys_errlist"
.LASF683:
	.string	"_IOS_INPUT 1"
.LASF620:
	.string	"__NLINK_T_TYPE __SYSCALL_ULONG_TYPE"
.LASF552:
	.string	"__stub_fattach "
.LASF690:
	.string	"_IOS_BIN 128"
.LASF161:
	.string	"__INT16_MAX__ 0x7fff"
.LASF512:
	.string	"__attribute_malloc__ __attribute__ ((__malloc__))"
.LASF604:
	.string	"__SWORD_TYPE long int"
.LASF743:
	.string	"_IO_flockfile(_fp) "
.LASF515:
	.string	"__attribute_const__ __attribute__ ((__const__))"
.LASF490:
	.string	"__NTH(fct) __LEAF_ATTR fct throw ()"
.LASF518:
	.string	"__attribute_deprecated__ __attribute__ ((__deprecated__))"
.LASF280:
	.string	"__FLT128_MANT_DIG__ 113"
.LASF617:
	.string	"__INO_T_TYPE __SYSCALL_ULONG_TYPE"
.LASF459:
	.string	"__USE_POSIX 1"
.LASF159:
	.string	"__SIG_ATOMIC_WIDTH__ 32"
.LASF325:
	.string	"__DEC32_MIN__ 1E-95DF"
.LASF450:
	.string	"_LARGEFILE64_SOURCE 1"
.LASF661:
	.string	"_G_HAVE_ST_BLKSIZE defined (_STATBUF_ST_BLKSIZE)"
.LASF469:
	.string	"_LARGEFILE_SOURCE 1"
.LASF596:
	.string	"__S16_TYPE short int"
.LASF309:
	.string	"__FLT64X_DIG__ 18"
.LASF368:
	.string	"__SIZEOF_WINT_T__ 4"
.LASF202:
	.string	"__UINTPTR_MAX__ 0xffffffffffffffffUL"
.LASF724:
	.string	"_IO_SCIENTIFIC 04000"
.LASF527:
	.string	"__attribute_artificial__ __attribute__ ((__artificial__))"
.LASF263:
	.string	"__FLT32_HAS_DENORM__ 1"
.LASF323:
	.string	"__DEC32_MIN_EXP__ (-94)"
.LASF55:
	.string	"__UINT64_TYPE__ long unsigned int"
.LASF736:
	.string	"_IO_getc_unlocked(_fp) (_IO_BE ((_fp)->_IO_read_ptr >= (_fp)->_IO_read_end, 0) ? __uflow (_fp) : *(unsigned char *) (_fp)->_IO_read_ptr++)"
.LASF28:
	.string	"__SIZEOF_LONG_DOUBLE__ 16"
.LASF733:
	.string	"_IO_stdout ((_IO_FILE*)(&_IO_2_1_stdout_))"
.LASF100:
	.string	"__cpp_init_captures 201304"
.LASF543:
	.string	"__LDBL_REDIR_NTH(name,proto) name proto __THROW"
.LASF533:
	.string	"__restrict_arr "
.LASF531:
	.string	"__va_arg_pack() __builtin_va_arg_pack ()"
.LASF625:
	.string	"__RLIM_T_TYPE __SYSCALL_ULONG_TYPE"
.LASF287:
	.string	"__FLT128_MAX__ 1.18973149535723176508575932662800702e+4932F128"
.LASF790:
	.string	"_IO_read_end"
.LASF195:
	.string	"__INT_FAST64_WIDTH__ 64"
.LASF833:
	.string	"advanced_macro_usage_pass_in_entire_func.cpp"
.LASF658:
	.string	"_G_HAVE_MMAP 1"
.LASF451:
	.string	"_DEFAULT_SOURCE"
.LASF273:
	.string	"__FLT64_MAX__ 1.79769313486231570814527423731704357e+308F64"
.LASF291:
	.string	"__FLT128_HAS_DENORM__ 1"
.LASF135:
	.string	"__LONG_MAX__ 0x7fffffffffffffffL"
.LASF22:
	.string	"__SIZEOF_INT__ 4"
.LASF614:
	.string	"__DEV_T_TYPE __UQUAD_TYPE"
.LASF141:
	.string	"__PTRDIFF_MAX__ 0x7fffffffffffffffL"
.LASF426:
	.string	"__USE_ATFILE"
.LASF378:
	.string	"__GCC_ASM_FLAG_OUTPUTS__ 1"
.LASF802:
	.string	"_fileno"
.LASF500:
	.string	"__bos(ptr) __builtin_object_size (ptr, __USE_FORTIFY_LEVEL > 1)"
.LASF370:
	.string	"__amd64 1"
.LASF442:
	.string	"_POSIX_SOURCE 1"
.LASF246:
	.string	"__LDBL_MIN__ 3.36210314311209350626267781732175260e-4932L"
.LASF460:
	.string	"__USE_POSIX2 1"
.LASF394:
	.string	"__unix__ 1"
.LASF492:
	.string	"__glibc_clang_has_extension(ext) 0"
.LASF549:
	.string	"__HAVE_GENERIC_SELECTION 0"
.LASF363:
	.string	"__GCC_HAVE_DWARF2_CFI_ASM 1"
.LASF129:
	.string	"__EXCEPTIONS 1"
.LASF238:
	.string	"__LDBL_DIG__ 18"
.LASF162:
	.string	"__INT32_MAX__ 0x7fffffff"
.LASF471:
	.string	"__USE_XOPEN2KXSI 1"
.LASF140:
	.string	"__WINT_MIN__ 0U"
.LASF619:
	.string	"__MODE_T_TYPE __U32_TYPE"
.LASF704:
	.string	"_IO_TIED_PUT_GET 0x400"
.LASF267:
	.string	"__FLT64_DIG__ 15"
.LASF334:
	.string	"__DEC64_EPSILON__ 1E-15DD"
.LASF762:
	.string	"P_tmpdir \"/tmp\""
.LASF139:
	.string	"__WINT_MAX__ 0xffffffffU"
.LASF170:
	.string	"__INT_LEAST8_WIDTH__ 8"
.LASF509:
	.string	"__REDIRECT_NTHNL(name,proto,alias) name proto __THROWNL __asm__ (__ASMNAME (#alias))"
.LASF57:
	.string	"__INT_LEAST16_TYPE__ short int"
.LASF585:
	.string	"_BSD_SIZE_T_DEFINED_ "
.LASF440:
	.string	"_ISOC11_SOURCE 1"
.LASF244:
	.string	"__LDBL_DECIMAL_DIG__ 21"
.LASF826:
	.string	"stdout"
.LASF264:
	.string	"__FLT32_HAS_INFINITY__ 1"
.LASF569:
	.string	"__GLIBC_USE_IEC_60559_FUNCS_EXT 1"
.LASF392:
	.string	"__linux__ 1"
.LASF477:
	.string	"__USE_FORTIFY_LEVEL 0"
.LASF239:
	.string	"__LDBL_MIN_EXP__ (-16381)"
.LASF571:
	.string	"__GLIBC_USE_IEC_60559_TYPES_EXT 1"
.LASF176:
	.string	"__INT_LEAST32_WIDTH__ 32"
.LASF107:
	.string	"__cpp_static_assert 201411"
.LASF644:
	.string	"__SSIZE_T_TYPE __SWORD_TYPE"
.LASF677:
	.string	"__need___va_list"
.LASF793:
	.string	"_IO_write_ptr"
.LASF375:
	.string	"__SIZEOF_FLOAT128__ 16"
.LASF184:
	.string	"__UINT_LEAST32_MAX__ 0xffffffffU"
.LASF504:
	.string	"__errordecl(name,msg) extern void name (void) __attribute__((__error__ (msg)))"
.LASF621:
	.string	"__FSWORD_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF294:
	.string	"__FLT32X_MANT_DIG__ 53"
.LASF148:
	.string	"__WCHAR_WIDTH__ 32"
.LASF423:
	.string	"__USE_LARGEFILE64"
.LASF172:
	.string	"__INT16_C(c) c"
.LASF402:
	.string	"__STDC_NO_THREADS__ 1"
.LASF438:
	.string	"_ISOC99_SOURCE 1"
.LASF123:
	.string	"__cpp_variadic_using 201611"
.LASF13:
	.string	"__ATOMIC_ACQ_REL 4"
.LASF201:
	.string	"__INTPTR_WIDTH__ 64"
.LASF391:
	.string	"__linux 1"
.LASF226:
	.string	"__DBL_MIN_10_EXP__ (-307)"
.LASF193:
	.string	"__INT_FAST32_WIDTH__ 64"
.LASF437:
	.string	"_ISOC99_SOURCE"
.LASF312:
	.string	"__FLT64X_MAX_EXP__ 16384"
.LASF810:
	.string	"__pad1"
.LASF564:
	.string	"__GLIBC_USE_LIB_EXT2"
.LASF813:
	.string	"__pad4"
.LASF722:
	.string	"_IO_UPPERCASE 01000"
.LASF443:
	.string	"_POSIX_C_SOURCE"
.LASF223:
	.string	"__DBL_MANT_DIG__ 53"
.LASF588:
	.string	"_GCC_SIZE_T "
.LASF534:
	.string	"__glibc_unlikely(cond) __builtin_expect ((cond), 0)"
.LASF134:
	.string	"__INT_MAX__ 0x7fffffff"
.LASF186:
	.string	"__UINT_LEAST64_MAX__ 0xffffffffffffffffUL"
.LASF726:
	.string	"_IO_UNITBUF 020000"
.LASF674:
	.string	"_IO_va_list _G_va_list"
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
