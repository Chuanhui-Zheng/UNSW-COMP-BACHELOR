##Blair z5351042
main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li   $v0, 5         #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    add  $t2,  $t0, 1
loop:
    ble  $t1, $t2, end
    beq  $t2, 13, end0
    move $a0, $t2
    li   $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
end0:
    addi $t2, $t2, 1
    j    loop
end:

    li   $v0, 0         # return 0
    jr   $ra
