#Blair z5351042
main:
        li   $a0, 42
        li   $v0, 1
        syscall
        li   $a0, '\n'
        li   $v0, 11
        syscall
        jr   $ra