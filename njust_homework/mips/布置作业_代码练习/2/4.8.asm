	.data
K: .space 4
Y: .space 4
Z: .space 200
endl: .asciiz "\n"

	.text
init:
	addi $t1,$0,56
	addi $t2,$0,20
	sw $t1,K
	sw $t2,Y
main:
	li $s1,4	#get 4（s1）
	mul $s2,$s1,$t2	#get Z[k] ($s2)=4*20
	la $s3,Z	#get Z's address（s3）
	add $s3,$s3,$s2 #get Z[k] address (s3)
	
	srl $t3,$t2,2		#(t3) = t2 / 4
	addi $t3,$t3,210 	#(t3) += 210
	sll $t3,$t3,4 		#(t3) *= 16
	sub $t3,$t2,$t3		#(t3) = Y - (t3)
	sw $t3,0($s3)		#also 80($t3 -> Z's address)
	
sysout:
	li $v0,1
	move $a0,$t3
	syscall

	li $v0,4
	la $a0,endl
	syscall
	
	