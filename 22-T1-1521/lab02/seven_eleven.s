#Blair z5351042
main:
        la   $a0, prompt
        li   $v0, 4
        syscall
        li   $v0, 5
        syscall
        move $t0, $v0
        li   $t1, 7
loop:
        bge  $t1, $t0 ,end
        rem  $t2, $t1, 7
        rem  $t3, $t1, 11
        beqz $t2, out
        beqz $t3, out
        b    loop2
loop2:
        addi $t1, $t1, 1
        b    loop
out:
        move   $a0, $t1
        li   $v0, 1
        syscall
        li   $a0, '\n'
        li   $v0, 11
        syscall
        b    loop2
end:
        li   $v0, 0
        jr   $ra

.data
        prompt: .asciiz "Enter a number: "
