 #end program
 .macro done
 	li	$v0 10
 	syscall
 .end_macro
 
 #print int
.macro print_int (%x)
	lw	$a0, %x
	li	$v0, 1
	syscall
.end_macro

 #print int from register 
.macro print_int_reg (%x)
	add	$a0, $zero ,%x
	li	$v0, 1
	syscall
.end_macro

#print strings
.macro print_string (%str)
	la	$a0, %str
	li	$v0, 4
	syscall
.end_macro

#print character from register
.macro print_char (%chr)
	move	$a0, %chr
	li	$v0, 11
	syscall
.end_macro

 #get string
 .macro get_string (%file)
 	li	$v0, 8
	li	$a1, 20
	la	$a0, %file
	syscall
.end_macro

#open file
.macro	open_file (%file)
	li	$v0, 13
 	la	$a0, %file
 	li	$a1, 0
 	li	$a2, 0
 	syscall
 	bgez	$v0, noError
 	print_string(errMsg)
 	done
 noError:
 	move	$s6, $v0
 .end_macro
 	
 #read file
 .macro read_file
 	li	$v0, 14
 	move	$a0, $s6
 	la	$a1, fileBuffer
 	li	$a2, 1024
 	syscall
 .end_macro
 
 #close file
 .macro close_file
 	li	$v0, 16
 	move	$a0, $s6
 	syscall
 .end_macro
 
 #allocate heap memory
 .macro allocate_heap
 	li	$v0, 9
 	li	$a0, 1024
 	syscall
 .end_macro
 	
 #checks if string is empty and removes new line
 .macro check_string(%str)
 	#check if string is empty
	li	$t0, 0
	li	$t9, 10
	lb	$t1, %str($t0)
        addi $t0, $t0, 1
        bne	$t1, $t9, remove
        done
  remove:
  	#iterate to end of string and remove newline character
        lb	$t1, %str($t0)
        addi	$t0, $t0, 1
        bnez	$t1, remove
        beq	$a1, $t0, skip
        subiu	$t0, $t0, 2
        sb	$0, %str($t0)
    skip:
.end_macro
