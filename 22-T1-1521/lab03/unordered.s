##Blair z5351042
# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0

main:
    li   $t0, 0         # i = 0
loop0:
    bge  $t0, 10, end0  # while (i < 10) {
    li   $v0, 5         #   scanf("%d", &numbers[i]);
    syscall             #
    mul  $t1, $t0, 4    #   calculate &numbers[i]
    la   $t2, numbers   #
    add  $t3, $t1, $t2  #
    sw   $v0, ($t3)     #   store entered number in array
    addi $t0, $t0, 1    #   i++;
    j    loop0          # }
end0:
    li   $t0, 0
    li   $t4, 0
    li   $t5, 0
loop1:
    bge  $t0, 10, end1
    mul  $t1, $t0, 4
    add  $t3, $t1, $t2
    lw   $v0, ($t3)
    bge  $v0, $t4, end2
    li   $t5, 1
end2:
    move $t4, $v0
    addi $t0, $t0, 1
    j    loop1;
end1:
    move $a0, $t5
    li   $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
    jr   $ra

.data

numbers:
    .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  # int numbers[10] = {0};
