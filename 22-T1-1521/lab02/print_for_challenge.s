#Blair z5351042
main:
        li   $a0, 'H'
        li   $v0, 11
        syscall
        li   $a0, 'i'
        li   $v0, 11
        syscall
        li   $a0, '\n'
        li   $v0, 11
        syscall
        jr   $ra
