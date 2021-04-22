	.data
STRMENU:	.asciiz	"\n\t--------calendar--------\n\t--------  menu  --------\n\n\t1.Show A certain MONTH\n\t2.Show A certain YEAR\n\t3.Cal DateDiff\n\t4.Exit\n"
STRWEEK:	.asciiz "Sun\tMon\tTue\tWed\tThu\tFri\tSat\n"
STRINFOYEAR:	.asciiz "please input year: "
STRINFOMONTH:	.asciiz "please input month: "
# �������ڲ����
STRINFOSTARTYEAR:	.asciiz "please input start year: "
STRINFOSTARTMONTH:	.asciiz "please input start month: "
STRINFOSTARTDAY:	.asciiz "please input start day: "
STRINFOENDYEAR:	.asciiz "please input end year: "
STRINFOENDMONTH:	.asciiz "please input end month: "
STRINFOENDDAY:		.asciiz "please input end day: "
STRINFODATEDIFF:	.asciiz "\nthe DateDiff is: "
# ��ʽ�����
STRSPACETAB:	.asciiz "   \t"
STRSPACE:	.asciiz " "
STRTAB:		.asciiz "\t"
STRENTER:	.asciiz "\n"
STRMONTH:	.asciiz "\n\n\t\t    Month: "
# ÿ�������� ��ʼΪƽ��
MONTHARR:	.align 2
		.word	0,31,28,31,30,31,30,31,31,30,31,30,31
# ���뻺��
TEMPSTR:	.space 100
TEMPINT:	.align 2
		.space 80


	.text
	.globl main
main:
	# ��ʾ�˵�
	la	$a0,STRMENU
	jal coutStr
	# ����ѡ��
	jal cinInt
	lw	$a0,TEMPINT
	# �ж����� ����1����ʾ������2����ʾ����, 3�������ڲ4 �˳�, ���������¿�ʼmain
	xor	$t0,$a0,1
	bnez	$t0,notCalMonth_main
		jal calMonth
		b main
	notCalMonth_main:
	xor	$t0,$a0,2
	bnez	$t0,notCalYear_main
		jal calYear
		b main
	notCalYear_main:
	xor	$t0,$a0,3
	bnez	$t0,notcalDate2Date_main
		jal calDate2Date
		b main
	notcalDate2Date_main:
	xor	$t0,$a0,4
	bnez	$t0,main
	
	li	$v0,10
	syscall
	

calMonth:
	# ����ra s0 s1
	addiu	$sp,$sp,-12
	sw	$ra,($sp)
	sw	$s0,4($sp)
	sw	$s1,8($sp)
	# ��� please input year:
	la	$a0,STRINFOYEAR
	jal	coutStr
	jal	cinInt		# ������
	lw	$s0,TEMPINT	# s0:��
	# ��� please input month:
	la	$a0,STRINFOMONTH
	jal	coutStr
	jal	cinInt		# ������
	lw	$s1,TEMPINT	# s1:��
	
	move	$a0,$s0
	move	$a1,$s1
	jal	calCertainMonth	# ����ȷ����ĳ��ĳ��
	
	lw	$ra,($sp)
	lw	$s0,4($sp)
	lw	$s1,8($sp)
	addiu	$sp,$sp,12
	move	$t0,$zero
	jr	$ra

calYear:
	addiu	$sp,$sp,-12
	sw	$ra,($sp)
	sw	$s0,4($sp)
	sw	$s1,8($sp)
	
	# ��� please input year:
	la	$a0,STRINFOYEAR
	jal	coutStr
	jal	cinInt		# ������
	lw	$s0,TEMPINT	# s0:��
	
	li	$s1,1
	loopfor1_calYear:
		bgt	$s1,12,end_loopfor1_calYear
		
		# �����ͷ Month:x
		la	$a0,STRMONTH
		jal	coutStr
		move	$a0,$s1
		jal	coutInt
		la	$a0,STRENTER
		jal	coutStr
		
		move	$a0,$s0
		move	$a1,$s1
		jal	calCertainMonth	# ����ȷ����ĳ��ĳ��
		addi	$s1,$s1,1
		b loopfor1_calYear
	end_loopfor1_calYear:
	lw	$ra,($sp)
	lw	$s0,4($sp)
	lw	$s1,8($sp)
	addiu	$sp,$sp,12
	jr	$ra

	
calDate2Date:
	# ����ra s1-s6
	addiu	$sp,$sp,-32
	sw	$ra,($sp)
	sw	$s1,4($sp)
	sw	$s2,8($sp)
	sw	$s3,12($sp)
	sw	$s4,16($sp)
	sw	$s5,20($sp)
	sw	$s6,24($sp)
	sw	$s7,28($sp)
	
	# ��� please input start year:
	la	$a0,STRINFOSTARTYEAR
	jal	coutStr
	jal	cinInt		# ������
	lw	$s1,TEMPINT	# s1:��start
	# ��� please input start month:
	la	$a0,STRINFOSTARTMONTH
	jal	coutStr
	jal	cinInt		# ������
	lw	$s2,TEMPINT	# s2:��start
	# ��� please input start day:
	la	$a0,STRINFOSTARTDAY
	jal	coutStr
	jal	cinInt		# ������
	lw	$s3,TEMPINT	# s3:��start
	
	# ��� please input end year:
	la	$a0,STRINFOENDYEAR
	jal	coutStr
	jal	cinInt		# ������
	lw	$s4,TEMPINT	# s4:��end
	# ��� please input end month:
	la	$a0,STRINFOENDMONTH
	jal	coutStr
	jal	cinInt		# ������
	lw	$s5,TEMPINT	# s5:��end
	# ��� please input end day:
	la	$a0,STRINFOENDDAY
	jal	coutStr
	jal	cinInt		# ������
	lw	$s6,TEMPINT	# s6:��end
	
	li	$s7,0
	add	$s7,$s7,$s6
	sub	$s7,$s7,$s3
	# ����start��ʱ��
	move	$a0,$s1
	jal	isLeapYear
	li	$t3,28
	sw	$t3,MONTHARR+8
	beqz	$v0,notleap_start_month_calDate2Date
		li	$t3,29
		sw	$t3,MONTHARR+8
	notleap_start_month_calDate2Date:
	li	$s3,1
	loop_start_month_calDate2Date:
		ble	$s2,$s3,end_loop_start_month_calDate2Date
		move	$a0,$s3
		jal	monthArrInd
		sub	$s7,$s7,$v0
		addi	$s3,$s3,1
		b loop_start_month_calDate2Date
	end_loop_start_month_calDate2Date:
	# ����end��ʱ��
	move	$a0,$s4
	jal	isLeapYear
	li	$t3,28
	sw	$t3,MONTHARR+8
	beqz	$v0,notleap_end_month_calDate2Date
		li	$t3,29
		sw	$t3,MONTHARR+8
	notleap_end_month_calDate2Date:
	li	$s6,1
	loop_end_month_calDate2Date:
		ble	$s5,$s6,end_loop_end_month_calDate2Date
		move	$a0,$s6
		jal	monthArrInd
		add	$s7,$s7,$v0
		addi	$s6,$s6,1
		b loop_end_month_calDate2Date
	end_loop_end_month_calDate2Date:
	
	# ��������ʱ��
	loop_year_calDate2Date:
		slt	$t0,$s1,$s4
		beqz	$t0,end_loop_year_calDate2Date
		addi	$s7,$s7,365
		move	$a0,$s1
		jal	isLeapYear
		beqz	$v0,notleap_year_calDate2Date
			addi	$s7,$s7,1
		notleap_year_calDate2Date:
		addi	$s1,$s1,1
		b 	loop_year_calDate2Date
	end_loop_year_calDate2Date:
	la	$a0,STRINFODATEDIFF
	jal	coutStr
	move	$a0,$s7
	jal	coutInt
	
	lw	$ra,($sp)
	lw	$s1,4($sp)
	lw	$s2,8($sp)
	lw	$s3,12($sp)
	lw	$s4,16($sp)
	lw	$s5,20($sp)
	lw	$s6,24($sp)
	lw	$s7,28($sp)
	addiu	$sp,$sp,32
	jr 	$ra
		
isLeapYear:
	# �ж��ǲ������� �� ���� v0 = 1
	rem	$t0,$a0,4
	rem	$t1,$a0,100
	rem	$t2,$a0,400
	bnez	$t0,continue400_isLeapYear
		beqz	$t1,continue400_isLeapYear
			li	$v0,1
			jr	$ra
	continue400_isLeapYear:
		bnez	$t2,notleap_isLeapYear
			li	$v0,1
			jr	$ra
	notleap_isLeapYear:
		li	$v0,0
		jr	$ra

calCertainMonth:	#a0:year  a1:month
	addiu	$sp,$sp,-12
	sw	$ra,($sp)
	sw	$s0,4($sp)
	sw	$s1,8($sp)	
	
	move	$s0,$a0		# s0:year
	move	$s1,$a1		# s1:month
	
	li	$t3,29
	jal	isLeapYear
	beqz	$v0,notleap_calCertainMonth
		sw	$t3,MONTHARR+8
	notleap_calCertainMonth:
	# ����ʹ��s2������ s3��Ϊi ����ԭ����s2/s3
	addiu	$sp,$sp,-8
	sw	$s2,($sp)
	sw	$s3,4($sp)	
	
	li	$s3,1		#s3:for i = 1
	move	$s2,$zero
	loopfor1_calCertainMonth:
		ble	$s1,$s3,end_loopfor1_calCertainMonth	#�ж����� i < month
		move	$a0,$s3		# ׼������ ĳ�¶�����
		jal	monthArrInd	
		add	$s2,$s2,$v0	# ���ϼ�����
		addi	$s3,$s3,1	# i++
		b	loopfor1_calCertainMonth
	end_loopfor1_calCertainMonth:
	# ������ ���㹫ʽ��s = (year - 1 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + 1 + s) % 7
	addi	$t0,$s0,-1	#t0: year - 1
	div	$t1,$t0,4	#t1: (year - 1) / 4
	div	$t2,$t0,100	#t2: (year - 1) / 100
	div	$t3,$t0,400	#t3: (year - 1) / 400
	# s2 ����ǰ���
	addi	$s2,$s2,1	# s2 = s2 + 1
	add	$s2,$s2,$t0	# s2 = s2 + year - 1 
	add	$s2,$s2,$t1	# s2 = s2 + (year - 1) / 4
	sub	$s2,$s2,$t2	# s2 = s2 - (year - 1) / 100
	add	$s2,$s2,$t3	# s2 = s2 + (year - 1) / 400
	rem	$s2,$s2,7	# ȡ����
	
	# �����ͷ
	la	$a0,STRWEEK
	jal	coutStr
	# ����ո�
	li	$s3,0		#t1 : i = 0
	loopfor2_calCertainMonth:
		ble	$s2,$s3,end_loopfor2_calCertainMonth
		la	$a0,STRSPACETAB 	#��ʽ�����
		jal	coutStr
		addi	$s3,$s3,1
		b	loopfor2_calCertainMonth
	end_loopfor2_calCertainMonth:
	li	$s3,1		# s3:i = 1
	move	$a0,$s1		# ׼������ ĳ�¶�����
	jal	monthArrInd	
	move	$t5,$v0
	loopfor3_calCertainMonth:	 #for (int t = 1; t <= arr[month]; t++)
		blt	$t5,$s3,end_loopfor3_calCertainMonth
		# ��� ��
		move	$a0,$s3
		jal	coutInt
		la	$a0,STRSPACE 	#��ʽ�����
		jal	coutStr
		la	$a0,STRTAB 	#��ʽ�����
		jal	coutStr
		
		# ��ʽ�� ��� ���� \n		if (s % 7 == 0)
		addi	$s2,$s2,1
		rem	$s2,$s2,7
		bnez	$s2,s_not_zero_loopfor3_calCertainMonth
			la	$a0,STRENTER
			jal	coutStr
		s_not_zero_loopfor3_calCertainMonth:
		addi	$s3,$s3,1
		b	loopfor3_calCertainMonth
	end_loopfor3_calCertainMonth:
	lw	$s2,($sp)
	lw	$s3,4($sp)
	addiu	$sp,$sp,8
	lw	$ra,($sp)
	lw	$s0,4($sp)
	lw	$s1,8($sp)
	addiu	$sp,$sp,12
	jr	$ra

	
monthArrInd:	# a0 Ϊ�±� ��0��ʼ,����1�����1�� �������� v0
	la	$t0,MONTHARR
	move	$t1,$a0
	loop_monthArrInd:
		beqz	$t1,endloop_monthArrInd
		addi	$t1,$t1,-1
		addi	$t0,$t0,4
		b	loop_monthArrInd
	endloop_monthArrInd:
	lw	$v0,($t0)
	jr 	$ra

cinStr:		# ����һ��str������ TEMPSTR ����
	li	$v0,8
	la	$a0,TEMPSTR
	li	$a1,100
	syscall
	jr 	$ra
		
cinInt:		# ����һ�����֣����� TEMPINT ����
	li	$v0,5
	syscall
	sw	$v0,TEMPINT
	jr 	$ra

coutStr:	# ��str��ַ���� $a0 ��
	li	$v0,4
	syscall
	jr	$ra

coutInt:	# �� Int ���� $a0 ��
	li	$v0,1
	syscall
	jr	$ra
	
