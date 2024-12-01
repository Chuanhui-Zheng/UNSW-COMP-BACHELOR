##Blair z5351042

# read a line and print whether it is a palindrom

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    li   $t0, 0
loop1:
    add  $t7, $a0, $t0
    lb   $t4, ($t7)
    addi $t0, $t0, 1
    bne  $t4, 0, loop1

    sub  $t0, $t0, 1
    li   $t7, 0
    sub	 $t4, $t0, 2

loop2:
    bge  $t7, $t4, finish

    add  $t3, $a0, $t7
    add  $t1, $a0, $t4
    lb   $t2, ($t3)
    lb   $t0, ($t1)
    beq  $t2, $t0, range
    la   $a0, not_palindrome
    li   $v0, 4
    syscall

    li   $v0, 0          # return 0
    jr   $ra

range:
    addi $t7, $t7, 1
    sub  $t4, $t4, 1

    j    loop2

finish:
    la   $a0, palindrome
    li   $v0, 4
    syscall

    li   $v0, 0          # return 0
    jr   $ra


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256