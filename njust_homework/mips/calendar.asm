	.data
STRMENU:	.asciiz	"\n\t--------calendar--------\n\t--------  menu  --------\n\n\t1.Show A certain MONTH\n\t2.Show A certain YEAR\n\t3.Cal DateDiff\n\t4.Exit\n"
STRWEEK:	.asciiz "Sun\tMon\tTue\tWed\tThu\tFri\tSat\n"
STRINFOYEAR:	.asciiz "please input year: "
STRINFOMONTH:	.asciiz "please input month: "
# 计算日期差距用
STRINFOSTARTYEAR:	.asciiz "please input start year: "
STRINFOSTARTMONTH:	.asciiz "please input start month: "
STRINFOSTARTDAY:	.asciiz "please input start day: "
STRINFOENDYEAR:	.asciiz "please input end year: "
STRINFOENDMONTH:	.asciiz "please input end month: "
STRINFOENDDAY:		.asciiz "please input end day: "
STRINFODATEDIFF:	.asciiz "\nthe DateDiff is: "
# 格式化输出
STRSPACETAB:	.asciiz "   \t"
STRSPACE:	.asciiz " "
STRTAB:		.asciiz "\t"
STRENTER:	.asciiz "\n"
STRMONTH:	.asciiz "\n\n\t\t    Month: "
# 每个月天数 初始为平年
MONTHARR:	.align 2
		.word	0,31,28,31,30,31,30,31,31,30,31,30,31
# 输入缓冲
TEMPSTR:	.space 100
TEMPINT:	.align 2
		.space 80


	.text
	.globl main
main:
	# 显示菜单
	la	$a0,STRMENU
	jal coutStr
	# 输入选项
	jal cinInt
	lw	$a0,TEMPINT
	# 判断输入 输入1则显示月历，2则显示年历, 3计算日期差，4 退出, 其他则重新开始main
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
	# 储存ra s0 s1
	addiu	$sp,$sp,-12
	sw	$ra,($sp)
	sw	$s0,4($sp)
	sw	$s1,8($sp)
	# 输出 please input year:
	la	$a0,STRINFOYEAR
	jal	coutStr
	jal	cinInt		# 输入年
	lw	$s0,TEMPINT	# s0:年
	# 输出 please input month:
	la	$a0,STRINFOMONTH
	jal	coutStr
	jal	cinInt		# 输入月
	lw	$s1,TEMPINT	# s1:月
	
	move	$a0,$s0
	move	$a1,$s1
	jal	calCertainMonth	# 计算确定的某年某月
	
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
	
	# 输出 please input year:
	la	$a0,STRINFOYEAR
	jal	coutStr
	jal	cinInt		# 输入年
	lw	$s0,TEMPINT	# s0:年
	
	li	$s1,1
	loopfor1_calYear:
		bgt	$s1,12,end_loopfor1_calYear
		
		# 输出表头 Month:x
		la	$a0,STRMONTH
		jal	coutStr
		move	$a0,$s1
		jal	coutInt
		la	$a0,STRENTER
		jal	coutStr
		
		move	$a0,$s0
		move	$a1,$s1
		jal	calCertainMonth	# 计算确定的某年某月
		addi	$s1,$s1,1
		b loopfor1_calYear
	end_loopfor1_calYear:
	lw	$ra,($sp)
	lw	$s0,4($sp)
	lw	$s1,8($sp)
	addiu	$sp,$sp,12
	jr	$ra

	
calDate2Date:
	# 储存ra s1-s6
	addiu	$sp,$sp,-32
	sw	$ra,($sp)
	sw	$s1,4($sp)
	sw	$s2,8($sp)
	sw	$s3,12($sp)
	sw	$s4,16($sp)
	sw	$s5,20($sp)
	sw	$s6,24($sp)
	sw	$s7,28($sp)
	
	# 输出 please input start year:
	la	$a0,STRINFOSTARTYEAR
	jal	coutStr
	jal	cinInt		# 输入年
	lw	$s1,TEMPINT	# s1:年start
	# 输出 please input start month:
	la	$a0,STRINFOSTARTMONTH
	jal	coutStr
	jal	cinInt		# 输入月
	lw	$s2,TEMPINT	# s2:月start
	# 输出 please input start day:
	la	$a0,STRINFOSTARTDAY
	jal	coutStr
	jal	cinInt		# 输入日
	lw	$s3,TEMPINT	# s3:日start
	
	# 输出 please input end year:
	la	$a0,STRINFOENDYEAR
	jal	coutStr
	jal	cinInt		# 输入年
	lw	$s4,TEMPINT	# s4:年end
	# 输出 please input end month:
	la	$a0,STRINFOENDMONTH
	jal	coutStr
	jal	cinInt		# 输入月
	lw	$s5,TEMPINT	# s5:月end
	# 输出 please input end day:
	la	$a0,STRINFOENDDAY
	jal	coutStr
	jal	cinInt		# 输入如
	lw	$s6,TEMPINT	# s6:日end
	
	li	$s7,0
	add	$s7,$s7,$s6
	sub	$s7,$s7,$s3
	# 计算start月时间
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
	# 计算end月时间
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
	
	# 计算年间隔时间
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
	# 判断是不是闰年 是 返回 v0 = 1
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
	# 将会使用s2计算周 s3作为i 储存原来的s2/s3
	addiu	$sp,$sp,-8
	sw	$s2,($sp)
	sw	$s3,4($sp)	
	
	li	$s3,1		#s3:for i = 1
	move	$s2,$zero
	loopfor1_calCertainMonth:
		ble	$s1,$s3,end_loopfor1_calCertainMonth	#判断条件 i < month
		move	$a0,$s3		# 准备计算 某月多少天
		jal	monthArrInd	
		add	$s2,$s2,$v0	# 加上计算结果
		addi	$s3,$s3,1	# i++
		b	loopfor1_calCertainMonth
	end_loopfor1_calCertainMonth:
	# 计算周 计算公式：s = (year - 1 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + 1 + s) % 7
	addi	$t0,$s0,-1	#t0: year - 1
	div	$t1,$t0,4	#t1: (year - 1) / 4
	div	$t2,$t0,100	#t2: (year - 1) / 100
	div	$t3,$t0,400	#t3: (year - 1) / 400
	# s2 加上前面的
	addi	$s2,$s2,1	# s2 = s2 + 1
	add	$s2,$s2,$t0	# s2 = s2 + year - 1 
	add	$s2,$s2,$t1	# s2 = s2 + (year - 1) / 4
	sub	$s2,$s2,$t2	# s2 = s2 - (year - 1) / 100
	add	$s2,$s2,$t3	# s2 = s2 + (year - 1) / 400
	rem	$s2,$s2,7	# 取余数
	
	# 输出表头
	la	$a0,STRWEEK
	jal	coutStr
	# 输出空格
	li	$s3,0		#t1 : i = 0
	loopfor2_calCertainMonth:
		ble	$s2,$s3,end_loopfor2_calCertainMonth
		la	$a0,STRSPACETAB 	#格式化输出
		jal	coutStr
		addi	$s3,$s3,1
		b	loopfor2_calCertainMonth
	end_loopfor2_calCertainMonth:
	li	$s3,1		# s3:i = 1
	move	$a0,$s1		# 准备计算 某月多少天
	jal	monthArrInd	
	move	$t5,$v0
	loopfor3_calCertainMonth:	 #for (int t = 1; t <= arr[month]; t++)
		blt	$t5,$s3,end_loopfor3_calCertainMonth
		# 输出 日
		move	$a0,$s3
		jal	coutInt
		la	$a0,STRSPACE 	#格式化输出
		jal	coutStr
		la	$a0,STRTAB 	#格式化输出
		jal	coutStr
		
		# 格式化 输出 换行 \n		if (s % 7 == 0)
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

	
monthArrInd:	# a0 为下标 从0开始,输入1则代表1月 返回天数 v0
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

cinStr:		# 输入一个str，并在 TEMPSTR 返回
	li	$v0,8
	la	$a0,TEMPSTR
	li	$a1,100
	syscall
	jr 	$ra
		
cinInt:		# 输入一个数字，并在 TEMPINT 返回
	li	$v0,5
	syscall
	sw	$v0,TEMPINT
	jr 	$ra

coutStr:	# 将str地址放入 $a0 中
	li	$v0,4
	syscall
	jr	$ra

coutInt:	# 将 Int 放入 $a0 中
	li	$v0,1
	syscall
	jr	$ra
	
