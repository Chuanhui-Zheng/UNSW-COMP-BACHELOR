# print a triangle of asterisks

main:
    li      $v0, 5         #   scanf("%d", &x);
    syscall
    move    $t0, $v0
    li      $t1, 0

    # YOU DO NOT NEED TO CHANGE THE LINES ABOVE HERE
    # CHANGE THE BELOW LINES TO YOUR CODE

loop1:
    bge     $t1, $t0, main__end
    li      $t2, 0

loop2:
    bgt     $t2, $t1, ipp
    li      $a0, '*'       #   printf("%c\n", '*');
    li      $v0, 11
    syscall
    addi    $t2, $t2, 1
    j       loop2

ipp:
    addi    $t1, $t1, 1
    li      $a0, '\n'      #   printf("%c", '\n');
    li      $v0, 11
    syscall
    j       loop1

    # CHANGE THE ABOVE LINES TO YOUR CODE
    # YOU DO NOT NEED TO CHANGE THE LINES BELOW HERE

main__end:
    li      $v0, 0         # return 0
    jr      $ra
