.data
array:	.space 80
mean:	.float 0
medianFloat:	.float 0
medianWord:	.word 0
stdDev:	.float 0
newLine:	.asciiz "\n"
space: .asciiz " "
errormessage:	.asciiz	"Error: Invalid array"
input:	.asciiz	"input.txt"
arrmsg:	.asciiz	"The array before: "
sortarrmsg:	.asciiz	"The array after: "
meanmsg:	.asciiz	"The mean is: "
medianmsg:	.asciiz "The median is: "
stdDevmsg:	.asciiz	"The standard deviation is: "
filename:	.asciiz	"input.txt"
two:	.float	2
one:	.float	1
zero:	.float	0
buffer:	
	.space 80

.text
	#load filename and buffer name to registers
	#to open the file
	la	$a0, buffer
	la	$a1, filename
	jal	readFile
	
	#checks if file was empty
	bgt	$v0, $zero, noError
	
	#print errormessage for check
	la	$a0, errormessage
	li	$v0, 4
	syscall
	j done

	noError:
	#file was not empty
	#converts bytes to words
	la	$a0, array
	li	$a1, 20
	la	$a2, buffer
	jal 	convertBytes
	
	#print message for the array before sorting
	la	$a0, arrmsg
	li	$v0, 4
	syscall
	
	#call print array method
	la	$a0, array
	li	$a1, 20
	jal 	print
	
	#print newLine
	la	$a0, newLine
	li	$v0, 4
	syscall
	
	#call selection sort
	la	$a0, array
	li	$a1, 20
	jal 	selectionSort
	
	#print message for the array after sorting
	la	$a0, sortarrmsg
	li	$v0, 4
	syscall
	
	#call print array method
	la	$a0, array
	li	$a1, 20
	jal 	print
	
	#print newLine
	la	$a0, newLine
	li	$v0, 4
	syscall
	
	#call calcMean method
	la	$a0, array
	li	$a1, 20
	jal 	calcMean
	
	s.s	$f0, mean
	
	#print message for the mean
	la	$a0, meanmsg
	li	$v0, 4
	syscall
	
	#print the mean
	lwc1	$f12, mean
	li	$v0, 2
	syscall
	
	#print newLine
	la	$a0, newLine
	li	$v0, 4
	syscall
	
	#call calcMedian method
	la	$a0, array
	li	$a1, 20
	jal 	calcMedian
	
	#print message for the median
	la	$a0, medianmsg
	li	$v0, 4
	syscall
	
	bgtz	$v1, odd
	j skipOdd
	odd:
	#save word median
	sw	$v0, medianWord
	
 	lw	$a0, medianWord
	li	$v0, 1
	syscall
	j	continueMain
	
	skipOdd:
	#save float median
	s.s	$f0, medianFloat
	
	#print the mean
	lwc1	$f12, medianFloat
	li	$v0, 2
	syscall
	
	
	continueMain:
	#print newLine
	la	$a0, newLine
	li	$v0, 4
	syscall
	
	#call calcSD method
	la	$a0, array
	li	$a1, 20
	l.s	$f12, mean
	jal 	calcSD
	
	#save dtandard Deviation
	s.s	$f0, stdDev
	
	#print message for the SD
	la	$a0, stdDevmsg
	li	$v0, 4
	syscall
	
	#print the mean
	lwc1	$f12, stdDev
	li	$v0, 2
	syscall
	
	#print newLine
	la	$a0, newLine
	li	$v0, 4
	syscall
	
	
	


done:	#end program
	li	$v0 10
	syscall
	
readFile:
	#open the input file
 	li	$v0, 13
 	la	$a0, filename
 	li	$a1, 0
 	li	$a2, 0
 	syscall
 	move	$s6, $v0
 	
 	#read from the input file
 	li	$v0, 14
 	move	$a0, $s6
 	la	$a1, buffer
 	li	$a2, 80
 	syscall# read from file
 	
 	#return to main
 	jr	$ra
 	
convertBytes:
 	li	$t9,0	
 	
 	loop:
 	#load byte
 	lb	$t0, ($a2)
 	
 	#check if end of file
 	beq	$t0, $zero, end
 	
 	#check if is digit or not
 	blt $t0, 48, loop
	bgt $t0, 57, loop
 	
 	#check if single digit or not
 	addi	$a2, $a2, 1
 	lb	$t1, ($a2)
 	#branch if single digit
 	beq	$t1, 10, single
 	
 	#convert from ascii to int
 	subi	$t0, $t0, 48
 	subi	$t1, $t1, 48
 	#move digit to tens place
 	mul	$t0, $t0, 10
 	#adds the whole number
 	add	$t0, $t0, $t1
 	#skips new line to match single
 	addi	$a2, $a2, 1
 	j	store
 	
 	single:
 	#convert from ascii to int
 	subi	$t0, $t0, 48
 	
 	store:
 	#save number to array
 	sw	$t0, ($a0)
	#move pointers
	addi	$a2, $a2, 1
	addi	$a0, $a0, 4
	addi	$t9, $t9, 1
	#check if max nums reached
 	blt	$t9, $a1, loop
 	
	end:#return to main
 	jr	$ra
 	
print:
 	li	$t9,0
 	move	$s0, $a0
 	
 	printloop:
 	#load word
 	lw	$a0, ($s0)
	li	$v0, 1
	syscall #print word
	
	#print space
	#print message for the array before sorting
	la	$a0, space
	li	$v0, 4
	syscall
 	
	#move pointers
	addi	$s0, $s0, 4
	addi	$t9, $t9, 1
	#check if max nums reached
 	blt	$t9, $a1, printloop
 	
	#return to main
 	jr	$ra
 	
selectionSort:
	#outer loop counter
	li	$t0, 0
	#inner loop counter
	li	$t1, 0
	li	$t9, 20
 	
 	outer_loop:
	#get the current address for the value
	mul	$s6, $t0, 4
	add	$s6, $a0, $s6
	lw	$t6, ($s6)	
	
	# Store smallest number's address in $s3 and smallest number in $s4
	move	$s3, $s6
	move	$s4, $t6
	
	# set $t1 to current iteration value
	move	$t1, $t0	
	
	# loops until 20, finding smallest integer in array
	inner_loop:
	#get the current address for the value
	mul	$s7, $t1, 4
	add	$s7, $a0, $s7
	lw	$t7, ($s7)	
	
	blt	$t7, $s4, save_new_smallest
	j	continue

	save_new_smallest:
	move	$s3, $s7
	move	$s4, $t7
	
	continue:
	addi	$t1, $t1, 1
	blt	$t1, $t9, inner_loop
	
	# Swap elements
	sw	$t6, ($s3)
	sw	$s4, ($s6)
			
	addi	$t0, $t0, 1
	blt	$t0, $t9, outer_loop
	
	#return to main
	jr	$ra
	
calcMean:

	#sum
	li	$t0, 0
	#loop variable
	li	$t9, 0
	
	meanloop:
 	#load word
 	lw	$t1, ($a0)
 	#summation
	add	$t0, $t0, $t1
	
	#move pointers
	addi	$a0, $a0, 4
	addi	$t9, $t9, 1
	#check if max nums reached
 	blt	$t9, $a1, meanloop
 	
 	#move to float registers for calculating mean
 	mtc1	$t0, $f0
 	cvt.s.w	$f0, $f0
 	
 	#loading array length
 	mtc1	$a1, $f2
 	cvt.s.w	$f2, $f2
 	
 	#division
 	div.s	$f0, $f0, $f2
 	
 	#return to main
 	jr	$ra
 	
 calcMedian:
 
 	#check if array is odd or even
 	and	$t9, $a1, 1
	bnez	$t9, isOdd
	
	#array is even
	#find offset to get first median number
	div 	$a1, $a1, 2
	mul 	$a1, $a1, 4
	sub 	$a1, $a1, 4
	#add to array address
	add 	$a0, $a0, $a1
	
	#load first number
	lw 	$t0, ($a0)
	
	#load second number
	addi 	$a0, $a0, 4
	lw 	$t1, ($a0) 
	
	#move to float registers
	mtc1 	$t0, $f0	
	mtc1 	$t1, $f2	
	
	#convert the numbers to float
	cvt.s.w $f0, $f0	
	cvt.s.w $f2, $f2	
	
	#calculate middle of two numbers
	add.s 	$f0, $f0, $f2
	l.s	$f2, two	
	div.s 	$f0, $f0, $f2
	
	#flag for even array
	li 	$v1, 0
	j	exitMedian
	isOdd:
	#calculates offset for median number
	div	$a1, $a1, 2
	mul	$a1, $a1, 4
	
	add	$a0, $a0, $s5

	#load median
	lw	$v0, ($a0)
	#saves flag for median being word
	li	$v1, 1
	
	#return to main
	exitMedian:
	jr	$ra
	
calcSD:
	#counter
 	li	$t9, 0
 	#summation variable
 	l.s	$f0, zero
 	
 	SDloop:
 	#get and convert array value
 	lwc1	$f2, ($a0)
 	cvt.s.w	$f2, $f2
 	
 	#subtract mean and square
 	sub.s	$f2, $f2, $f12
 	mul.s	$f2, $f2, $f2
 	
 	#add to sum
 	add.s	$f0, $f0, $f2
 	
	#move pointers
	addi	$a0, $a0, 4
	addi	$t9, $t9, 1
	#check if max nums reached
 	blt	$t9, $a1, SDloop
 	
 	#load n-1
 	mtc1	$a1, $f4
 	cvt.s.w	$f4, $f4
 	l.s	$f6, one
 	sub.s	$f4, $f4, $f6
 	
 	#divide sum by n-1
 	div.s	$f0, $f0, $f4
 	
 	#square root
 	sqrt.s	$f0, $f0
 	
	#return to main
 	jr	$ra
	
 	
