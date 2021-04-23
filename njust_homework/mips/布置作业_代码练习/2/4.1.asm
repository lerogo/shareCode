	.data 
chico: .word 1,2,31,2,312,4321,2,31,12,214,124,123,412
       .space 408

res: .asciiz "result: "

     	.text 
loop1:
	li $t1,100
	la $s0,chico
	loop2:
	     beqz $t1,main
	     sw $t1,($s0)
	     addi $s0,$s0,4
	     addi $t1,$t1,-1
	     b loop2
main:
	li $t9,100
	la $s0,chico
	loop: beqz $t9,end
	      lw $t1,($s0)
	      add $t2,$t2,$t1
	      addi $s0,$s0,4
	      addi $t9,$t9,-1
	      b loop
end:
	li $v0,4
	la $a0,res
	syscall
	li $v0,1
	move $a0,$t2
	syscall 