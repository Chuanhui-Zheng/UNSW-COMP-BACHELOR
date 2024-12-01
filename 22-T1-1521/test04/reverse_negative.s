# Read numbers into an array until a negative number is entered
# then print the numbers in reverse order

# i in register $t0
# registers $t3, $t2 & $t1 used to hold temporary results

main:
    li   $t0, 0
loop0:
    bge  $t0, 1000, end0 # while (i < 1000) {
    li   $v0, 5
    syscall
    blt  $v0, $zero, prt
    mul  $t1, $t0, 4     #   calculate &numbers[i]
    la   $t2, numbers    #
    add  $t1, $t1, $t2   #
    sw   $v0, ($t1)      #   store them in array
    addi $t0, $t0, 1
    j    loop0
prt:
    sub  $t0, $t0, 1
    blt  $t0, $zero, end0
    mul  $t1, $t0, 4     #   calculate &numbers[i]
    la   $t2, numbers    #
    add  $t1, $t1, $t2   #
    lw   $a0, ($t1)      #   load entered number from array
    li   $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
    # sub  $t1, $t1, 4
    j    prt

end0:


    li   $v0, 0
    jr   $ra

.data
numbers:
    .space 4000