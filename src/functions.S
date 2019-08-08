.globl set_initial_square
.globl moveCursor

.extern generate_rand
.extern generate_initial_pipe
.extern initialPipePosition
.extern pipeMap
.extern cursorPosition
.extern place_pipe

.text


set_initial_square:
    addi    $sp, $sp, -12
    sw      $ra, 0($sp)
    sw      $s0, 4($sp)
    sw      $s1, 8($sp)

    jal     generate_rand
    move    $s0, $v0

    jal     generate_rand
    andi    $s1, $v0, 6
    
    jal     generate_initial_pipe
    move    $t0, $v0

    move    $t1, $zero
    move    $t2, $s1
    addi    $t2, $t2, 1

Begin_if:
    add     $t1, $t1, $s0
    addi    $t2, $t2, -1
    bne     $t2, $zero, Begin_if

End_if:
    la      $t3, initialPipePosition
    la      $t4, pipeMap

    add     $t4, $t4, $t1
    sw      $t4, 0($t3)

    lw      $ra, 0($sp)
    lw      $s0, 4($sp)
    lw      $s1, 8($sp)
    addi    $sp, $sp, 12
    jr		$ra
    


moveCursor:
If1: # left
    li      $t0, 1
    bne     $a0, $t0, If2

    lw      $t0, cursorPosition
    la      $t1, pipeMap
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    lw      $t2, cursorPosition
    addi    $t2, $t2, -1
    sw      $t2, cursorPosition

    j exitMoveCursor

If2: # right
    li      $t0, 2
    bne     $a0, $t0, If3

    lw      $t0, cursorPosition
    la      $t1, pipeMap
    addi    $t1, $t1, 9
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    addi    $t1, $t1, 10
    beq     $t0, $t1, exitMoveCursor

    lw      $t2, cursorPosition
    addi    $t2, $t2, 1
    sw      $t2, cursorPosition

    j exitMoveCursor

If3: # down
    li      $t0, 3
    bne     $a0, $t0, If4

    lw      $t0, cursorPosition
    la      $t1, pipeMap
    addi    $t1, $t1, 60
    slt     $t2, $t0, $t1
    beq     $t2, $zero, exitMoveCursor

    lw      $t2, cursorPosition
    addi    $t2, $t2, 10
    sw      $t2, cursorPosition

    j exitMoveCursor

If4: # up
    li      $t0, 4
    bne     $a0, $t0, If5

    lw      $t0, cursorPosition
    la      $t1, pipeMap
    addi    $t1, $t1, 9
    slt     $t2, $t1, $t0
    beq     $t2, $zero, exitMoveCursor

    lw      $t2, cursorPosition
    addi    $t2, $t2, -10
    sw      $t2, cursorPosition

    j exitMoveCursor

If5: # place Pipe
    li      $t0, 5
    bne     $a0, $t0, exitMoveCursor

    addi    $sp, $sp, -4
    sw      $ra, 0($sp)

    jal     place_pipe

    lw      $ra, 0($sp)
    addi    $sp, $sp, 4

exitMoveCursor:
    jr      $ra


#count_pipes: