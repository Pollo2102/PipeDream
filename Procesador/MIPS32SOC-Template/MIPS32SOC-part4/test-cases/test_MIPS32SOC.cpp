#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include "doctest.h"
#include "VMIPS32SOC_InstMemory.h"
#include "VMIPS32SOC_DataMemory.h"
#include "VMIPS32SOC_RegisterFile.h"
#include "VMIPS32SOC_MIPS32SOC.h"
#include "VMIPS32SOC_VGATextCard.h"
#include "VMIPS32SOC_DualPortVGARam.h"
#include "VMIPS32SOC.h"

#define GLOBAL_BASEADDR 0x10010000
#define STACK_BASEADDR  0x7FFFEFFC
#define VGA_BASEADDR    0x0000B800
#define CODE_BASEADDR   0x00400000

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
    uint32_t& pc = m.MIPS32SOC->PC; \
    uint32_t* instMem = m.MIPS32SOC->instMem->memory; \
    uint32_t* dataMem = m.MIPS32SOC->dataMem->memory; \
    uint32_t* vgaFB = m.MIPS32SOC->vgaTextCard->frameBuff->memory

#define CHECK_ERROR_SIGNALS(m) \
        do { \
            REQUIRE((m).MIPS32SOC->invalidOpcode == 0); \
            REQUIRE((m).MIPS32SOC->invalidPC == 0); \
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

struct CHex {
public:
    CHex(uint32_t v): v(v) {}
    bool operator==(const CHex& rhs) const { return v == rhs.v; }
    bool operator!=(const CHex& rhs) const { return !operator==(rhs); }
    uint32_t v;
};

struct SNum {
public:
    SNum(int32_t v): v(v) {}
    bool operator==(const SNum& rhs) const { return v == rhs.v; }
    bool operator!=(const SNum& rhs) const { return !operator==(rhs); }
    int32_t v;
};

doctest::String toString(const CHex& n) {
    std::ostringstream ss;

    ss << "0x" << std::hex << n.v << std::dec;
    return ss.str().c_str();
}

doctest::String toString(const SNum& n) {
    return std::to_string(n.v).c_str();
}

void reset(VMIPS32SOC& m) {
    m.reset = 1;
    m.clk = 0;
    m.eval();
    m.clk = 1;
    m.eval();
    m.clk = 0;
    m.reset = 0;
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
    
    CHECK(SNum(t1) == SNum(-3000));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(t2 == 0);
}

TEST_CASE("'addu' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);
    a0 = 10500;  
    a1 = 3500;
    a2 = -3500;
    a3 = 500;

    setProgramCode(m, test_addu_code, TEST_ADDU_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(t0 == 14000);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(SNum(t1) == SNum(-3000));
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
    
    CHECK(SNum(t1) == SNum(-4000));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(t2 == 7000);
}

TEST_CASE("'subu' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);
    a0 = 10500;  
    a1 = 3500;
    a2 = -3500;
    a3 = 500;

    setProgramCode(m, test_subu_code, TEST_SUBU_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(t0 == 7000);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(SNum(t1) == SNum(-4000));
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
    CHECK(CHex(t0) == CHex(0x00bb00dd));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t1) == CHex(0x11000044));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t2) == CHex(0x00220044));
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
    CHECK(CHex(t0) == CHex(0xaabbccdd));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t1) == CHex(0x11223344));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t2) == CHex(0x00BB33DD));
}

TEST_CASE("'xor' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 0xaabbccdd;  
    a1 = 0xffffffff;
    a2 = 0x11223344;

    setProgramCode(m, test_xor_code, TEST_XOR_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t0) == CHex(0x55443322));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t1) == CHex(0xEEDDCCBB));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t2) == CHex(0x0));
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

TEST_CASE("'sltu' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 10500;  
    a1 = 1;
    a2 = 0xffffffff;

    setProgramCode(m, test_sltu_code, TEST_SLTU_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t0 == 0);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t1 == 0);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t2 == 1);
}

TEST_CASE("'lw' data memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = GLOBAL_BASEADDR;
    dataMem[0] = 0xaabbccdd;
    dataMem[4] = 0x11223344;
    dataMem[16] = 0xdeadbeef;

    setProgramCode(m, test_lw_code, TEST_LW_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    
    CHECK(CHex(t0) == CHex(0xaabbccdd));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0x11223344));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t2) == CHex(0xdeadbeef));
}

TEST_CASE("'lb' data memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = GLOBAL_BASEADDR;
    dataMem[0] = 0xaabb1122;

    setProgramCode(m, test_lb_code, TEST_LB_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);

    clockPulse(m);
    
    CHECK(CHex(t0) == CHex(0xffffffaa));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);

    clockPulse(m);
    
    CHECK(CHex(t1) == CHex(0xffffffbb));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);

    clockPulse(m);
    
    CHECK(CHex(t2) == CHex(0x00000011));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);

    clockPulse(m);
    
    CHECK(CHex(t3) == CHex(0x00000022));
}

TEST_CASE("'lbu' data memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = GLOBAL_BASEADDR;
    dataMem[0] = 0xaabb1122;

    setProgramCode(m, test_lbu_code, TEST_LBU_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    
    CHECK(CHex(t0) == CHex(0x000000aa));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0x000000bb));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t2) == CHex(0x00000011));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t3) == CHex(0x00000022));
}

TEST_CASE("'lh' data memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = GLOBAL_BASEADDR;
    dataMem[0] = 0xaabb1122;

    setProgramCode(m, test_lh_code, TEST_LH_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    
    CHECK(CHex(t0) == CHex(0xffffaabb));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0x00001122));
}

TEST_CASE("'lhu' data memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = GLOBAL_BASEADDR;
    dataMem[0] = 0xaabb1122;

    setProgramCode(m, test_lhu_code, TEST_LHU_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    
    CHECK(CHex(t0) == CHex(0x0000aabb));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0x00001122));
}

TEST_CASE("'lw' vga memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = VGA_BASEADDR;
    m.MIPS32SOC->vgaTextCard->frameBuff->memory[0] = 0xaabbccdd;
    m.MIPS32SOC->vgaTextCard->frameBuff->memory[4] = 0x11223344;
    m.MIPS32SOC->vgaTextCard->frameBuff->memory[16] = 0xdeadbeef;

    setProgramCode(m, test_lw_code, TEST_LW_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    
    CHECK(CHex(t0) == CHex(0xaabbccdd));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0x11223344));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t2) == CHex(0xdeadbeef));
}

TEST_CASE("'lb' vga memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = VGA_BASEADDR;
    vgaFB[0] = 0xaabb1122;

    setProgramCode(m, test_lb_code, TEST_LB_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);

    clockPulse(m);
    
    CHECK(CHex(t0) == CHex(0xffffffaa));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);

    clockPulse(m);
    
    CHECK(CHex(t1) == CHex(0xffffffbb));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);

    clockPulse(m);
    
    CHECK(CHex(t2) == CHex(0x00000011));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);

    clockPulse(m);
    
    CHECK(CHex(t3) == CHex(0x00000022));
}

TEST_CASE("'lbu' vga memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = VGA_BASEADDR;
    vgaFB[0] = 0xaabb1122;

    setProgramCode(m, test_lbu_code, TEST_LBU_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    
    CHECK(CHex(t0) == CHex(0x000000aa));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0x000000bb));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t2) == CHex(0x00000011));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t3) == CHex(0x00000022));
}

TEST_CASE("'lh' vga memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = VGA_BASEADDR;
    vgaFB[0] = 0xaabb1122;

    setProgramCode(m, test_lh_code, TEST_LH_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    
    CHECK(CHex(t0) == CHex(0xffffaabb));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0x00001122));
}

TEST_CASE("'lhu' vga memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = VGA_BASEADDR;
    vgaFB[0] = 0xaabb1122;

    setProgramCode(m, test_lhu_code, TEST_LHU_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    
    CHECK(CHex(t0) == CHex(0x0000aabb));
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0x00001122));
}

TEST_CASE("'sw' data memory test") {
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
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[0] == 0xaabbccdd);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[4] == 0x11223344);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    
    CHECK(dataMem[16] == 0xdeadbeef);
}

TEST_CASE("'sh' data memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = GLOBAL_BASEADDR;
    t0 = 0xaabb;
    t1 = 0xccdd;

    dataMem[0] = 0x11111111;
    dataMem[4] = 0x22222222;

    setProgramCode(m, test_sh_code, TEST_SH_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[0] == 0xaabb1111);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[0] == 0xaabbccdd);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[4] == 0xaabb2222);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[4] == 0xaabbccdd);
}

TEST_CASE("'sb' data memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = GLOBAL_BASEADDR;
    t0 = 0xaa;
    t1 = 0xbb;
    t2 = 0xcc;
    t3 = 0xdd;
    dataMem[0] = 0x11111111;
    dataMem[4] = 0x22222222;

    setProgramCode(m, test_sb_code, TEST_SB_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[0] == 0xaa111111);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[0] == 0xaabb1111);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[0] == 0xaabbcc11);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[0] == 0xaabbccdd);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[4] == 0xaa222222);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[4] == 0xaabb2222);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[4] == 0xaabbcc22);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(dataMem[4] == 0xaabbccdd);
}

TEST_CASE("'sw' vga memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = VGA_BASEADDR;
    t0 = 0xaabbccdd;
    t1 = 0x11223344;
    t2 = 0xdeadbeef;

    setProgramCode(m, test_sw_code, TEST_SW_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[0] == 0xaabbccdd);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[4] == 0x11223344);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    
    CHECK(vgaFB[16] == 0xdeadbeef);
}

TEST_CASE("'sh' vga memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = VGA_BASEADDR;
    t0 = 0xaabb;
    t1 = 0xccdd;

    vgaFB[0] = 0x11111111;
    vgaFB[4] = 0x22222222;

    setProgramCode(m, test_sh_code, TEST_SH_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[0] == 0xaabb1111);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[0] == 0xaabbccdd);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[4] == 0xaabb2222);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[4] == 0xaabbccdd);
}

TEST_CASE("'sb' vga memory test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = VGA_BASEADDR;
    t0 = 0xaa;
    t1 = 0xbb;
    t2 = 0xcc;
    t3 = 0xdd;
    vgaFB[0] = 0x11111111;
    vgaFB[4] = 0x22222222;

    setProgramCode(m, test_sb_code, TEST_SB_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[0] == 0xaa111111);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[0] == 0xaabb1111);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[0] == 0xaabbcc11);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[0] == 0xaabbccdd);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[4] == 0xaa222222);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[4] == 0xaabb2222);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[4] == 0xaabbcc22);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);

    CHECK(vgaFB[4] == 0xaabbccdd);
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

TEST_CASE("'lui' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);
    setProgramCode(m, test_lui_code, TEST_LUI_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t0) == CHex(0xaabb0000));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0xccdd0000));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t2) == CHex(0x11220000));
}

TEST_CASE("'addi' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);
    a0 = 3500;
    a1 = 3500;
    a2 = 3500;

    setProgramCode(m, test_addi_code, TEST_ADDI_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(t0 == 4000);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(t1 == 3000);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(t2 == 0);
}

TEST_CASE("'addiu' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);
    a0 = 3500;
    a1 = 3500;
    a2 = 3500;

    setProgramCode(m, test_addiu_code, TEST_ADDIU_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(t0 == 4000);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(t1 == 3000);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(t2 == 0);
}

TEST_CASE("'andi' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);
    a0 = 0xaabbccdd;
    a2 = 0x11223344;

    setProgramCode(m, test_andi_code, TEST_ANDI_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t0) == CHex(0xdd));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0x3344));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t2) == CHex(0xc0d0));
}

TEST_CASE("'ori' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);
    a0 = 0xaabbcc00;
    a1 = 0x11223300;
    a2 = 0x11223300;

    setProgramCode(m, test_ori_code, TEST_ORI_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t0) == CHex(0xaabbccdd));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0x11223344));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t2) == CHex(0x1122f3cd));
}

TEST_CASE("'xori' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);
    a0 = 0xaabbccdd;
    a1 = 0xffffffff;
    a2 = 0x11223344;

    setProgramCode(m, test_xori_code, TEST_XORI_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t0) == CHex(0xAABB3322));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t1) == CHex(0x1122CCBB));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(CHex(t2) == CHex(0x11220000));
}

TEST_CASE("'slti' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 10500;  
    a1 = 1;
    a2 = 0xffffffff;

    setProgramCode(m, test_slti_code, TEST_SLTI_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t0 == 1);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t1 == 1);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t2 == 0);
}

TEST_CASE("'sltiu' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 10500;  
    a1 = 1;
    a2 = 0xffffffff;

    setProgramCode(m, test_sltiu_code, TEST_SLTIU_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t0 == 0);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t1 == 0);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t2 == 1);
}

TEST_CASE("'invalid PC' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    // Special program
    instMem[0] = 0x08100200; //j	0x400800
    instMem[0x800] = 0x08100400; //j	0x401000

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK(m.MIPS32SOC->invalidPC == 0);
    CHECK(pc == (CODE_BASEADDR + 0x800));
    clockPulse(m);
    CHECK(m.MIPS32SOC->invalidPC == 0);
}

TEST_CASE("'invalid global address' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    setProgramCode(m, test_invalid_gbladdr_code, TEST_INVALID_GBLADDR_CODE_SIZE);
    a0 = GLOBAL_BASEADDR;

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    
    clockPulse(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);

    clockPulse(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 1);

    clockPulse(m);
    REQUIRE(pc == CODE_BASEADDR + 0xc);

    a0 = GLOBAL_BASEADDR - 4;
    reset(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 1);
}

TEST_CASE("'invalid stack address' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    setProgramCode(m, test_invalid_stkaddr_code, TEST_INVALID_STKADDR_CODE_SIZE);
    a1 = STACK_BASEADDR;

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    clockPulse(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);
    
    clockPulse(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 0);

    clockPulse(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 1);

    clockPulse(m);
    REQUIRE(pc == CODE_BASEADDR + 0xc);

    a1 = STACK_BASEADDR - 4;
    reset(m);
    REQUIRE(m.MIPS32SOC->invalidAddr == 1);
}

TEST_CASE("'bgez' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = -3500;
    a1 = -1;
    a2 = 0;
    a3 = 10500;

    setProgramCode(m, test_bgez_code, TEST_BGEZ_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(pc == (CODE_BASEADDR + 4));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 8));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 24));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 28));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 12));
    CHECK_ERROR_SIGNALS(m);
}

TEST_CASE("'bgtz' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = -3500;
    a1 = 0;
    a2 = 3500;
    a3 = 10500;

    setProgramCode(m, test_bgtz_code, TEST_BGTZ_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(pc == (CODE_BASEADDR + 4));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 8));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 24));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 28));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 12));
    CHECK_ERROR_SIGNALS(m);
}

TEST_CASE("'blez' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = 3500;
    a1 = 1;
    a2 = 0;
    a3 = -3500;

    setProgramCode(m, test_blez_code, TEST_BLEZ_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(pc == (CODE_BASEADDR + 4));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 8));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 24));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 28));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 12));
    CHECK_ERROR_SIGNALS(m);
}

TEST_CASE("'bltz' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = 3500;
    a1 = 0;
    a2 = -3500;
    a3 = -10500;

    setProgramCode(m, test_bltz_code, TEST_BLTZ_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);
    
    CHECK(pc == (CODE_BASEADDR + 4));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 8));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 24));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 28));
    CHECK_ERROR_SIGNALS(m);
    clockPulse(m);

    CHECK(pc == (CODE_BASEADDR + 12));
    CHECK_ERROR_SIGNALS(m);
}

TEST_CASE("'sll' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 0xdeadbeef;  
    a1 = 0xaabbccdd;
    a2 = 0x11223344;

    setProgramCode(m, test_sll_code, TEST_SLL_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t0) == CHex(0xdeadbeef));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t1) == CHex(0xabbccdd0));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t2) == CHex(0x22334400));
}

TEST_CASE("'srl' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 0xdeadbeef;  
    a1 = 0xaabbccdd;
    a2 = 0x11223344;

    setProgramCode(m, test_srl_code, TEST_SRL_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t0) == CHex(0xdeadbeef));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t1) == CHex(0x0aabbccd));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t2) == CHex(0x00112233));
}

TEST_CASE("'sllv' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 0xdeadbeef;  
    a1 = 0xaabbccdd;
    a2 = 0x11223344;
    t0 = 0;
    t1 = 4;
    t2 = 8;

    setProgramCode(m, test_sllv_code, TEST_SLLV_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t0) == CHex(0xdeadbeef));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t1) == CHex(0xabbccdd0));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t2) == CHex(0x22334400));
}

TEST_CASE("'srlv' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 0xdeadbeef;  
    a1 = 0xaabbccdd;
    a2 = 0x11223344;
    t0 = 0;
    t1 = 4;
    t2 = 8;

    setProgramCode(m, test_srlv_code, TEST_SRLV_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t0) == CHex(0xdeadbeef));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t1) == CHex(0x0aabbccd));
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(CHex(t2) == CHex(0x00112233));
}

TEST_CASE("'sra' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 4320;  
    a1 = -4320;

    setProgramCode(m, test_sra_code, TEST_SRA_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t0 == 4320);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t1 == 2160);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(SNum(t2) == SNum(-1080));
}

TEST_CASE("'srav' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);

    a0 = 4320;  
    a1 = -4320;
    t0 = 0;
    t1 = 1;
    t2 = 2;

    setProgramCode(m, test_srav_code, TEST_SRAV_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t0 == 4320);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(t1 == 2160);
    clockPulse(m);
    CHECK_ERROR_SIGNALS(m);
    CHECK(SNum(t2) == SNum(-1080));
}

TEST_CASE("'jal' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    setProgramCode(m, test_jal_code, TEST_JAL_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    clockPulse(m);

    CHECK_ERROR_SIGNALS(m);
    CHECK(pc == (CODE_BASEADDR + 16));
    CHECK(ra == CODE_BASEADDR + 4);
    clockPulse(m);

    CHECK_ERROR_SIGNALS(m);
    CHECK(pc == (CODE_BASEADDR + 20));
    clockPulse(m);

    CHECK_ERROR_SIGNALS(m);
    CHECK(pc == (CODE_BASEADDR + 4));
    CHECK(ra == CODE_BASEADDR + 24);
}

TEST_CASE("'jr' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    a0 = 0x00400010;  
    a1 = 0x00400004;
    
    setProgramCode(m, test_jr_code, TEST_JR_CODE_SIZE);

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

TEST_CASE("'reset' test") {
    VMIPS32SOC m;
    DECLARE_MIPS32_REGS(m);

    randomizeRegisterFile(m);
    a0 = 10500;  
    a1 = 3500;
    t0 = 0xdeadbeef;

    setProgramCode(m, test_add_code, TEST_ADD_CODE_SIZE);

    reset(m);
    REQUIRE(pc == CODE_BASEADDR);
    CHECK_ERROR_SIGNALS(m);
    REQUIRE( CHex(t0) == CHex(0xdeadbeef) ); // On reset the register should preserve it's value    
}