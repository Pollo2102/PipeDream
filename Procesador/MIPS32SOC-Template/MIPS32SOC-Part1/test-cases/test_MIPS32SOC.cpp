#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <chrono>
#include <random>
#include "doctest.h"
#include "VMIPS32SOC_InstMemory.h"
#include "VMIPS32SOC_DataMemory.h"
#include "VMIPS32SOC_RegisterFile.h"
#include "VMIPS32SOC_MIPS32SOC.h"
#include "VMIPS32SOC.h"

#define GLOBAL_BASEADDR 0x0
#define CODE_BASEADDR   0x0

#define DECLARE_MIPS32_REGS(m) \
    uint32_t& zero = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::zero)]; \
    uint32_t& at = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::at)]; \
    uint32_t& v0 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::v0)]; \
    uint32_t& v1 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::v1)]; \
    uint32_t& a0 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::a0)]; \
    uint32_t& a1 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::a1)]; \
    uint32_t& a2 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::a2)]; \
    uint32_t& a3 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::a3)]; \
    uint32_t& t0 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::t0)]; \
    uint32_t& t1 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::t1)]; \
    uint32_t& t2 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::t2)]; \
    uint32_t& t3 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::t3)]; \
    uint32_t& t4 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::t4)]; \
    uint32_t& t5 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::t5)]; \
    uint32_t& t6 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::t6)]; \
    uint32_t& t7 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::t7)]; \
    uint32_t& s0 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::s0)]; \
    uint32_t& s1 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::s1)]; \
    uint32_t& s2 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::s2)]; \
    uint32_t& s3 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::s3)]; \
    uint32_t& s4 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::s4)]; \
    uint32_t& s5 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::s5)]; \
    uint32_t& s6 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::s6)]; \
    uint32_t& s7 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::s7)]; \
    uint32_t& t8 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::t8)]; \
    uint32_t& t9 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::t9)]; \
    uint32_t& k0 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::k0)]; \
    uint32_t& k1 = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::k1)]; \
    uint32_t& gp = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::gp)]; \
    uint32_t& sp = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::sp)]; \
    uint32_t& fp = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::fp)]; \
    uint32_t& ra = m.MIPS32SOC->regFile->memory[static_cast<int>(Mips32RegIndex::ra)]; \
    uint32_t& pc = m.MIPS32SOC->PC

#define CHECK_ERROR_SIGNALS(m) \
        do { \
            REQUIRE((m).MIPS32SOC->invalidOpcode == 0); \
        } while (0)

#include "tests-code.cpp"

enum class Mips32RegIndex {
    zero =  0,
    at =  1, 
    v0 =  2,
    v1 =  3,
    a0 =  4,
    a1 =  5,
    a2 =  6,
    a3 =  7,
    t0 =  8,
    t1 =  9,
    t2 = 10,
    t3 = 11,
    t4 = 12,
    t5 = 13,
    t6 = 14,
    t7 = 15,
    s0 = 16,
    s1 = 17,
    s2 = 18,
    s3 = 19,
    s4 = 20,
    s5 = 21,
    s6 = 22,
    s7 = 23,
    t8 = 24,
    t9 = 25,
    k0 = 26,
    k1 = 27,
    gp = 28,
    sp = 29,
    fp = 30,
    ra = 31,
};

void reset(VMIPS32SOC& m) {
    m.rst = 1;
    m.clk = 0;
    m.eval();
    m.clk = 1;
    m.eval();
    m.clk = 0;
    m.rst = 0;
    m.eval();
}

void clockPulse(VMIPS32SOC& m) {
    m.clk = 1;
    m.eval();
    m.clk = 0;
    m.eval();
}

void setProgramCode(VMIPS32SOC& m, const uint32_t code[], int size) {
    for (int i = 0; i < size; i++) {
        m.MIPS32SOC->instMem->memory[i] = code[i];
    }
}

void randomizeRegisterFile(VMIPS32SOC& m) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine re(seed);
    std::uniform_int_distribution<> dist(1, 65535);

    for (int i = 1; i < 32; i++) {
        m.MIPS32SOC->regFile->memory[i] = dist(re);
    }
}

TEST_CASE("'add' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);
    a0 = 10500;  
    a1 = 3500;
    a2 = -3500;
    a3 = 500;

    setProgramCode(m, test_add_code, TEST_ADD_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(t0 == 14000);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(t1 == -3000);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(t2 == 0);
}

TEST_CASE("'sub' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);
    a0 = 10500;  
    a1 = 3500;
    a2 = -3500;
    a3 = 500;

    setProgramCode(m, test_sub_code, TEST_SUB_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(t0 == 7000);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(t1 == -4000);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(t2 == 7000);
}

TEST_CASE("'and' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 0xaabbccdd;  
    a1 = 0x00ff00ff;
    a2 = 0x11223344;
    a3 = 0xff0000ff;

    setProgramCode(m, test_and_code, TEST_AND_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t0 == 0x00bb00dd);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t1 == 0x11000044);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t2 == 0x00220044);
}

TEST_CASE("'or' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 0xaa00cc00;  
    a1 = 0x00bb00dd;
    a2 = 0x00223300;
    a3 = 0x11000044;

    setProgramCode(m, test_or_code, TEST_OR_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t0 == 0xaabbccdd);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t1 == 0x11223344);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t2 == 0x00BB33DD);
}

TEST_CASE("'slt' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 10500;  
    a1 = 3500;
    a2 = -3500;
    a3 = 500;

    setProgramCode(m, test_slt_code, TEST_SLT_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t0 == 0);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t1 == 1);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t2 == 0);
}

TEST_CASE("'lw' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = GLOBAL_BASEADDR;
    m.MIPS32SOC->dataMem->memory[0] = 0xaabbccdd;
    m.MIPS32SOC->dataMem->memory[4] = 0x11223344;
    m.MIPS32SOC->dataMem->memory[16] = 0xdeadbeef;

    setProgramCode(m, test_lw_code, TEST_LW_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(t0 == 0xaabbccdd);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(t1 == 0x11223344);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(t2 == 0xdeadbeef);
}

TEST_CASE("'sw' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = GLOBAL_BASEADDR;
    t0 = 0xaabbccdd;
    t1 = 0x11223344;
    t2 = 0xdeadbeef;

    setProgramCode(m, test_sw_code, TEST_SW_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(m.MIPS32SOC->dataMem->memory[0] == 0xaabbccdd);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(m.MIPS32SOC->dataMem->memory[4] == 0x11223344);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(m.MIPS32SOC->dataMem->memory[16] == 0xdeadbeef);
}

TEST_CASE("'jmp' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    setProgramCode(m, test_jump_code, TEST_JUMP_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(pc == (CODE_BASEADDR + 16));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(pc == (CODE_BASEADDR + 20));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(pc == (CODE_BASEADDR + 4));
}

TEST_CASE("'beq' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = 10500;
    a1 = -3500;
    a2 = 10500;
    a3 = -3500;

    setProgramCode(m, test_beq_code, TEST_BEQ_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(pc == (CODE_BASEADDR + 4));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(pc == (CODE_BASEADDR + 20));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(pc == (CODE_BASEADDR + 24));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(pc == (CODE_BASEADDR + 8));
}

TEST_CASE("'bne' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = 10500;
    a1 = 10500;
    a2 = -3500;
    a3 = -3500;

    setProgramCode(m, test_bne_code, TEST_BNE_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(pc == (CODE_BASEADDR + 4));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 20));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 24));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(pc == (CODE_BASEADDR + 8));
}
