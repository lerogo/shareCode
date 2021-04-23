	.data
TEMPSTR:	.space	200	# ÊäÈë×Ö·û´®ÓÃ
TEMPSTRLEN:	.align 2
		.word	200
STRINFOPOS:	.asciiz "\nA Vowel was Found at Relation Position :	"
STRINFOEND:	.asciiz "\nThe num is:"
STRENTER:	.asciiz	"\n\n"

	.text
	.globl main
main:
	addiu	$sp,$sp,-4
	jal	cinStr
	la	$a0,TEMPSTR
	sw	$a0,($sp)
	jal	Scan
	la	$a0,STRINFOEND
	jal	coutStr
	lw	$a0,($sp)
	jal	coutInt
	la	$a0,STRENTER
	jal	coutStr
	addiu	$sp,$sp,4
	b	main
Scan:
	lw	$a0,($sp)
	addiu	$sp,$sp,-16
	sw	$ra,($sp)
	sw	$s0,4($sp)
	sw	$s1,8($sp)
	sw	$s2,12($sp)
	move	$s0,$a0		# s0:×Ö·û´®µØÖ·
	li	$s2,0
	li	$s1,1		#for i Î»ÖÃ
	loopfor1_Scan:
		lb	$t0,($s0)
		beqz	$t0,endloopfor1_Scan
		move	$a0,$t0
		jal	isVowel
		beqz	$v0,loopContinue
			la	$a0,STRINFOPOS
			jal	coutStr
			move	$a0,$s1
			jal	coutInt
			addi	$s2,$s2,1
		loopContinue:
		addi	$s0,$s0,1
		addi	$s1,$s1,1
		b 	loopfor1_Scan
	endloopfor1_Scan:
	move	$v0,$s2
	lw	$ra,($sp)
	lw	$s0,4($sp)
	lw	$s1,8($sp)
	lw	$s2,12($sp)
	addiu	$sp,$sp,16
	sw	$v0,($sp)
	jr	$ra

isVowel:
	move	$t0,$a0
	beq	$t0,'a',isV
	beq	$t0,'e',isV
	beq	$t0,'i',isV
	beq	$t0,'o',isV
	beq	$t0,'u',isV
	li	$v0,0
	jr	$ra
	isV:
	li	$v0,1
	jr	$ra
	
coutStr:	# a0£º×Ö·û´®µØÖ·
	li	$v0,4
	syscall
	jr	$ra

coutInt:	#a0:Int
	li	$v0,1
	syscall
	jr	$ra
	

cinStr:		# a0: ×Ö·û´®µØÖ·   a1: ³¤¶È
	la	$a0,TEMPSTR
	lw	$a1,TEMPSTRLEN
	li	$v0,8
	syscall
	jr	$ra

