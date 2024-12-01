main:
        la $a0, prompt
        li $v0,  4
        syscall
        jr $ra
        .data
prompt:
        .asciiz "Well, this was a MIPStake!\n"