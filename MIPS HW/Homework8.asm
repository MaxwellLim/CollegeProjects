# Instructions: 
#   Connect bitmap display:
#         set pixel dim to 4x4
#         set display dim to 256x256
#	use $gp as base address
#   Connect keyboard and run
#	use w (up), s (down), a (left), d (right), space (exit)
#	all other keys are ignored
#colors
.eqv	RED	0x00FF0000
.eqv	GREEN	0x0000FF00
.eqv	BLUE	0x000000FF
.eqv	WHITE	0x00FFFFFF
.eqv	YELLOW	0x00FFFF00
.eqv	CYAN	0x0000FFFF
.eqv	MAGENTA	0x00FF00FF

#directions
.eqv	UP	-64
.eqv	DOWN	64
.eqv	RIGHT	1
.eqv	LEFT	-1

#(0,0)
.eqv ORIGIN 0x10008000

#static mem 
.eqv STATIC 0x10010000

.data
color0:		.word	MAGENTA, CYAN, YELLOW, BLUE, GREEN, RED, WHITE
color2:		.word	WHITE, MAGENTA, CYAN, YELLOW, BLUE, GREEN, RED
color3:		.word	RED, WHITE, MAGENTA, CYAN, YELLOW, BLUE, GREEN
color4:		.word	GREEN, RED, WHITE, MAGENTA, CYAN, YELLOW, BLUE
color5:		.word	BLUE, GREEN, RED, WHITE, MAGENTA, CYAN, YELLOW
color6:		.word	YELLOW, BLUE, GREEN, RED, WHITE, MAGENTA, CYAN
color7:		.word	CYAN, YELLOW, BLUE, GREEN, RED, WHITE, MAGENTA
corners:	.word	1820, 1827, 2275, 2268

.text
	# set up starting position
	la	$a0, corners
	la	$a1, color0
	jal drawBox
	
	#color changing stuff for marquee effect
	li	$s7, 7
	li	$s6, 1
loop:	 
	div	$s6, $s7
	mfhi	$s6
	
	mul	$t6, $s6, 0x1C
	add	$t6, $t6, STATIC
	
	# check for input
	lw $t0, 0xffff0000  #t1 holds if input available
    	beq $t0, 0, moveBox   #If no input, keep displaying
	
	# process input
	lw 	$s1, 0xffff0004
	beq	$s1, 32, exit	# input space
	beq	$s1, 119, up 	# input w
	beq	$s1, 115, down 	# input s
	beq	$s1, 97, left  	# input a
	beq	$s1, 100, right	# input d
	# invalid input, ignore
	j	moveBox
	
	
	
up:
	#clear current position
	la	$a0, corners
	jal 	blackBox
	
	#move corners
	la	$t1, corners
	li	$t9, 0
	
upLoop:
	lw	$t2, ($t1)		#load corner
	addi	$t2, $t2, UP		#update corner
	sw	$t2, ($t1)		#save corner
	addi	$t9, $t9, 1		#update count
	addi	$t1, $t1, 4		#update pointer
	ble	$t9, 4, upLoop		#do for all corners
	
	j	moveBox			#draw new box

down:
	#clear current position
	la	$a0, corners
	jal 	blackBox
	
	#move corners
	la	$t1, corners
	li	$t9, 0
	
downLoop:
	lw	$t2, ($t1)		#load corner
	addi	$t2, $t2, DOWN		#update corner
	sw	$t2, ($t1)		#save corner
	addi	$t9, $t9, 1		#update count
	addi	$t1, $t1, 4		#update pointer
	ble	$t9, 4, downLoop	#do for all corners
	
	j	moveBox
	
left:
	#clear current position
	la	$a0, corners
	jal 	blackBox
	
	#move corners
	la	$t1, corners
	li	$t9, 0
	
leftLoop:
	lw	$t2, ($t1)		#load corner
	addi	$t2, $t2, LEFT		#update corner
	sw	$t2, ($t1)		#save corner
	addi	$t9, $t9, 1		#update count
	addi	$t1, $t1, 4		#update pointer
	ble	$t9, 4, leftLoop	#do for all corners
	
	j	moveBox
	
right:
	#clear current position
	la	$a0, corners
	jal 	blackBox
	
	#move corners
	la	$t1, corners
	li	$t9, 0
	
rightLoop:
	
	lw	$t2, ($t1)		#load corner
	addi	$t2, $t2, RIGHT		#update corner
	sw	$t2, ($t1)		#save corner
	addi	$t9, $t9, 1		#update count
	addi	$t1, $t1, 4		#update pointer
	ble	$t9, 4, rightLoop	#do for all corners
	
	
	# process valid input
moveBox:
	#draw box in new position
	la	$a0, corners
	move	$a1, $t6
	jal drawBox
	
	addi	$s6, $s6, 1
	#loop program
	j loop

	
	#end program	
exit:	li	$v0, 10
	syscall



drawBox:
#$t1=address
#$t2=color
#$t0=counter
	move	$t5, $a0
#draw top side
	
	li	$t0, 0 
	lw	$t1, ($t5)
	move	$t2, $a1
drawTop:
	addi	$a0, $zero, 5
	li	$v0, 32
	syscall				#5ms delay
	mul	$s1, $t1, 4	  	# multiply by 4 to get word offset
	add	$s1, $s1, ORIGIN	# add to base address
	lw	$t3, ($t2)
	sw	$t3, ($s1)	 	# store color at memory location
	addi	$t0, $t0, 1		#increment count
	addi	$t1, $t1, RIGHT		#next address
	addi	$t2, $t2, 4		#next color
	blt	$t0, 7, drawTop
	
#draw right side
	li	$t0, 0 
	lw	$t1, 4($t5)
	move	$t2, $a1
drawRight:
	addi	$a0, $zero, 5
	li	$v0, 32
	syscall				#5ms delay
	mul	$s1, $t1, 4	  	# multiply by 4 to get word offset
	add	$s1, $s1, ORIGIN	# add to base address
	lw	$t3, ($t2)
	sw	$t3, ($s1)	 	# store color at memory location
	addi	$t0, $t0, 1		#increment count
	addi	$t1, $t1, DOWN		#next address
	addi	$t2, $t2, 4		#next color
	blt	$t0, 7, drawRight
	
#draw bottom side
	li	$t0, 0 
	lw	$t1, 8($t5)
	move	$t2, $a1
drawBottom:
	addi	$a0, $zero, 5
	li	$v0, 32
	syscall				#5ms delay
	mul	$s1, $t1, 4	  	# multiply by 4 to get word offset
	add	$s1, $s1, ORIGIN	# add to base address
	lw	$t3, ($t2)
	sw	$t3, ($s1)	 	# store color at memory location
	addi	$t0, $t0, 1		#increment count
	addi	$t1, $t1, LEFT		#next address
	addi	$t2, $t2, 4		#next color
	blt	$t0, 7, drawBottom
	
#draw left side
	li	$t0, 0 
	lw	$t1, 12($t5)
	move	$t2, $a1
drawLeft:
	addi	$a0, $zero, 5
	li	$v0, 32
	syscall				#5ms delay
	mul	$s1, $t1, 4	  	# multiply by 4 to get word offset
	add	$s1, $s1, ORIGIN	# add to base address
	lw	$t3, ($t2)
	sw	$t3, ($s1)	 	# store color at memory location
	addi	$t0, $t0, 1		#increment count
	addi	$t1, $t1, UP		#next address
	addi	$t2, $t2, 4		#next color
	blt	$t0, 7, drawLeft
	
	jr	$ra
	
blackBox:
#$t1=address
#$t0=counter
	move	$t5, $a0
	li	$t3, 0
#draw top side
	
	li	$t0, 0 
	lw	$t1, ($t5)
blackTop:
	addi	$a0, $zero, 5
	li	$v0, 32
	syscall				#5ms delay
	mul	$s1, $t1, 4	  	# multiply by 4 to get word offset
	add	$s1, $s1, ORIGIN	# add to base address
	sw	$t3, ($s1)	 	# store color at memory location
	addi	$t0, $t0, 1		#increment count
	addi	$t1, $t1, RIGHT		#next address
	addi	$t2, $t2, 4		#next color
	blt	$t0, 7, blackTop
	
#draw right side
	li	$t0, 0 
	lw	$t1, 4($t5)
blackRight:
	addi	$a0, $zero, 5
	li	$v0, 32
	syscall				#5ms delay
	mul	$s1, $t1, 4	  	# multiply by 4 to get word offset
	add	$s1, $s1, ORIGIN	# add to base address
	sw	$t3, ($s1)	 	# store color at memory location
	addi	$t0, $t0, 1		#increment count
	addi	$t1, $t1, DOWN		#next address
	addi	$t2, $t2, 4		#next color
	blt	$t0, 7, blackRight
	
#draw bottom side
	li	$t0, 0 
	lw	$t1, 8($t5)
blackBottom:
	addi	$a0, $zero, 5
	li	$v0, 32
	syscall				#5ms delay
	mul	$s1, $t1, 4	  	# multiply by 4 to get word offset
	add	$s1, $s1, ORIGIN	# add to base address
	sw	$t3, ($s1)	 	# store color at memory location
	addi	$t0, $t0, 1		#increment count
	addi	$t1, $t1, LEFT		#next address
	addi	$t2, $t2, 4		#next color
	blt	$t0, 7, blackBottom
	
#draw left side
	li	$t0, 0 
	lw	$t1, 12($t5)
blackLeft:
	addi	$a0, $zero, 5
	li	$v0, 32
	syscall				#5ms delay
	mul	$s1, $t1, 4	  	# multiply by 4 to get word offset
	add	$s1, $s1, ORIGIN	# add to base address
	sw	$t3, ($s1)	 	# store color at memory location
	addi	$t0, $t0, 1		#increment count
	addi	$t1, $t1, UP		#next address
	addi	$t2, $t2, 4		#next color
	blt	$t0, 7, blackLeft
	
	jr	$ra
