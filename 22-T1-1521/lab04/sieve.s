#Blair z5351042
# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:
    li   $t0, 0
circ1:
    bge  $t0, 1000, stop1
    la   $t1, prime
    add  $t2, $t1, $t0    # $t2 = &prime[i]
    li   $t6, 1
    sb   $t6, ($t2)
    addi $t0, $t0, 1
    j    circ1
stop1:
    li   $t0, 2
circ2:
    bge  $t0, 1000, end
    add  $t2, $t1, $t0
    lb   $t3, ($t2)
    bne  $t3, 1, stop2
    move $a0, $t0
    li   $v0, 1           # print i 
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
    mul  $t5, $t0, 2      # $t5 = j = i * 2
circ3:
    bge  $t5, 1000, stop2
    add  $t2, $t1, $t5
    li   $t8, 0
    sb   $t8, ($t2)
    add  $t5, $t5, $t0
    j    circ3
stop2:
    addi $t0, $t0, 1
    j    circ2
end:
    li $v0, 0           # return 0
    jr $31

.data
prime:
    .space 1000