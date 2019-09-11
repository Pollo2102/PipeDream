// File 'test_add.S'
const uint32_t test_add_code[] = {
    /*0x00400000: */ 0x00854020, //add	t0, a0, a1
    /*0x00400004: */ 0x00c74820, //add	t1, a2, a3
    /*0x00400008: */ 0x00a65020, //add	t2, a1, a2
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_ADD_CODE_SIZE = 4;

// File 'test_and.S'
const uint32_t test_and_code[] = {
    /*0x00400000: */ 0x00854024, //and	t0, a0, a1
    /*0x00400004: */ 0x00c74824, //and	t1, a2, a3
    /*0x00400008: */ 0x00a65024, //and	t2, a1, a2
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_AND_CODE_SIZE = 4;

// File 'test_beq.S'
const uint32_t test_beq_code[] = {
    /*0x00400000: */ 0x10850004, //beq	a0, a1, 0x400014
    /*0x00400004: */ 0x10860003, //beq	a0, a2, 0x400014
    /*0x00400008: */ 0x00005020, //add	t2, zero, zero
    /*0x0040000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00400010: */ 0x00005020, //add	t2, zero, zero
    /*0x00400014: */ 0x00005020, //add	t2, zero, zero
    /*0x00400018: */ 0x10a7fffb, //beq	a1, a3, 0x400008
};
const int TEST_BEQ_CODE_SIZE = 7;

// File 'test_bne.S'
const uint32_t test_bne_code[] = {
    /*0x00400000: */ 0x14850004, //bne	a0, a1, 0x400014
    /*0x00400004: */ 0x14860003, //bne	a0, a2, 0x400014
    /*0x00400008: */ 0x00005020, //add	t2, zero, zero
    /*0x0040000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00400010: */ 0x00005020, //add	t2, zero, zero
    /*0x00400014: */ 0x00005020, //add	t2, zero, zero
    /*0x00400018: */ 0x14a7fffb, //bne	a1, a3, 0x400008
};
const int TEST_BNE_CODE_SIZE = 7;

// File 'test_jump.S'
const uint32_t test_jump_code[] = {
    /*0x00400000: */ 0x08100004, //j	0x400010
    /*0x00400004: */ 0x00005020, //add	t2, zero, zero
    /*0x00400008: */ 0x00005020, //add	t2, zero, zero
    /*0x0040000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00400010: */ 0x00005020, //add	t2, zero, zero
    /*0x00400014: */ 0x08100001, //j	0x400004
};
const int TEST_JUMP_CODE_SIZE = 6;

// File 'test_lw.S'
const uint32_t test_lw_code[] = {
    /*0x00400000: */ 0x8c880000, //lw	t0, 0(a0)
    /*0x00400004: */ 0x8c890010, //lw	t1, 16(a0)
    /*0x00400008: */ 0x8c8a0040, //lw	t2, 64(a0)
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_LW_CODE_SIZE = 4;

// File 'test_or.S'
const uint32_t test_or_code[] = {
    /*0x00400000: */ 0x00854025, //or	t0, a0, a1
    /*0x00400004: */ 0x00c74825, //or	t1, a2, a3
    /*0x00400008: */ 0x00a65025, //or	t2, a1, a2
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_OR_CODE_SIZE = 4;

// File 'test_slt.S'
const uint32_t test_slt_code[] = {
    /*0x00400000: */ 0x0085402a, //slt	t0, a0, a1
    /*0x00400004: */ 0x00c7482a, //slt	t1, a2, a3
    /*0x00400008: */ 0x00a6502a, //slt	t2, a1, a2
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SLT_CODE_SIZE = 4;

// File 'test_sub.S'
const uint32_t test_sub_code[] = {
    /*0x00400000: */ 0x00854022, //sub	t0, a0, a1
    /*0x00400004: */ 0x00c74822, //sub	t1, a2, a3
    /*0x00400008: */ 0x00a65022, //sub	t2, a1, a2
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SUB_CODE_SIZE = 4;

// File 'test_sw.S'
const uint32_t test_sw_code[] = {
    /*0x00400000: */ 0xac880000, //sw	t0, 0(a0)
    /*0x00400004: */ 0xac890010, //sw	t1, 16(a0)
    /*0x00400008: */ 0xac8a0040, //sw	t2, 64(a0)
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SW_CODE_SIZE = 4;

// File 'test_addi.S'
const uint32_t test_addi_code[] = {
    /*0x00000000: */ 0x208801f4, //addi	t0, a0, 500
    /*0x00000004: */ 0x20c9fe0c, //addi	t1, a2, -500
    /*0x00000008: */ 0x20aaf254, //addi	t2, a1, -3500
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_ADDI_CODE_SIZE = 4;

// File 'test_addiu.S'
const uint32_t test_addiu_code[] = {
    /*0x00000000: */ 0x248801f4, //addiu	t0, a0, 500
    /*0x00000004: */ 0x24c9fe0c, //addiu	t1, a2, -500
    /*0x00000008: */ 0x24aaf254, //addiu	t2, a1, -3500
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_ADDIU_CODE_SIZE = 4;

// File 'test_addu.S'
const uint32_t test_addu_code[] = {
    /*0x00000000: */ 0x00854021, //addu	t0, a0, a1
    /*0x00000004: */ 0x00c74821, //addu	t1, a2, a3
    /*0x00000008: */ 0x00a65021, //addu	t2, a1, a2
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_ADDU_CODE_SIZE = 4;

// File 'test_andi.S'
const uint32_t test_andi_code[] = {
    /*0x00000000: */ 0x308800ff, //andi	t0, a0, 0xff
    /*0x00000004: */ 0x30c9ffff, //andi	t1, a2, 0xffff
    /*0x00000008: */ 0x308af0f0, //andi	t2, a0, 0xf0f0
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_ANDI_CODE_SIZE = 4;

// File 'test_lui.S'
const uint32_t test_lui_code[] = {
    /*0x00000000: */ 0x3c08aabb, //lui	t0, 0xaabb
    /*0x00000004: */ 0x3c09ccdd, //lui	t1, 0xccdd
    /*0x00000008: */ 0x3c0a1122, //lui	t2, 0x1122
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_LUI_CODE_SIZE = 4;

// File 'test_ori.S'
const uint32_t test_ori_code[] = {
    /*0x00000000: */ 0x348800dd, //ori	t0, a0, 0xdd
    /*0x00000004: */ 0x34c90044, //ori	t1, a2, 0x44
    /*0x00000008: */ 0x34aac0cd, //ori	t2, a1, 0xc0cd
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_ORI_CODE_SIZE = 4;

// File 'test_subu.S'
const uint32_t test_subu_code[] = {
    /*0x00000000: */ 0x00854023, //subu	t0, a0, a1
    /*0x00000004: */ 0x00c74823, //subu	t1, a2, a3
    /*0x00000008: */ 0x00a65023, //subu	t2, a1, a2
    /*0x0000000c: */ 0x08000003, //j	0xc
};
const int TEST_SUBU_CODE_SIZE = 4;

// File 'test_invalid_gbladdr.S'
const uint32_t test_invalid_gbladdr_code[] = {
    /*0x00400000: */ 0x8c880000, //lw	t0, 0(a0)
    /*0x00400004: */ 0x8c880ff8, //lw	t0, 4088(a0)
    /*0x00400008: */ 0x8c880ffc, //lw	t0, 4092(a0)
    /*0x0040000c: */ 0x8c881000, //lw	t0, 4096(a0)
    /*0x00400010: */ 0x08100004, //j	0x400010
};
const int TEST_INVALID_GBLADDR_CODE_SIZE = 5;

// File 'test_invalid_stkaddr.S'
const uint32_t test_invalid_stkaddr_code[] = {
    /*0x00400000: */ 0x8ca80000, //lw	t0, 0(a1)
    /*0x00400004: */ 0x8ca80ff8, //lw	t0, 4088(a1)
    /*0x00400008: */ 0x8ca80ffc, //lw	t0, 4092(a1)
    /*0x0040000c: */ 0x8ca81000, //lw	t0, 4096(a1)
    /*0x00400010: */ 0x08100004, //j	0x400010
};
const int TEST_INVALID_STKADDR_CODE_SIZE = 5;

// File 'test_xor.S'
const uint32_t test_xor_code[] = {
    /*0x00400000: */ 0x00854026, //xor	t0, a0, a1
    /*0x00400004: */ 0x00c54826, //xor	t1, a2, a1
    /*0x00400008: */ 0x00c65026, //xor	t2, a2, a2
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_XOR_CODE_SIZE = 4;

// File 'test_xori.S'
const uint32_t test_xori_code[] = {
    /*0x00400000: */ 0x3888ffff, //xori	t0, a0, 0xffff
    /*0x00400004: */ 0x38c9ffff, //xori	t1, a2, 0xffff
    /*0x00400008: */ 0x38ca3344, //xori	t2, a2, 0x3344
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_XORI_CODE_SIZE = 4;

// File 'test_sltu.S'
const uint32_t test_sltu_code[] = {
    /*0x00400000: */ 0x0085402b, //sltu	t0, a0, a1
    /*0x00400004: */ 0x00c7482b, //sltu	t1, a2, a3
    /*0x00400008: */ 0x00a6502b, //sltu	t2, a1, a2
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SLTU_CODE_SIZE = 4;

// File 'test_sltiu.S'
const uint32_t test_sltiu_code[] = {
    /*0x00400000: */ 0x2c882903, //sltiu	t0, a0, 10499
    /*0x00400004: */ 0x2cc901f4, //sltiu	t1, a2, 500
    /*0x00400008: */ 0x2caaffff, //sltiu	t2, a1, -1
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SLTIU_CODE_SIZE = 4;

// File 'test_slti.S'
const uint32_t test_slti_code[] = {
    /*0x00400000: */ 0x28882905, //slti	t0, a0, 10501
    /*0x00400004: */ 0x28c90000, //slti	t1, a2, 0
    /*0x00400008: */ 0x28aaffff, //slti	t2, a1, -1
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SLTI_CODE_SIZE = 4;

/****** Part 3 tests: BEGIN *******/

// File 'test_lb.S'
const uint32_t test_lb_code[] = {
    /*0x00400000: */ 0x80880000, //lb	t0, 0(a0)
    /*0x00400004: */ 0x80890001, //lb	t1, 1(a0)
    /*0x00400008: */ 0x808a0002, //lb	t2, 2(a0)
    /*0x0040000c: */ 0x808b0003, //lb	t3, 3(a0)
    /*0x00400010: */ 0x08100004, //j	0x400010
};
const int TEST_LB_CODE_SIZE = 5;

// File 'test_lbu.S'
const uint32_t test_lbu_code[] = {
    /*0x00400000: */ 0x90880000, //lbu	t0, 0(a0)
    /*0x00400004: */ 0x90890001, //lbu	t1, 1(a0)
    /*0x00400008: */ 0x908a0002, //lbu	t2, 2(a0)
    /*0x0040000c: */ 0x908b0003, //lbu	t3, 3(a0)
    /*0x00400010: */ 0x08100004, //j	0x400010
};
const int TEST_LBU_CODE_SIZE = 5;

// File 'test_lhu.S'
const uint32_t test_lhu_code[] = {
    /*0x00400000: */ 0x94880000, //lhu	t0, 0(a0)
    /*0x00400004: */ 0x94890002, //lhu	t1, 2(a0)
    /*0x00400008: */ 0x08100002, //j	0x400008
};
const int TEST_LHU_CODE_SIZE = 3;

// File 'test_lh.S'
const uint32_t test_lh_code[] = {
    /*0x00400000: */ 0x84880000, //lh	t0, 0(a0)
    /*0x00400004: */ 0x84890002, //lh	t1, 2(a0)
    /*0x00400008: */ 0x08100002, //j	0x400008
};
const int TEST_LH_CODE_SIZE = 3;

// File 'test_sb.S'
const uint32_t test_sb_code[] = {
    /*0x00400000: */ 0xa0880000, //sb	t0, 0(a0)
    /*0x00400004: */ 0xa0890001, //sb	t1, 1(a0)
    /*0x00400008: */ 0xa08a0002, //sb	t2, 2(a0)
    /*0x0040000c: */ 0xa08b0003, //sb	t3, 3(a0)
    /*0x00400010: */ 0xa0880010, //sb	t0, 16(a0)
    /*0x00400014: */ 0xa0890011, //sb	t1, 17(a0)
    /*0x00400018: */ 0xa08a0012, //sb	t2, 18(a0)
    /*0x0040001c: */ 0xa08b0013, //sb	t3, 19(a0)
    /*0x00400020: */ 0x08100008, //j	0x400020
};
const int TEST_SB_CODE_SIZE = 9;

// File 'test_sh.S'
const uint32_t test_sh_code[] = {
    /*0x00400000: */ 0xa4880000, //sh	t0, 0(a0)
    /*0x00400004: */ 0xa4890002, //sh	t1, 2(a0)
    /*0x00400008: */ 0xa4880010, //sh	t0, 16(a0)
    /*0x0040000c: */ 0xa4890012, //sh	t1, 18(a0)
    /*0x00400010: */ 0x08100004, //j	0x400010
};
const int TEST_SH_CODE_SIZE = 5;

/****** Part 3 tests: END *******/

/****** Part 4 tests: BEGIN *****/

// File 'test_bgez.S'
const uint32_t test_bgez_code[] = {
    /*0x00400000: */ 0x04810005, //bgez	a0, 0x400018
    /*0x00400004: */ 0x04a10004, //bgez	a1, 0x400018
    /*0x00400008: */ 0x04c10003, //bgez	a2, 0x400018
    /*0x0040000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00400010: */ 0x00005020, //add	t2, zero, zero
    /*0x00400014: */ 0x00005020, //add	t2, zero, zero
    /*0x00400018: */ 0x00005020, //add	t2, zero, zero
    /*0x0040001c: */ 0x04e1fffb, //bgez	a3, 0x40000c
};
const int TEST_BGEZ_CODE_SIZE = 8;

// File 'test_bgtz.S'
const uint32_t test_bgtz_code[] = {
    /*0x00400000: */ 0x1c800005, //bgtz	a0, zero, 0x400018
    /*0x00400004: */ 0x1ca00004, //bgtz	a1, zero, 0x400018
    /*0x00400008: */ 0x1cc00003, //bgtz	a2, zero, 0x400018
    /*0x0040000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00400010: */ 0x00005020, //add	t2, zero, zero
    /*0x00400014: */ 0x00005020, //add	t2, zero, zero
    /*0x00400018: */ 0x00005020, //add	t2, zero, zero
    /*0x0040001c: */ 0x1ce0fffb, //bgtz	a3, zero, 0x40000c
};
const int TEST_BGTZ_CODE_SIZE = 8;

// File 'test_blez.S'
const uint32_t test_blez_code[] = {
    /*0x00400000: */ 0x18800005, //blez	a0, zero, 0x400018
    /*0x00400004: */ 0x18a00004, //blez	a1, zero, 0x400018
    /*0x00400008: */ 0x18c00003, //blez	a2, zero, 0x400018
    /*0x0040000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00400010: */ 0x00005020, //add	t2, zero, zero
    /*0x00400014: */ 0x00005020, //add	t2, zero, zero
    /*0x00400018: */ 0x00005020, //add	t2, zero, zero
    /*0x0040001c: */ 0x18e0fffb, //blez	a3, zero, 0x40000c
};
const int TEST_BLEZ_CODE_SIZE = 8;

// File 'test_bltz.S'
const uint32_t test_bltz_code[] = {
    /*0x00400000: */ 0x04800005, //bltz	a0, 0x400018
    /*0x00400004: */ 0x04a00004, //bltz	a1, 0x400018
    /*0x00400008: */ 0x04c00003, //bltz	a2, 0x400018
    /*0x0040000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00400010: */ 0x00005020, //add	t2, zero, zero
    /*0x00400014: */ 0x00005020, //add	t2, zero, zero
    /*0x00400018: */ 0x00005020, //add	t2, zero, zero
    /*0x0040001c: */ 0x04e0fffb, //bltz	a3, 0x40000c
};
const int TEST_BLTZ_CODE_SIZE = 8;

// File 'test_sll.S'
const uint32_t test_sll_code[] = {
    /*0x00400000: */ 0x00044000, //sll	t0, a0, 0
    /*0x00400004: */ 0x00054900, //sll	t1, a1, 4
    /*0x00400008: */ 0x00065200, //sll	t2, a2, 8
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SLL_CODE_SIZE = 4;

// File 'test_srl.S'
const uint32_t test_srl_code[] = {
    /*0x00400000: */ 0x00044002, //srl	t0, a0, 0
    /*0x00400004: */ 0x00054902, //srl	t1, a1, 4
    /*0x00400008: */ 0x00065202, //srl	t2, a2, 8
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SRL_CODE_SIZE = 4;

// File 'test_sllv.S'
const uint32_t test_sllv_code[] = {
    /*0x00400000: */ 0x01044004, //sllv	t0, a0, t0
    /*0x00400004: */ 0x01254804, //sllv	t1, a1, t1
    /*0x00400008: */ 0x01465004, //sllv	t2, a2, t2
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SLLV_CODE_SIZE = 4;

// File 'test_srlv.S'
const uint32_t test_srlv_code[] = {
    /*0x00400000: */ 0x01044006, //srlv	t0, a0, t0
    /*0x00400004: */ 0x01254806, //srlv	t1, a1, t1
    /*0x00400008: */ 0x01465006, //srlv	t2, a2, t2
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SRLV_CODE_SIZE = 4;

// File 'test_sra.S'
const uint32_t test_sra_code[] = {
    /*0x00400000: */ 0x00044003, //sra	t0, a0, 0
    /*0x00400004: */ 0x00044843, //sra	t1, a0, 1
    /*0x00400008: */ 0x00055083, //sra	t2, a1, 2
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SRA_CODE_SIZE = 4;

// File 'test_srav.S'
const uint32_t test_srav_code[] = {
    /*0x00400000: */ 0x01044007, //srav	t0, a0, t0
    /*0x00400004: */ 0x01244807, //srav	t1, a0, t1
    /*0x00400008: */ 0x01455007, //srav	t2, a1, t2
    /*0x0040000c: */ 0x08100003, //j	0x40000c
};
const int TEST_SRAV_CODE_SIZE = 4;

// File 'test_jal.S'
const uint32_t test_jal_code[] = {
    /*0x00400000: */ 0x0c100004, //jal	0x400010
    /*0x00400004: */ 0x00005020, //add	t2, zero, zero
    /*0x00400008: */ 0x00005020, //add	t2, zero, zero
    /*0x0040000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00400010: */ 0x00005020, //add	t2, zero, zero
    /*0x00400014: */ 0x0c100001, //jal	0x400004
};
const int TEST_JAL_CODE_SIZE = 6;

// File 'test_jr.S'
const uint32_t test_jr_code[] = {
    /*0x00400000: */ 0x00800008, //jr	a0
    /*0x00400004: */ 0x00005020, //add	t2, zero, zero
    /*0x00400008: */ 0x00005020, //add	t2, zero, zero
    /*0x0040000c: */ 0x00005020, //add	t2, zero, zero
    /*0x00400010: */ 0x00005020, //add	t2, zero, zero
    /*0x00400014: */ 0x00a00008, //jr	a1
};
const int TEST_JR_CODE_SIZE = 6;

/****** Part 4 tests: END *******/