#Blair z5351042
main:
    la   $a0, prompt1
    li   $v0, 4
    syscall
    li   $v0, 5
    syscall
    move $t0, $v0
    la   $a0, prompt2
    li   $v0, 4
    syscall
    li   $v0, 5
    syscall
    move $t1, $v0
    la   $a0, prompt3
    li   $v0, 4
    syscall
    li   $v0, 5
    syscall
    move $t2, $v0
    beq  $t0, $t1, end
    beqz $t0, end
    slt  $t3, $t1, $t0
    slt  $t4, $t2, $zero
    add  $t4, $t3, $t4
    beq  $t4, 2, loop1
    beqz $t4, loop2
    b    end
loop1:
    blt $t0, $t1, end
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
    add $t0, $t0, $t2
    b   loop1
loop2:
    bgt $t0, $t1, end
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
    add $t0, $t0, $t2
    b   loop2
end:
    li   $v0, 0
    jr   $ra

.data
    prompt1: .asciiz "Enter the starting number: "
    prompt2: .asciiz "Enter the stopping number: "
    prompt3: .asciiz "Enter the step size: "
