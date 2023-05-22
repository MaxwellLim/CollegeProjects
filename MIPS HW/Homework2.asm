.data
a:	.word	0
b:	.word	0
c:	.word	0
ans1:	.word	0
ans2:	.word	0
ans3:	.word	0
space:	.asciiz	" "
name:	.asciiz
namepromt:	.asciiz	"What is your name? "
intpromt:	.asciiz	"Please enter an integer between 1-100: "
resmsg:	.asciiz	"your answers are "

.text
main:
	#promt name
	la	$a0, namepromt
	li	$v0, 4
	syscall
	
	#get name
	li	$v0, 8
	li	$a1, 20
	la	$a0, name
	syscall
	
	#promt int 1
	la	$a0, intpromt
	li	$v0 4
	syscall
	
	#get int 1
	li	$v0, 5
	syscall
	sw	$v0, a
	
	#promt int 2
	la	$a0, intpromt
	li	$v0, 4
	syscall
	
	#get int 2
	li	$v0, 5
	syscall
	sw	$v0, b
	
	#promt int 3
	la	$a0, intpromt
	li	$v0, 4
	syscall
	
	#get int 3
	li	$v0, 5
	syscall
	sw	$v0, c
	
	#loading numbers
	lw	$t1, a
	lw	$t2, b
	lw	$t3, c
	
	#calc ans1
	add	$t4, $t1, $t1
	sub	$t4, $t4, $t2
	addi	$t4, $t4, 9
	
	#save ans1
	sw	$t4, ans1
	
	#calc ans2
	sub	$t4, $t3, $t2
	subi	$t5, $t1, 5
	add	$t4, $t5, $t4
	
	#save ans2
	sw	$t4, ans2
	
	#calc ans3
	subi	$t1, $t1, 3
	addi	$t2, $t2, 4
	addi	$t3, $t3, 7
	add	$t4, $t1, $t2
	sub	$t4, $t4, $t3
	
	#save ans3
	sw	$t4, ans3
	
	#print name
	la	$a0, name
	li	$v0, 4
	syscall
	
	#print answers message
	la	$a0, resmsg
	li	$v0, 4
	syscall
	
	#print ans1
	lw	$a0, ans1
	li	$v0, 1
	syscall
	
	#print space
	la	$a0, space
	li	$v0, 4
	syscall
	
	#print ans2
	lw	$a0, ans2
	li	$v0, 1
	syscall
	
	#print space
	la	$a0, space
	li	$v0, 4
	syscall
	
	
	#print ans3
	lw	$a0, ans3
	li	$v0, 1
	syscall
	
exit:
	li $v0 10
	syscall
	
#Sample 1
#Name=James
#a=56 b=29 c=99
#ans1=92 ans2=121 ans3=-20

#Sample 1
#Name=Charles
#a=-20 = b=49 c=-100
#ans1=-80 ans2=-174 ans3=123
