	.data
space: .asciiz "\t"
	.text

main:
	jal getnum
	jal getsort
	
	li $v0,1
	move $a0,$a0
	syscall
	
	li $v0,4
	la $a0,space
	syscall
	
	li $v0,1
	move $a0,$a1
	syscall
	
	li $v0,4
	la $a0,space
	syscall
	
	li $v0,1
	move $a0,$a2
	syscall
	
	li $v0,4
	la $a0,space
	syscall
	
	li $v0,10
	syscall
	
	
	
	
getnum:
	li $v0,5
	syscall
	move $a0,$v0
	
	li $v0,5
	syscall 
	move $a1,$v0
	
	li $v0,5
	syscall 
	move $a2,$v0
	
	jr $ra

getsort:
	bgt $a0,$a1,a0ga1
		#a0<a1
		bgt $a1,$a2,a0sa1_a1ga2
			#a1<a2
			jr $ra
		a0sa1_a1ga2:
			#a1>a2
			bgt $a0,$a2,a0sa1_a1ga2_a0ga2
				#a0<a2
				move $t1,$a1
				move $a1,$a2
				move $a2,$t1
				jr $ra
			a0sa1_a1ga2_a0ga2:
				#a0>a2
				move $t1,$a0
				move $a0,$a2
				move $a2,$a1
				move $a1,$t1
				jr $ra
	a0ga1:
		#a0>a1
		bgt $a0,$a2,a0ga1_a0ga2
			#a0<a2
			move $t1,$a0
			move $a0,$a1
			move $a1,$t1
			jr $ra
	a0ga1_a0ga2:
		#a0>a2
		bgt $a1,$a2,a0ga1_a0ga2_a1ga2
			#a1<a2
			move $t1,$a0
			move $a0,$a1
			move $a1,$a2
			move $a2,$t1
			jr $ra
		a0ga1_a0ga2_a1ga2:
			#a1>a2
			#max a0    mid a1  min a2
			move $t1,$a0
			move $a0,$a2
			move $a2,$t1
			jr $ra
		
		
		
		
		
		


