	.data
X: 	.align 0
	.space 123	#100 word  and N is 100
strend:	.asciiz "\nthe result: "

	.text
	.globl main
main:	
	li $t1,123 	# t1: i = 100
	la $s0,X	# s0 -> X
	li $t3,65
	li $t4,122
	# 初始化
	loop_for1:	
		blez 	$t1,end_for1
		slt 	$t5,$t4,$t3
		beqz	$t5,endif
			li $t3,65
		endif:
		sb 	$t3,($s0)	# s0 = 1
		addi 	$s0,$s0,1	# s0 -> s0-1
		addi 	$t1,$t1,-1	# i--
		addi	$t3,$t3,1
		b loop_for1
	end_for1:
	la	$a0,X
	li	$a1,123	
	li	$a2,101

	addiu	$sp,$sp,-24
	sw	$a0,($sp)
	sw	$a1,4($sp)	
	sb	$a2,8($sp)
	jal	Search
	
	# 输出
	li	$v0,4
	la	$a0,strend
	syscall
	li	$v0,1
	lb	$a0,16($sp)
	syscall
	li	$v0,10
	syscall
	
Search:
	lw	$t0,($sp)	#t0:X address
	lw	$t1,4($sp)	#t1:X len
	lb	$t2,8($sp)	#t2:V
	
	li	$t3,1
	
	# 逐个进行查找
	loop_for2:
		slt 	$t4,$t3,$t1
		beqz	$t4,end_for2
		lb	$t5,($t0)
		xor	$t5,$t5,$t2		# 异或判断相等
		beqz	$t5,end_for3
		addi	$t0,$t0,1
		addi	$t3,$t3,1
		b loop_for2
	end_for2:				# 没有查找到 返回-1
		li	$t0,-1
		sw	$t0,16($sp)
		jr	$ra
	end_for3:				# 查找到 返回第一次出现位置
		sw	$t3,16($sp)
		jr	$ra

	