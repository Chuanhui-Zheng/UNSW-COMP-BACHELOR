#Blair z5351042
main:
        la   $a0, prompt
        li   $v0, 4
        syscall
        
        li   $v0, 5
        syscall
        move $t0, $v0
        li   $t1, 1

loop:
        bgt  $t1, $t0, end
        move $a0, $t1
        li   $v0, 1
        syscall
        
        li   $a0, '\n'
        li   $v0, 11
        syscall

        addi $t1, 1
        b    loop
end:
        li   $v0, 0
        jr   $ra

.data
        prompt: .asciiz "Enter a number: "
