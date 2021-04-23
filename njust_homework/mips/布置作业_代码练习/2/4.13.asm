	.data
zap: .space 200
cerr: .asciiz "\n ---error--- \n"

	.text
main:
	li $a0,100
	li $t1,4
	div $a0,$t1
	mfhi $t2
	
	bnez $t2,error
	bgt $a0,196,error
	bltz $a0,error
	
	li $s0,1123
	la $s1,zap
	add $s1,$s1,$a0
	sw $s0,0($s1)
	
	li $v0,1
	lw $a0,0($s1)
	syscall
	
	li $v0,10
	syscall

error:
	li $v0,4
	la $a0,cerr
	syscall