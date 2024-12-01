 .data
    prompt_str: .asciiz "Enter a random seed: "
    result_str: .asciiz "The random result is: "

.text
main:
    li  $a0, prompt_str
    li  $v0, 4
    syscall
    li  $v0, 5
    syscall
    begin
    push $ra               # save $ra onto stack
    move $a0, $v0          # seed_rand(random_seed)
    jal  seed_rand
    pop  $ra               # recover $ra from stack
    push $ra
    li   $a0, 100          
    jal  rand
    pop  $ra               # recover $ra from stack
    push $ra
    move $a0, $v0          
    jal  add_rand
    pop  $ra
    push $ra
    move $a0, $v0
    jal  sub_rand          # sub_rand(value)
    pop  $ra             
    push $ra
    move $a0, $v0          
    jal  seq_rand          # seq_rand(value)
    pop  $ra
    la   $a0, result_str
    li   $v0, 4
    syscall
    move $a0, $v1
    li   $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
    jr   $ra

##
## The following are two utility functions, provided for you.
##
## You don't need to modify any of the following.
## But you may find it useful to read through.
## You'll be calling these functions from your code.
##

OFFLINE_SEED = 0x7F10FB5B

########################################################################
# .DATA
.data

# int random_seed;
.align 2
random_seed:    .space 4


########################################################################
# .TEXT <seed_rand>
.text

# DO NOT CHANGE THIS FUNCTION

add_rand:
    push $ra
    move $v1, $a0
    li   $a0, 0xFFFF
    jal  rand               # rand(oxFFFF)
    pop  $ra                
    add  $v0, $v0, $v1      # value + rand(0xFFFF)
    jr   $ra
sub_rand:
    push $ra
    move $v1, $a0
    jal  rand
    pop  $ra
    sub  $v0, $v1, $v0     # value - rand(value)
    jr   $ra
seq_rand:
    move $v1, $a0
    push $ra
    li   $a0, 100
    jal  rand              # rand(100)\
    pop  $ra
    move $t2, $v0
    li   $t1, 0
    j    floop
floop:
    bge  $t1, $t2, end     # if(i >= limit) goto end
    push $ra
    move $a0, $v1
    jal  add_rand
    pop  $ra
    move $v1, $v0
    addi $t1, $t1, 1
    j    floop
end:
    jr   $ra

seed_rand:
    # Args:
    #   - $a0: unsigned int seed
    # Returns: void
    #
    # Frame:    []
    # Uses:     [$a0, $t0]
    # Clobbers: [$t0]
    #
    # Locals:
    # - $t0: offline_seed
    #
    # Structure:
    #   seed_rand

    li  $t0, OFFLINE_SEED # const unsigned int offline_seed = OFFLINE_SEED;
    xor $t0, $a0          # random_seed = seed ^ offline_seed;
    sw  $t0, random_seed

    jr  $ra               # return;

########################################################################
# .TEXT <rand>
.text

# DO NOT CHANGE THIS FUNCTION

rand:
    # Args:
    #   - $a0: unsigned int n
    # Returns:
    #   - $v0: int
    #
    # Frame:    []
    # Uses:     [$a0, $v0, $t0]
    # Clobbers: [$v0, $t0]
    #
    # Locals:
    #   - $t0: random_seed
    #
    # Structure:
    #   rand

    lw      $t0, random_seed # unsigned int rand = random_seed;
    multu   $t0, 0x5bd1e995  # rand *= 0x5bd1e995;
    mflo    $t0
    addiu   $t0, 12345       # rand += 12345;
    sw      $t0, random_seed # random_seed = rand;

    remu    $v0, $t0, $a0    #    rand % n
    jr      $ra              # return rand % n;