# this code reads 2 lines of input and prints 42
# change it to print the results of the recursive calculation

main:
	begin
	push	$ra

	la	$a0, line1
	la	$a1, 16
	li	$v0, 8		# fgets(line1, 80, stdin);
	syscall

	la	$a0, line2
	la	$a1, 16
	li	$v0, 8		# fgets(line1, 80, stdin);
	syscall


	# THESE FOLLOWING LINES JUST PRINT 42
	# REPLACE THE LINES BELOW WITH YOUR CODE

	li	$a0, 42
	li	$v0, 1
	syscall
	li	$a0, '\n'
	li	$v0, 11
	syscall

	# REPLACE THE LINES ABOVE WITH YOUR CODE

	li	$v0, 0		# return 0

	pop	$ra
	end

	jr	$ra



function2:
	# PUT YOUR CODE FOR function2 HERE

	jr	$ra


function3:
	# PUT YOUR CODE FOR function3 HERE

	jr	$ra


# Data for the lines fgets'd in main
	.data
line1:
	.byte 0:16

line2:
	.byte 0:16
