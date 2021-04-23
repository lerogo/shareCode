	.data
X:	.align 2
	.word  21,32,3424,123,12,432,2,332,132,423,123	# N = 11
strend:	.asciiz "\nthe result: "
strspace:	.asciiz "\t"
	
	.text
	.globl main
main:
	la	$a0,X		# 加载地址
	li	$a1,11		# 加载数组长度
	addiu	$sp,$sp,-24	# 指针 存放
	sw	$a0,($sp)
	sw	$a1,4($sp)
	
	li	$v0,4		# 输出字符串
	la	$a0,strend
	syscall
	
	jal 	BubSort		# 调用函数
		
	li	$v0,10		# 退出
	syscall
	
BubSort:
	lw	$a0,($sp)	#a0:address
	lw	$a1,4($sp)	#a1:len
	
	move	$t1,$a1		# t1:i
	loopi:
		slt	$t3,$zero,$t1		# for(int i=len;i>0;--i)
		beqz	$t3,endloopi
		li	$t2,1		# t2:j
		loopj:				# for(int i=1;j<i;++j)
			slt	$t3,$t2,$t1
			beqz	$t3,endloopj
			
			mul	$t0,$t2,4	# 获取地址 arr[j]
			add	$a0,$a0,$t0
			lw	$t5,($a0)	#t5:arr[j]
			
			addi	$a0,$a0,-4
			lw	$t4,($a0)	#t4:arr[j-1]
			
			slt	$t6,$t5,$t4	# 比较大小 if (arr[j] < arr[j-1]) 交换
			beqz	$t6,endarrif
				sw	$t5,($a0)
				addi	$a0,$a0,4
				sw	$t4,($a0)
				addi	$a0,$a0,-4
			endarrif:		# 还原a0地址
			addi	$a0,$a0,4
			sub	$a0,$a0,$t0
			
			addi	$t2,$t2,1
			b	loopj
		endloopj:
		addi	$t1,$t1,-1
		b 	loopi
	endloopi:
		move 	$t0,$a1		# 长度
		move 	$t5,$a0		# 数组地址
		loopout:		# for输出
			blez	$t0,endloopout
			li	$v0,1
			lw	$a0,($t5)
			syscall
			li	$v0,4
			la	$a0,strspace
			syscall
			addi	$t5,$t5,4
			addi	$t0,$t0,-1
			b	loopout
		endloopout:
		jr $ra
	
	
	
	
	
	