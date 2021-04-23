	.data
arr: .space 40
odd: .asciiz "odd: "
even: .asciiz "even: "
endl: .asciiz "\n"

	.text

init:			# arr[i-1] = i%2 ? i:-i
	li $t1,11
	la $s1,arr
	addi $s1,$s1,36
	loop1:
		addi $t1,$t1,-1
		beqz $t1,main
		div $t2,$t1,2  	#now (t2) is lo
		mfhi $t2	#now (t2) is hi
		beqz $t2,evena	#if even num -> go to even
		sw $t1,0($s1)	#save word -> arr[t-1]
		addi $s1,$s1,-4	#arr[t-1-1]
		
		b loop1
		evena:
			neg $t2,$t1
			sw $t2,0($s1)	#save word -> arr[t-1]
			addi $s1,$s1,-4	#arr[t-1-1]
			
			b loop1

main:
	la $a0,arr
	li $a1,10
	jal PENO
	
	move $s0,$v0
	move $s1,$v1
	
	li $v0,4
	la $a0,odd
	syscall
	
	li $v0,1
	move $a0,$s0
	syscall
	
	li $v0,4
	la $a0,endl
	syscall
	
	li $v0,4
	la $a0,even
	syscall
	
	li $v0,1
	move $a0,$s1
	syscall
	
	li $v0,4
	la $a0,endl
	syscall
	
	li $v0,10
	syscall
	
PENO:		#PENO(&X, N, SP, SN)
	move $t1,$a0		#now (t1) -> arr's address
	move $t2,$a1		#now (t2) -> arr's lenth
	
	xor $v0,$v0,$v0		#v0/1 -> 0
	xor $v1,$v1,$v1
	
	loopPeno:
		beqz $t2,retPeno
			addi $t2,$t2,-1
			lw $t5,0($t1)
			addi $t1,$t1,4
			div $t4,$t5,2
			mfhi $t4
			beqz $t4,evenb
				add $v0,$v0,$t5
				b loopPeno
			evenb:
				add $v1,$v1,$t5
				b loopPeno
		retPeno:
			jr $ra
	
	
