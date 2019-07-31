.globl  start
.extern main

.text

start: 
    .set noreorder

    #setup the stack pointer
    lui $sp, 0x7FFF
    ori $sp, $sp, 0xFFFC
    jal main
    j .
