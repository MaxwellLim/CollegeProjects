.data
prompt:		.asciiz	"Input a string"
endmsg:		.asciiz "Goodbye\n"
endmsg2:		.asciiz "Catch you on the flip side"
string:		.space	60
words:		.asciiz " words "
characters:	.asciiz	" characters\n"
space:		.asciiz	" "
numwords:	.word	0
numchars:	.word	0

.text
main:
	#get string
	la	$a0, prompt
	la	$a1, string
	li	$a2, 60
	li	$v0, 54
	syscall
	
	#checks for good status
	bne	$a1, $zero, exit
	#function call
	jal	count
	
	sw	$v1, numwords
	sw	$v0, numchars
	
	#print input string
	la	$a0, string
	li	$v0, 4
	syscall
	
	#print numwords
	lw	$a0, numwords
	li	$v0, 1
	syscall
	
	#print words
	la	$a0, words
	li	$v0, 4
	syscall
	
	#print numchars
	lw	$a0, numchars
	li	$v0, 1
	syscall
	
	#print characters
	la	$a0, characters
	li	$v0, 4
	syscall
	
	j	main
exit:	 
	#displays end message
	la	$a0, endmsg
	la	$a1, endmsg2
	li 	$v0 59
	syscall
	
	li	$v0 10
	syscall
count:	
	#new line
	li	$t3, 10
	#space
	li	$t4, 32
	#output for number of chars
	li	$v0, 0
	#output for number of words
	li	$v1, 1
	#loadmessage to $t0
	la	$t0, string
	
	#move stack pointer down
	addi 	$sp, $sp, -4
	#push $s1 to stack
	sw 	$s1, ($sp)

loop:
	#load single char
	lb 	$t1, ($t0)
	#chack if end of message
	beq	$t1, $t3, end
	#chack and jump if is not space
	bne	$t1, $t4, char
	#increment word count
	addi	$v1, $v1, 1
char:	
	#increment char count
	addi	$v0, $v0, 1
	addi $t0, $t0, 1	#iterate the address pointer
	#loop til end
	j loop
end:
	#pop stack to $s1
	lw $s1, ($sp)
	#move stack pointer up
	addi $sp, $sp, 4
	
	#end function
	jr $ra