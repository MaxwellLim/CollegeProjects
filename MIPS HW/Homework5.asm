.include	"Homework5Macros.asm"
.data
inputPrompt:	.asciiz "Please enter the file name to compress of <enter> to exit: "
errMsg:		.asciiz	"Error opening file. Program terminating"
origData:	.asciiz	"Original Data:\n"
compData:	.asciiz	"Compressed Data:\n"
uncompData:	.asciiz	"Uncompressed Data\n"
origFileSize:	.asciiz	"Original file size:\n"
compFileSize:	.asciiz	"Compressed file size:\n"
newLine:	.asciiz	"\n"
		.align	2
compSize:	.word
fileSize:	.word
fileName:	.ascii	""
		.space	20
		.align 2
fileBuffer:	.asciiz
		.space	1024
uncompBuffer:	.asciiz
		.space	1024

.text
restart:
	#allocates space in heap
	allocate_heap
	#save heap address in register
	add	$s1, $v0, $zero
	
	#promt and retrieve name of input file
	print_string(inputPrompt)
	get_string(fileName)
	
	#open and read file
	check_string(fileName)
	open_file(fileName)
	read_file
	sw	$v0, fileSize
	move	$t5, $v0
	close_file
	
	#makes sure there is a null terminator at end of current string
	
	la	$a0, fileBuffer
	lw	$a1, fileSize
	jal	fixBuffer
	
	#print the original file
	print_string(origData)
	print_string(fileBuffer)
	print_string(newLine)
	
	#compress the text
	la	$a0, fileBuffer
	add	$a1, $s1, $zero
	lw	$a2, fileSize
	jal	compress
	sw	$v0, compSize
	
	#print compressed file
	print_string(compData)
	add	$a0, $s1, $zero
	jal	printCompress
	print_string(newLine)
	
	#uncompress file
	add	$a0, $s1, $zero
	la	$a1, uncompBuffer
	lw	$a2, compSize
	jal	uncompress
	
	#print uncompressed file
	print_string(uncompData)
	print_string(uncompBuffer)
	print_string(newLine)
	
	#print the original file size
	print_string(origFileSize)
	print_int_reg($t5)
	print_string(newLine)
	
	#print the compressed file size
	print_string(compFileSize)
	print_int(compSize)
	print_string(newLine)
	
	j	restart
	
compress:
	add	$t8, $zero, $a2
	#total character count
	li	$v0, 0
	#characters read count
	li	$t9, 1
	lb	$t1, ($a0)
	#current character count
	li	$t0, 1
	compressLoop:
	#load new byte
	addi	$a0, $a0, 1
	lb	$t2, ($a0)
	addi	$t9, $t9, 1
	#check if same or not
	bne	$t1, $t2, newChar
	addi	$t0, $t0, 1
	j	compressLoop
	
	newChar:
	#add new char to heap
	sb	$t1, ($a1)
	addi	$a1, $a1, 1
	#add count of char to heap
	sb	$t0, ($a1)
	addi	$a1, $a1, 1
	move	$t1, $t2
	#add count to comp size
	addi	$v0, $v0, 2
	li	$t0, 1
	ble	$t9, $t8, compressLoop
	
	jr	$ra
	
	

printCompress:
	move	$t9, $a0
	printLoop:
	#load char and count
	lb	$t0, ($t9)
	lb	$t1, 1($t9)
	
	#end if end of string
	beqz	$t0, endPrint
	
	#print char and count
	print_char($t0)
	print_int_reg($t1)
	addi	$t9, $t9, 2
	
	j	printLoop
	
	endPrint:
	jr	$ra
	
uncompress:
	uncompLoop:
	#comp char count
	li	$t9, 0
	#load character and count
	lb	$t0, ($a0)
	lb	$t1, 1($a0)
	addi	$a0, $a0, 2
	addi	$t9, $t9, 2
	
	#end if char is end of string
	beqz	$t0, endUncomp
	
	li	$t8, 0
	innerLoop:
	#save to uncomp buffer
	sb	$t0, ($a1)
	addi	$t8, $t8, 1
	addi	$a1, $a1, 1
	blt	$t8, $t1, innerLoop
	
	blt	$t9, $a2, uncompLoop
	endUncomp:
	add	$t0, $zero, $zero
	sb	$t0, ($a1)
	jr	$ra

fixBuffer:
	#null
	li	$t0, 0
	#end of string
	add	$a0, $a0, $a1
	sb	$t0, ($a0)
	jr	$ra
