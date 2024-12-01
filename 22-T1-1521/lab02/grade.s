#Blair z5351042
main:
        la   $a0, prompt
        li   $v0, 4
        syscall
        li   $v0, 5
        syscall
        move $t0, $v0
        blt  $t0, 50, b1
        blt  $t0, 65, b2
        blt  $t0, 75, b3
        blt  $t0, 85, b4
        la   $a0, prompt6
        li   $v0, 4
        syscall
        b   end
b1:
        la   $a0, prompt2
        li   $v0, 4
        syscall
        b   end
b2:
        la   $a0, prompt3
        li   $v0, 4
        syscall
        b   end
b3:
        la   $a0, prompt4
        li   $v0, 4
        syscall
        b   end
b4:
        la   $a0, prompt5
        li   $v0, 4
        syscall
        b   end
end:
        li   $v0, 0
        jr   $ra        
.data
        prompt: .asciiz "Enter a mark: "
        prompt2: .asciiz "FL\n"
        prompt3: .asciiz "PS\n"
        prompt4: .asciiz "CR\n"
        prompt5: .asciiz "DN\n"
        prompt6: .asciiz "HD\n"
