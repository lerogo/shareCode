	.data
SRC: .space 408
DESC: .space 400
srcResult: .asciiz "srcResult: "
descResult: .asciiz "descResult: "
print_n: .asciiz "\n"

	.text 
init:
	la $s0,SRC
	li $t0,100
	li $s1,0
	loop_init:
		beqz $t0,main
		sw $t0,($s0)
		addi $s0,$s0,4
		addi $t0,$t0,-1
		lw $t9,-4($s0)
		add $s1,$s1,$t9
		b loop_init

main:
	li $v0,4
	la $a0,srcResult
	syscall
	
	li $v0,1
	move $a0,$s1
	syscall
	
	li $v0,4
	la $a0,print_n
	syscall
	
	la $s0,SRC
	la $s1,DESC
	li $t0,100
	loop_main:
		beqz $t0,sysout
		lw $t9,($s0)
		sw $t9,($s1)
		sw $0,($s0)
		addi $s0,$s0,4
		addi $s1,$s1,4
		addi $t0,$t0,-1
		b loop_main

sysout:
	li $t0,100
	loop_sysout:
		beqz $t0,end
		lw $t9,-4($s0)
		lw $t8,-4($s1)
		add $s5,$s5,$t9
		add $s4,$s4,$t8
		addi $s0,$s0,-4
		addi $s1,$s1,-4
		addi $t0,$t0,-1
		b loop_sysout
end:	
	li $v0,4
	la $a0,srcResult
	syscall
	
	li $v0,1
	move $a0,$s5
	syscall
	
	li $v0,4
	la $a0,print_n
	syscall
	
	li $v0,4
	la $a0,descResult
	syscall
	li $v0,1
	move $a0,$s4
	syscall
	
	li $v0,4
	la $a0,print_n
	syscall