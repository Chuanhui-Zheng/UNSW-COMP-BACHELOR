##Blair z5351042
main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li   $t1, 0
loop1:
    ble  $t0, $t1, end
    li   $t2, 0
loop2:
    ble  $t0, $t2, end1
    li   $a0, '*'
    li   $v0, 11
    syscall
    addi $t2, $t2, 1
    b    loop2
end1:
    addi $t1, $t1, 1
    li   $a0, '\n'
    li   $v0, 11
    syscall
    b    loop1
end:

    li   $v0, 0         # return 0
    jr   $ra
