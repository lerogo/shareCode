	.data
	
str: .asciiz "09azAZ123 abc ABC @@ ## $$ !!q123\n"

	.text 
main:
	addi $sp,$sp,-8
	la $a0,str
	sw $a0,4($sp)
	li $t1,34
	sw $t1,0($sp)
	addi $sp,$sp,8
	
	jal scan
	
	li $v0,4
	la $a0,str
	syscall		
	
	li $v0,1
	lw $a0,8($sp)
	syscall
	
	lw $a0,4($sp)
	syscall
	
	lw $a0,($sp)
	syscall
	
	li $v0,10
	syscall

scan:
	addi $sp,$sp,-24
	sw $ra,12($sp)
	lw $a0,20($sp)
	lw $t1,16($sp)
	
	addi $sp,$sp,-24
	sw $s1,0($sp)
	sw $s2,4($sp)
	sw $s3,8($sp)
	sw $s4,12($sp)
	sw $s5,16($sp)
	sw $s6,20($sp)
	addi $sp,$sp,24
	
	li $s1,0x30
	li $s2,0x39
	
	li $s3,0x41
	li $s4,0x5a
	
	li $s5,0x61
	li $s6,0x7a
	
	li $t7,0
	li $t8,0
	li $t9,0
	
	loop:
		bltz $t1,end
			addi $t1,$t1,-1
			add $t3,$a0,$t1
			lb $t4,($t3)
			
			bgt $t4,$s6,loop	# <=z
				bge $t4,$s5,addL	# <a
					bgt $t4,$s4,loop # <=Z
						bge $t4,$s3,addU # <A
							bgt $t4,$s2,loop # <=9
								bge $t4,$s1,addD # <0
			b loop
addD:
	addi $t7,$t7,1
	b loop	

addU:	
	addi $t8,$t8,1
	b loop

addL:	
	addi $t9,$t9,1
	b loop
	
end:
	sw $t9,($sp)
	sw $t8,4($sp)
	sw $t7,8($sp)
	lw $ra,12($sp)
	
	addi $sp,$sp,-24
	lw $s1,0($sp)
	lw $s2,4($sp)
	lw $s3,8($sp)
	lw $s4,12($sp)
	lw $s5,16($sp)
	lw $s6,20($sp)
	addi $sp,$sp,24
	
	jr $ra
	
