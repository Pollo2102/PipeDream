// File 'test_add.S'
const uint32_t test_add_code[] = {
    /*0x00000000: */ 0x00854020, //add	t0, a0, a1
    /*0x00000004: */ 0x00c74820, //add	t1, a2, a3
    /*0x00000008: */ 0x00a65020, //add	t2, a1, a2
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_ADD_CODE_SIZE = 4;

// File 'test_and.S'
const uint32_t test_and_code[] = {
    /*0x00000000: */ 0x00854024, //and	t0, a0, a1
    /*0x00000004: */ 0x00c74824, //and	t1, a2, a3
    /*0x00000008: */ 0x00a65024, //and	t2, a1, a2
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_AND_CODE_SIZE = 4;

// File 'test_beq.S'
const uint32_t test_beq_code[] = {
    /*0x00000000: */ 0x10850004, //beq	a0, a1, 0x14
    /*0x00000004: */ 0x10860003, //beq	a0, a2, 0x14
    /*0x00000008: */ 0x00005020, //add	t2, zero, zero
    /*0x0000000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00000010: */ 0x00005020, //add	t2, zero, zero
    /*0x00000014: */ 0x00005020, //add	t2, zero, zero
    /*0x00000018: */ 0x10a7fffb, //beq	a1, a3, 0x8
};
const int TEST_BEQ_CODE_SIZE = 7;

// File 'test_bne.S'
const uint32_t test_bne_code[] = {
    /*0x00000000: */ 0x14850004, //bne	a0, a1, 0x14
    /*0x00000004: */ 0x14860003, //bne	a0, a2, 0x14
    /*0x00000008: */ 0x00005020, //add	t2, zero, zero
    /*0x0000000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00000010: */ 0x00005020, //add	t2, zero, zero
    /*0x00000014: */ 0x00005020, //add	t2, zero, zero
    /*0x00000018: */ 0x14a7fffb, //bne	a1, a3, 0x8
};
const int TEST_BNE_CODE_SIZE = 7;

// File 'test_jump.S'
const uint32_t test_jump_code[] = {
    /*0x00000000: */ 0x08000004, //j	0x10
    /*0x00000004: */ 0x00005020, //add	t2, zero, zero
    /*0x00000008: */ 0x00005020, //add	t2, zero, zero
    /*0x0000000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00000010: */ 0x00005020, //add	t2, zero, zero
    /*0x00000014: */ 0x08000001, //j	0x4
};
const int TEST_JUMP_CODE_SIZE = 6;

// File 'test_lw.S'
const uint32_t test_lw_code[] = {
    /*0x00000000: */ 0x8c880000, //lw	t0, 0(a0)
    /*0x00000004: */ 0x8c890010, //lw	t1, 16(a0)
    /*0x00000008: */ 0x8c8a0040, //lw	t2, 64(a0)
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_LW_CODE_SIZE = 4;

// File 'test_or.S'
const uint32_t test_or_code[] = {
    /*0x00000000: */ 0x00854025, //or	t0, a0, a1
    /*0x00000004: */ 0x00c74825, //or	t1, a2, a3
    /*0x00000008: */ 0x00a65025, //or	t2, a1, a2
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_OR_CODE_SIZE = 4;

// File 'test_slt.S'
const uint32_t test_slt_code[] = {
    /*0x00000000: */ 0x0085402a, //slt	t0, a0, a1
    /*0x00000004: */ 0x00c7482a, //slt	t1, a2, a3
    /*0x00000008: */ 0x00a6502a, //slt	t2, a1, a2
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_SLT_CODE_SIZE = 4;

// File 'test_sub.S'
const uint32_t test_sub_code[] = {
    /*0x00000000: */ 0x00854022, //sub	t0, a0, a1
    /*0x00000004: */ 0x00c74822, //sub	t1, a2, a3
    /*0x00000008: */ 0x00a65022, //sub	t2, a1, a2
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_SUB_CODE_SIZE = 4;

// File 'test_sw.S'
const uint32_t test_sw_code[] = {
    /*0x00000000: */ 0xac880000, //sw	t0, 0(a0)
    /*0x00000004: */ 0xac890010, //sw	t1, 16(a0)
    /*0x00000008: */ 0xac8a0040, //sw	t2, 64(a0)
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_SW_CODE_SIZE = 4;

