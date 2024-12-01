# given one integer value return the right justified version of the value.
# right-justification is (in this case)
# the process of removing all zeros from the right side of the value
# eg:
# given  (in $a0) 0b00000000000000000000000001101000
# return (in $v0) 0b00000000000000000000000000001101

.text
.globl final_q2

final_q2:
    # YOU DO NOT NEED TO CHANGE THE LINES ABOVE HERE
    li $t0, 1
    li $t1, 0
    move $t2, $a0

loop:
    bge  $t1, 32, end
    and  $t3, $t2, $t0
    bne  $t3, 0, end
    srl  $t2, $t2, 1
    addi $t1, $t1,1
    j    loop

end:
    move $v0, $t2
    jr $ra
