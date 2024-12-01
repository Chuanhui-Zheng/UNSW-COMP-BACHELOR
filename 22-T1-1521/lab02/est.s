#Blair z5351042
main:
        la $t7, prompt
        move $a0, $t7
        li $v0, 4
        syscall
        li   $a0, '\n'
        li   $v0, 11
        syscall
        jr $ra
.data
        prompt: .asciiz "Enter how many: "

