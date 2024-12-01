########################################################################
# COMP1521 22T1 -- Assignment 1 -- Mipstermind!
#
#
# !!! IMPORTANT !!!
# Before starting work on the assignment, make sure you set your tab-width to 8!
# It is also suggested to indent with tabs only.
# Instructions to configure your text editor can be found here:
#   https://cgi.cse.unsw.edu.au/~cs1521/22T1/resources/mips-editors.html
# !!! IMPORTANT !!!
#
#
# This program was written by Blair (z5351042)
# on 3/25/2022
#
# Version 1.0 (28-02-22): Team COMP1521 <cs1521@cse.unsw.edu.au>
#
########################################################################

#![tabsize(8)]

# Constant definitions.
# DO NOT CHANGE THESE DEFINITIONS

TURN_NORMAL = 0
TURN_WIN    = 1
NULL_GUESS  = -1


########################################################################
# .DATA
# YOU DO NOT NEED TO CHANGE THE DATA SECTION
.data

# int correct_solution[GUESS_LEN];
.align 2
correct_solution:	.space GUESS_LEN * 4

# int current_guess[GUESS_LEN];
.align 2
current_guess:		.space GUESS_LEN * 4

# int solution_temp[GUESS_LEN];
.align 2
solution_temp:		.space GUESS_LEN * 4


guess_length_str:	.asciiz "Guess length:\t"
valid_guesses_str:	.asciiz "Valid guesses:\t1-"
number_turns_str:	.asciiz "How many turns:\t"
enter_seed_str:		.asciiz "Enter a random seed: "
you_lost_str:		.asciiz "You lost! The secret codeword was: "
turn_str_1:		.asciiz "---[ Turn "
turn_str_2:		.asciiz " ]---\n"
enter_guess_str:	.asciiz "Enter your guess: "
you_win_str:		.asciiz "You win, congratulations!\n"
correct_place_str:	.asciiz "Correct guesses in correct place:   "
incorrect_place_str:	.asciiz "Correct guesses in incorrect place: "

############################################################
####                                                    ####
####   Your journey begins here, intrepid adventurer!   ####
####                                                    ####
############################################################


########################################################################
#
# Implement the following 8 functions,
# and check these boxes as you finish implementing each function
#
#  - [ ] main
#  - [ ] play_game
#  - [ ] generate_solution
#  - [ ] play_turn
#  - [ ] read_guess
#  - [ ] copy_solution_into_temp
#  - [ ] calculate_correct_place
#  - [ ] calculate_incorrect_place
#  - [X] seed_rand  (provided for you)
#  - [X] rand       (provided for you)
#
########################################################################


########################################################################
# .TEXT <main>
.text
main:
	# Args:     void
	# Returns:
	#   - $v0: int
	#
	# Frame:    [$ra, ...]
	# Uses:     [$v0, $a0, ...]
	# Clobbers: [$v0, $a0, ...]
	#
	# Locals:
	#   - []
	#
	# Structure:
	#   main
	#   -> [prologue]
	#   -> body
	#   -> [epilogue]

main__prologue:
	begin                   # begin a new stack frame
	push	$ra             # | $ra

main__body:
	# printf("Guess length: %d\n", GUESS_LEN);
	li		$v0, 4
	la		$a0, guess_length_str
	syscall                 # guess_length_str
	li		$v0, 1
	li		$a0, GUESS_LEN
	syscall                 # printf("%d", GUESS_LEN);
	li		$v0, 11
	li		$a0, '\n'
	syscall                 # printf("\n");
	# printf("Valid guesses: 1-%d\n", GUESS_CHOICES);
	li		$v0, 4
	la		$a0, valid_guesses_str
	syscall                 # printf("Valid guesses: 1-");
	li		$v0, 1
	li		$a0, GUESS_CHOICES
	syscall                 # GUESS_CHOICES
	li		$v0, 11
	li		$a0, '\n'
	syscall                 # printf("\n");
	# printf("How many turns: %d\n\n", MAX_TURNS);
	li		$v0, 4
	la		$a0, number_turns_str
	syscall                 # printf("How many turns: ");
	li		$v0, 1
	li		$a0, MAX_TURNS
	syscall					# printf("%d", MAX_TURNS);
	li		$v0, 11
	li		$a0, '\n'
	syscall                 # printf("\n");
	syscall                 # printf("\n");
	li		$v0, 4			# print_string
	la		$a0, enter_seed_str		
	syscall					# enter_seed_str
	li   	$v0, 5
	syscall					# scanf("%d", &random_seed);
	move 	$a0, $v0		# $a0 = $v0 = random_seed
	push 	$ra	
	jal  	seed_rand
	pop		$ra
	move 	$s0, $t0

	push 	$ra
	jal  	play_game
	pop  	$ra

main__epilogue:
	pop		$ra
	end                     # ends the current stack frame

	li		$v0, 0
	jr		$ra             # return 0;





########################################################################
# .TEXT <play_game>
.text
play_game:
	# Args:     void
	# Returns:  void
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - [...]
	#
	# Structure:
	#   play_game
	#   -> [prologue]
	#   -> body
	#   -> [epilogue]

play_game__prologue:
	push 	$ra
	push    $s3
	push 	$s5
	push	$a1
	jal		generate_solution	# generate_solution()
	li  	$s2, MAX_TURNS
	li		$a1, 0	# turn = 0
	li  	$s5, TURN_WIN

	
	
play_game__body:

	bge 	$a1, $s2, last_statement
	push	$ra
	push	$s2
	jal		play_turn
	move 	$a0, $v0							# play_turn(turn)
	move	$s3, $a0
	pop    	$s2
	pop     $ra
	beq		$s3, $s5, play_game__epilogue
	
	add		$a1, $a1, 1
	j		play_game__body
last_statement:
	li		$a0, you_lost_str					# printf("You lost! The secret codeword was: ")
	li		$v0, 4								# $v0 =4 
	syscall
	li		$t1, 0								# i =0 
	li		$t2, GUESS_LEN
loop1:	
	bge		$t1, $t2, final_print
	mul		$t7, $t1, 4
	la		$t3, correct_solution
	add		$t5, $t3, $t7
	lw		$a0, 0($t5)
	li		$v0, 1								# printf("%d ", correct_solution[i]);
	syscall				
	li		$a0, ' '
	li		$v0, 11	
	syscall
	add		$t1, $t1, 1
	j		loop1
	
final_print:
	li		$a0, '\n' 							#  printf("\n");
	li		$v0, 11	
	syscall	

play_game__epilogue:
	pop		$a1
	pop 	$s5
	pop		$s3
	pop		$ra
	jr		$ra             					# return;

########################################################################
# .TEXT <generate_solution>
.text
generate_solution:
	# Args:     void
	# Returns:  void
	#
	# Frame:    [$ra]
	# Uses:     [$s1, $s2, $a0, $v0, $t2-$t5]
	# Clobbers: [$s1]
	#
	# Locals:
	#   - $s2 [GUESS_LEN]
	#   - $a0 [GUESS_CHOICES]
	#
	# Structure:
	#   generate_solution
	#   -> [prologue]
	#   -> body
	#   -> [epilogue]

generate_solution__prologue:
	li		$s1, 0			# i = 0
	li  	$s2, GUESS_LEN	

generate_solution__body:
	bge		$s1, $s2, generate_solution__epilogue
	li  	$a0, GUESS_CHOICES
	push 	$ra
	jal 	rand
	pop  	$ra
	move 	$t5, $v0
	addi 	$t5, $t5, 1		# $t5 = $t5 + 1
	mul 	$t2, $s1, 4
	la  	$t7, correct_solution
	add 	$t3, $t2, $t7
	sw  	$t5, ($t3) 		# correct_solution[i] = $t
	addi 	$s1, $s1, 1		# i++;
	j   	generate_solution__body	

generate_solution__epilogue:
	jr		$ra             # return;



########################################################################
# .TEXT <play_turn>
.text
play_turn:
	# Args:
	#   - $a0: int
	# Returns:
	#   - $v0: int
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - [...]
	#
	# Structure:
	#   play_turn
	#   -> [prologue]
	#   -> body
	#   -> [epilogue]

play_turn__prologue:
	push 	$ra
	push	$a1
	push	$s6
	push    $s5
	push	$s3
	li		$s3, GUESS_LEN		# $s3 = GUESS_LEN
	
	# move $a0, $s1
	# li   $v0, 1
	# syscall
play_turn__body:

	
	li		$a0, turn_str_1  				# printf("---[ Turn);
	li  	$v0, 4
	syscall
	add 	$a1, $a1, 1

	move 	$a0, $a1						# printf(%d, turn + 1)
	li		$v0, 1
	syscall
	li		$a0, turn_str_2					# printf(" ]---")
	li  	$v0, 4
	syscall
	li		$a0, enter_guess_str			# enter_guess_str
	li		$v0, 4
	syscall
	jal		read_guess
	
	jal 	copy_solution_into_temp	
	 
	push	$ra
	jal		calculate_correct_place
	move 	$a0, $v0
	move 	$s5, $a0						# int correct_place   = calculate_correct_place();
	pop		$ra
	push	$ra
	jal		calculate_incorrect_place
	move 	$a0, $v1
	move 	$s6, $a0						# int incorrect_place = calculate_incorrect_place();
	pop		$ra
	beq		$s5, $s3, win_fun
	li		$a0, correct_place_str			# correct_place_str
	li		$v0, 4		
	syscall
	move 	$a0, $s5						# printf("%d" , correct_place)
	li		$v0, 1
	syscall
	li		$a0, '\n'						# printf("%c", '\n') 
	li		$v0, 11			  
	syscall
	li		$a0, incorrect_place_str 		# printf("Correct guesses in incorrect place:")
	li		$v0, 4		
	syscall
	move 	$a0, $s6						# printf("%d",incorrect_place)
	li		$v0, 1		
	syscall
	li		$a0, '\n'						# printf("%c", '\n') 
	li		$v0, 11			  
	syscall
	li		$t2, TURN_NORMAL				# $t2 = TURN_WIN
	move 	$v0, $t2						#  return TURN_NORMAL
	# move 	$a0, $v1
	# li		$v0, 1
	# syscall
	j		play_turn__epilogue
	

win_fun:
	li		$a0, you_win_str 		# you_win_str
	li		$v0, 4
	syscall 
	li		$t1, TURN_WIN		# $t1 = TURN_WIN
	move 	$v0, $t1		# return TURN_WIN
play_turn__epilogue:
	pop     $s3
	pop		$s5
	pop		$s6
	pop 	$a1
	pop 	$ra
	jr		$ra             # return;


########################################################################
# .TEXT <read_guess>
.text
read_guess:
	# Args:     void
	# Returns:  void
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - [...]
	#
	# Structure:
	#   read_guess
	#   -> [prologue]
	#   -> body
	#   -> [epilogue]

read_guess__prologue:
	push	$ra
	li	$s0, 0				# int n_guess = 0	
	li  $s2, GUESS_LEN
read_guess__body:
	bge	$s0, $s2, read_guess__epilogue
	li	$v0, 5				# scanf("%d", &guess);
	syscall

	move 	$s1, $v0
	mul	$t2, $s0, 4	   
	la  $t7, current_guess	# current_guess[n_guess] = guess;
	add $t3, $t7, $t2
	sw  $s1, 0($t3)

	# move $a0, $s1
	# li   $v0, 1
	# syscall
	add $s0, $s0, 1			# n_guess ++
	j		read_guess__body# jump to read_guess_body

read_guess__epilogue:
	pop $ra
	jr	$ra             	# return;

########################################################################
# .TEXT <copy_solution_into_temp>
.text
copy_solution_into_temp:
	# Args:     void
	# Returns:  void
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - [...]
	#
	# Structure:
	#   copy_solution_into_temp
	#   -> [prologue]
	#   -> body
	#   -> [epilogue]

copy_solution_into_temp__prologue:
	push 	$ra
	push	$s1
	la		$t1, solution_temp
	la		$t2, correct_solution
	li		$t0, 0 				# int i = 0
	li		$s1, GUESS_LEN		# $t1 =G 
copy_solution_into_temp__body:
	bge		$t0, $s1, copy_solution_into_temp__epilogue
	mul		$t7, $t0, 4
	add		$t3, $t7, $t1
	add		$t5, $t7, $t2
	lw		$t4, 0($t5)
	sw		$t4, 0($t3)			#  solutoin_temp[i] = correct_solution[i];
	# move 	$a0, $t4			# $a0 = $61
	# li		$v0, 1
	# syscall
	addi		$t0, $t0, 1		# i ++;
	j		copy_solution_into_temp__body
	
copy_solution_into_temp__epilogue:
	pop		$s1
	pop		$ra
	jr		$ra             	# return;

########################################################################
# .TEXT <calculate_correct_place>
.text
calculate_correct_place:
	# Args:     void
	# Returns:
	#   - $v0: int
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - [...]
	#
	# Structure:
	#   calculate_correct_place
	#   -> [prologue]
	#   -> body
	#   -> [epilogue]

calculate_correct_place__prologue:
	push	$ra
	push    $s3
	push    $s2
	push    $a1

	li		$a1, 0 				# total = 0 
	li		$t0, 0				# guess_index = 0
	li		$s3, GUESS_LEN		# $s1 =GUESS_LEN 
	li		$s2, NULL_GUESS		# $s2 =NULL_GUESS 
	
calculate_correct_place__body:
	bge		$t0, $s3, calculate_correct_place__epilogue
	
	mul		$t1, $t0, 4	   
	la  	$t2, current_guess	# int guess = current_guess[guess_index]
	add 	$t7, $t2, $t1
	lw  	$t3, 0($t7)
	mul		$t1, $t0, 4
	la		$t2, solution_temp
	add		$t7, $t2, $t1			 
	lw		$t5, 0($t7)			# solution_temp[guess_index]
	beq		$t3, $t5, statement

	add		$t0, $t0, 1			# guess_index ++
	j		calculate_correct_place__body
statement:	
	add		$a1, $a1, 1			# total ++;
	
	mul		$t1, $t0, 4			# current_guess[guess_index] = NULL_GUESS;
	la		$t2, current_guess
	add		$t7, $t2, $t1		
	sw		$s2, 0($t7)			 

	mul		$t1, $t0, 4			# solution_temp[guess_index] = NULL_GUESS;
	la		$t2, solution_temp	# 
	add		$t3, $t2, $t1
	sw		$s2, 0($t3)
	add		$t0, $t0, 1		# guess_index ++
	j		calculate_correct_place__body
calculate_correct_place__epilogue:
	move 	$v0, $a1			# $a0 = a21
	
	# li		$v0, 1			# $v0 =1 
	# syscall
	# li		$a0, '\n'
	# li		$v0, 11			# $v0 =11 
	# syscall
	pop		$a1
	pop     $s2
	pop		$s3
	pop		$ra

	jr		$ra            		# return total;
					

########################################################################
# .TEXT <calculate_incorrect_place>
.text
calculate_incorrect_place:
	# Args:     void
	# Returns:
	#   - $v0: int
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - [...]
	#
	# Structure:
	#   calculate_incorrect_place
	#   -> [prologue]
	#   -> body
	#   -> [epilogue]

calculate_incorrect_place__prologue:
	push	$ra
	push	$s0
	push	$s3
	push    $a1
	li		$a1, 0 				# int total = 0;
	li		$t0, 0				# int guess_index = 0
	li		$s0, NULL_GUESS		# $s0 = NULL_GUESS
	li		$s3, GUESS_LEN		# $s3 =GUESS_LEN 
	

calculate_incorrect_place__body:
	bge		$t0, $s3, calculate_incorrect_place__epilogue
	mul		$t2, $t0, 4
	la		$t7, current_guess		
	add		$t3, $t7, $t2
	lw		$t5, 0($t3)			# find guess: $t5
	li		$t1, 0
	bne		$t5, $s0, statement1
	add		$t0, $t0, 1			# guess_index ++
	j		calculate_incorrect_place__body

statement1:	
	bge		$t1, $s3, statement7
	
	mul		$t2, $t1, 4
	la		$t7, solution_temp
	add		$t3, $t7, $t2		# $t3 = $31 + 2t2
	lw		$t4, 0($t3)			# solution_temp[solution_index]
	mul		$t2, $t0, 4
	la		$t7, current_guess		
	add		$t3, $t7, $t2
	lw		$t5, 0($t3)		# find guess
	beq		$t4, $t5, statement2
	add		$t1, $t1, 1			# solution_index++
	j		statement1
	
statement2:
	add		$a1, $a1, 1			# total ++
	mul		$t2, $t1, 4
	la		$t7, solution_temp
	add		$t3, $t7, $t2
	sw		$s0, 0($t3)
	add		$t0, $t0, 1			# solution index ++
	# add		$t1, $t1, 1		# guess_index ++
	j		calculate_incorrect_place__body
statement7:
	add		$t0, $t0, 1			# $t0 = $t1 + $t2
	j		calculate_incorrect_place__body
calculate_incorrect_place__epilogue:
	move 	$v1, $a1			# $a0 = a1
	pop		$a1
	pop		$s3
	pop		$s0
	pop		$ra	
	jr		$ra             	# return;




########################################################################
####                                                                ####
####        STOP HERE ... YOU HAVE COMPLETED THE ASSIGNMENT!        ####
####                                                                ####
########################################################################

##
## The following are two utility functions, provided for you.
##
## You don't need to modify any of the following.
## But you may find it useful to read through.
## You'll be calling these functions from your code.
##


########################################################################
# .DATA
# DO NOT CHANGE THIS DATA SECTION
.data

# int random_seed;
.align 2
random_seed:		.space 4


########################################################################
# .TEXT <seed_rand>
# DO NOT CHANGE THIS FUNCTION
.text
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

	li	$t0, OFFLINE_SEED # const unsigned int offline_seed = OFFLINE_SEED;
	xor	$t0, $a0          # random_seed = seed ^ offline_seed;
	sw	$t0, random_seed

	jr	$ra               # return;




########################################################################
# .TEXT <rand>
# DO NOT CHANGE THIS FUNCTION
.text
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
	# - $t0: random_seed
	#
	# Structure:
	#   rand

	lw	$t0, random_seed  # unsigned int rand = random_seed;
	multu	$t0, 0x5bd1e995   # rand *= 0x5bd1e995;
	mflo	$t0
	addiu	$t0, 12345        # rand += 12345;
	sw	$t0, random_seed  # random_seed = rand;

	remu	$v0, $t0, $a0     # rand % n
	jr	$ra               # return;
