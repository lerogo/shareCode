	.data
X: 	.align 2	#word align 2
	.space 400	#100 word  and N is 100
strend:	.asciiz "\nthe result: "

	.text
	.globl main
main:	
	li $t1,100 	# t1: i = 100
	la $s0,X	# s0 -> X
	loop_for1:	
		blez 	$t1,end_for1
		sw 	$t1,($s0)	# s0 = 1
		addi 	$s0,$s0,4	# s0 -> s0-1
		addi 	$t1,$t1,-1	# i--
		b loop_for1
	end_for1:
	addiu 	$sp,$sp,-12	#store a0,a1,v0
	la 	$a0,X
	li 	$a1,100
	sw 	$a0,($sp)
	sw 	$a1,4($sp)
	sw 	$v0,8($sp)
	
	# get num to s0
	jal 	getNum
	move 	$s0,$v0
	
	# re a0,a1,v0
	sw 	$a0,($sp)
	sw 	$a1,4($sp)
	sw 	$v0,8($sp)
	addi 	$sp,$sp,12
	
	
	li 	$v0,4
	la 	$a0,strend
	syscall
	li 	$v0,1
	move 	$a0,$s0
	syscall
	
	li 	$v0,10
	syscall
	
getNum:
	move 	$t1,$a0	 # t1: X address
	move 	$t0,$a1	 # t0: X num
	move 	$v0,$zero
	loop_for2:	
		blez 	$t0,end_for2
		lw 	$t2,($t1)
		li 	$t4,4
		rem 	$t3,$t2,$t4	# t3: rem	获取余数 是否除尽
		bnez 	$t3,notif
			addi $v0,$v0,1	
		notif:	
		addi 	$t1,$t1,4	# t1 -> t1-1
		addi 	$t0,$t0,-1	# i--
		b 	loop_for2
	end_for2:
	jr $ra
	
	



