	.file	"sort-c-wc.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	strCmp
	.type	strCmp, @function
strCmp:
	lbu	a5,0(a0)
	lbu	a4,0(a1)
	beq	a5,zero,.L2
.L3:
	bne	a5,a4,.L2
	addi	a0,a0,1
	addi	a1,a1,1
	lbu	a5,0(a0)
	lbu	a4,0(a1)
	bne	a5,zero,.L3
.L2:
	sub	a0,a5,a4
	ret
	.size	strCmp, .-strCmp
	.align	2
	.globl	words
	.type	words, @function
words:					#a0 llega siendo el arreglo
	lbu	a4,0(a0)		# a4 = a[i]
	beq	a4,zero,.L9		# a[i] != '\0' -> .L9
	addi	a5,a0,1		# i = 0
	li	a3,1			# espacio = 1, valor inicial
	li	a0,0			# a0 = words
	li	a2,32			# a2 = ' '
	li	a1,1			# espacio = 1, valor variable
	li	a6,0			# espacio = 0, valor fijo
	j	.L8				# -> .L8
.L10:
	mv	a3,a1			# espacio = 1
.L7:
	addi	a5,a5,1		# i++
	lbu	a4,-1(a5)		# se avanza al siguiente a[i]
	beq	a4,zero,.L12	# a[i] != '\0', aquí está la condición del while -> .L12
.L8:
	beq	a4,a2,.L10		# a[i] == ' ' -> .L10
	beq	a3,zero,.L7		# espacio == 0 -> .L7
	addi	a0,a0,1		# words++
	mv	a3,a6			# espacio = 0
	j	.L7				# -> .L7
.L12:
	ret
.L9:			#	caso en que a[i] != '\0' en el primer caracter del string; retorna 0.
	li	a0,0
	ret
	.size	words, .-words
	.align	2
	.globl	min
	.type	min, @function
min:
	mv	a4,a0
	sub	a1,a2,a1
	slli	a5,a1,2
	add	a0,a0,a5
	addi	a1,a1,1
	ble	a2,a1,.L13
	slli	a1,a1,2
	add	a5,a4,a1
	slli	a2,a2,2
	add	a2,a4,a2
	j	.L16
.L15:
	addi	a5,a5,4
	beq	a5,a2,.L13
.L16:
	lw	a3,0(a0)
	lw	a4,0(a5)
	ble	a3,a4,.L15
	mv	a0,a5
	j	.L15
.L13:
	ret
	.size	min, .-min
	.align	2
	.globl	sort
	.type	sort, @function
sort:
	addi	sp,sp,-48
	sw	ra,44(sp)
	sw	s0,40(sp)
	sw	s1,36(sp)
	sw	s2,32(sp)
	sw	s3,28(sp)
	sw	s4,24(sp)
	sw	s5,20(sp)
	sw	s6,16(sp)
	sw	s7,12(sp)
	sw	s8,8(sp)
	sw	s9,4(sp)
	addi	s0,sp,48
	slli	s5,a1,2
	addi	a5,s5,15
	andi	a5,a5,-16
	sub	sp,sp,a5
	ble	a1,zero,.L18
	mv	s7,a0
	mv	s6,a1
	mv	s3,a1
	mv	s4,sp
	mv	s1,a0
	mv	s2,s4
	add	s5,s5,a0
	mv	s9,s4
	mv	s8,a0
.L20:
	lw	a0,0(s8)
	call	words
	sw	a0,0(s9)
	addi	s8,s8,4
	addi	s9,s9,4
	bne	s8,s5,.L20
.L21:
	mv	a2,s6
	mv	a1,s3
	mv	a0,s4
	call	min
	lw	a4,0(s1)
	sub	a5,a0,s4
	add	a5,s7,a5
	lw	a3,0(a5)
	sw	a3,0(s1)
	sw	a4,0(a5)
	lw	a5,0(s2)
	lw	a4,0(a0)
	sw	a4,0(s2)
	sw	a5,0(a0)
	addi	s3,s3,-1
	addi	s1,s1,4
	addi	s2,s2,4
	bne	s1,s5,.L21
.L18:
	addi	sp,s0,-48
	lw	ra,44(sp)
	lw	s0,40(sp)
	lw	s1,36(sp)
	lw	s2,32(sp)
	lw	s3,28(sp)
	lw	s4,24(sp)
	lw	s5,20(sp)
	lw	s6,16(sp)
	lw	s7,12(sp)
	lw	s8,8(sp)
	lw	s9,4(sp)
	addi	sp,sp,48
	jr	ra
	.size	sort, .-sort
	.ident	"GCC: (GNU) 11.1.0"
