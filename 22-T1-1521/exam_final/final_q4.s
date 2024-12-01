# return the number of peaks in an array of integers
#
# A peak is a value that is both preceded and succeeded
# by a value smaller than itself
#
# ie:
# Both the value before and the value after the current value
# are smaller than the current value
#
# eg:
# [1, 3, 2, 5, 4, 4, 9, 0, 1, -9, -5, -7]
#     ^     ^        ^     ^       ^
# The value 3, 5, 9, 1, -5 are all peaks in this array
# So your function should return 5

.text
.globl final_q4

final_q4:
	# YOU DO NOT NEED TO CHANGE THE LINES ABOVE HERE
	move  $t0, $a0
	move  $t1, $a1
	li    $t2, 0
	li    $t3, 1
	sub   $t1, $t1, 1

loop:
	bge   $t3, $t1, end
	mul   $t4, $t3, 4
	add   $t5, $t4, $t0
	lw    $t6, ($t5)

	sub   $t4, $t3, 1
	mul   $t4, $t4, 4
	add   $t5, $t4, 4
	add   $t5, $t4, $t0
	lw    $t7, ($t5)

	addi  $t4, $t3, 1
	mul   $t4, $t4, 4
	add   $t5, $t4, $t0
	lw    $t8, ($t5)

	ble   $t6, $t7, ipp
	ble   $t6, $t8, ipp
	addi  $t2, $t2, 1

ipp:
	addi  $t3, $t3, 1
	j     loop

end:
	move $v0, $t2
	jr   $ra
