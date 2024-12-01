# x in register $t0
# i in register $t1
# n_seen in register $t2
# registers $t5 and $t4 used to hold temporary results
main:

    li   $t2, 0          # n_seen = 0;
start:
    bge  $t2, 10, end    # while (n_seen < 10) {
    la   $a0, string0
    li   $v0, 4
    syscall
    li   $v0, 5
    syscall

    move $t0, $v0

    la   $t7, 0
begin:
    bge  $t7, $t2, store
    mul  $t5, $t7, 4
    la   $t4, numbers
    add  $t5, $t5, $t4
    lw   $t6, ($t5)
    beq  $t0, $t6, start
    addi $t7, $t7, 1
    j    begin

store:
    mul  $t5, $t2, 4    # calculate &numbers[n_seen]
    la   $t4, numbers
    add  $t5, $t5, $t4
    sw   $t0, ($t5)     # numbers[n_seen] = x

    addi $t2, $t2, 1
    j    start
end:
    la   $a0, string1
    li   $v0, 4
    syscall
    move $a0, $t0       # printf("%d", x)
    li   $v0, 1
    syscall
    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    li   $v0, 0
    jr   $ra

    .data

numbers:
    .space 40           # int numbers[10];

string0:
    .asciiz "Enter a number: "
string1:
    .asciiz "10th different number was: "