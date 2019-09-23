/*
 * MIPS32Sim.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: ideras
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>
#include "VMIPS32SOC.h"
#include "VMIPS32SOC_MIPS32SOC.h"
#include "VMIPS32SOC_InstMemory.h"
#include "VMIPS32SOC_DataMemory.h"
#include "VMIPS32SOC_RegisterFile.h"
#include "VMIPS32SOC_MIPS32SOC.h"
#include "VMIPS32SOC_VGATextCard.h"
#include "VMIPS32SOC_DualPortVGARam.h"
#include "VMIPS32SOC_FontRom.h"
#include "VMIPS32SOC_RomColorPalette.h"
#include "Mips32SocSim.h"

const char *reg_names[] = {
    "$zero", "$at", "$v0", "$v1",
    "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3",
    "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3",
    "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9", "$k0", "$k1",
    "$gp", "$sp", "$fp", "$ra"
};

bool repaintFlag = false;

Mips32Sim::Mips32Sim(VGATextWindow *vgatw):
    m32soc(new VMIPS32SOC),
    vgatw(vgatw),
    timerThread(nullptr),
    simThread(nullptr),
    running(true) {
    m32soc->clk = 0;
    m32soc->resetIn = 0;
    m32soc->eval();  // Execute initial blocks
}

Mips32Sim::~Mips32Sim() {
    running = false;

    if (timerThread != nullptr) {
        timerThread->join();
    }
    if (simThread != nullptr) {
        simThread->join();
    }
    delete timerThread, simThread;
    m32soc->final();
}

void Mips32Sim::oneClockPulse() {
    m32soc->clk = 1;
    m32soc->eval();
    m32soc->clk = 0;
    m32soc->eval();
}

void Mips32Sim::reset() {
    m32soc->resetIn = 1;
    m32soc->clk = 0;
    clockPulse();
    m32soc->resetIn = 0;
}

uint8_t *Mips32Sim::getVgaRom() {
    return m32soc->MIPS32SOC->vgaTextCard->fontRom->memory;
}

uint32_t *Mips32Sim::getVgaFb() {
    return m32soc->MIPS32SOC->vgaTextCard->frameBuff->memory;
}

uint32_t *Mips32Sim::getInstMem() { 
    return m32soc->MIPS32SOC->instMem->memory; 
}

uint32_t *Mips32Sim::getDataMem() {
    return m32soc->MIPS32SOC->dataMem->memory;
}

void Mips32Sim::dumpRegFile() {
    uint32_t *rf = m32soc->MIPS32SOC->regFile->memory;
    for (int i = 0; i < 32; i++) {
        printf("%s = %08x\n", reg_names[i], rf[i]);
    }
}

inline void printChar(char ch) {
    if (!(ch >=32 && ch <= 128)) {
        ch = '?';
    }
    std::cout << ch;
}

inline void printWord(uint32_t w) {
    printChar(static_cast<char>(w >> 24));
    printChar(static_cast<char>(w >> 16));
    printChar(static_cast<char>(w >> 8));
    printChar(static_cast<char>(w >> 0));
}

void Mips32Sim::dumpDataMemoryAscii() {
    int count = 0;
    uint32_t *mem = m32soc->MIPS32SOC->dataMem->memory;
    for (int i = 0; i < 32; i++) {
        printWord(mem[i]);
        count++;
        if (count == 16) {
            std::cout << '\n';
            count = 0;
        }
    }
}
void Mips32Sim::dumpDataMemory() {
    int count = 0;

    printf("Data memory\n");
    uint32_t *mem = m32soc->MIPS32SOC->dataMem->memory;
    for (int i = 0; i < 32; i++) {
        printf("%08X ", mem[i]);
        count++;
        if (count == 16) {
            printf("\n");
            count = 0;
        }
    }
}

uint32_t Mips32Sim::getDataAt(uint32_t addr) {
    uint32_t phys_addr = (addr - 0x10010000) / 4;
    uint32_t *mem = m32soc->MIPS32SOC->dataMem->memory;

    return mem[phys_addr];
}

bool Mips32Sim::start() {
    uint32_t *vgaram = m32soc->MIPS32SOC->vgaTextCard->frameBuff->memory;
    uint8_t *vgarom = m32soc->MIPS32SOC->vgaTextCard->fontRom->memory;
    uint8_t *vgapal = m32soc->MIPS32SOC->vgaTextCard->palRom->memory;

    if (!vgatw->initDisplay(vgaram, vgarom, vgapal)) {
        std::cerr << "Couldn't initialize VGA display. " << SDL_GetError() << '\n';
        running = false;
    } else {
        running = true;
        //timerThread = new std::thread(&Mips32Sim::repaintDisplayWindow, this);
        simThread = new std::thread(&Mips32Sim::run, this);
    }

    return running;
}

void Mips32Sim::repaintDisplayWindow() {
    while (running) {
        if (repaintFlag) {
            vgatw->redraw();
            repaintFlag = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool Mips32Sim::getResetState() {
    return vgatw->resetKeyPressed(); // Active HIGH    
}

void Mips32Sim::run() {
    m32soc->keypadIn = 0x0;
    reset();

    while (!Verilated::gotFinish()) {
        //dumpRegFile();
        /*uint32_t pc = m32soc->MIPS32SOC->pc;
        uint32_t mem_index = (pc - 0x400000) / 4;
        uint32_t inst = (mem_index < 2048)? m32soc->MIPS32SOC->instMem->memory[mem_index] : 0;

        std::cout << "FCLK " << static_cast<int>(m32soc->fclk)
                  << ", RST " << static_cast<int>(m32soc->rst)
                  << ", Opcode " << static_cast<int>(m32soc->MIPS32SOC->op)
                  << ", PC " << std::setw(8) << std::setfill('0') << std::hex << std::showbase << pc 
                  << ", Inst = " << inst 
                  << ", WDS " << ((int)m32soc->MIPS32SOC->__PVT__wds)
                  << ", RegWrite "<< ((int)m32soc->MIPS32SOC->__PVT__regw)
                  << ", LUI " << m32soc->MIPS32SOC->__PVT__s11 << '\n';
        std::string ans;
        std::getline(std::cin, ans);
        if (std::cin.eof()) {
            break;
        }
        if (ans == "n" || ans == "no" || ans == "NO" || ans == "N") {
            Verilated::gotFinish(true);
            break;
        }*/
        if (vgatw->stopKeyPressed()) {
            Verilated::gotFinish(true);
        } else {
            m32soc->resetIn = getResetState();
            m32soc->keypadIn = vgatw->getKeypadState();
            m32soc->clk = !m32soc->clk;
            m32soc->eval();

            if (m32soc->invalidAddr || m32soc->invalidOpc || m32soc->invalidPC) {
                Verilated::gotFinish(true);
            }
        }
    }
    running = false;

    dumpRegFile();
    uint32_t pc = m32soc->MIPS32SOC->PC;

    std::cout << "Processor stopped at PC = " << std::setw(8) 
              << std::setfill('0') << std::hex << std::showbase << pc << '\n';

    if (m32soc->invalidPC) {
        std::cerr << "CPU halted, due to invalid instruction address. PC = " 
                  << std::setw(8) << std::setfill('0') << std::hex << std::showbase << pc << '\n';
    }

    if (m32soc->invalidAddr) {
        uint32_t addr = m32soc->MIPS32SOC->aluResult;

        std::cerr << "CPU halted, due to invalid data address. PC = " 
                  << std::setw(8) << std::setfill('0') << std::hex << std::showbase << pc
                  << ", Address = " << addr << '\n';
    }

    if (m32soc->invalidOpc) {
        uint32_t mem_index = (pc - 0x400000) / 4;
        uint32_t inst = m32soc->MIPS32SOC->instMem->memory[mem_index];

        std::cerr << "CPU halted, due to invalid opcode. PC = " 
                  << std::setw(8) << std::setfill('0') << std::hex << std::showbase << pc
                  << ", Instruction = " << inst << '\n';
    }
}

int millis() {
    static auto time1 = std::chrono::system_clock::now();
    auto time2 = std::chrono::system_clock::now();
    auto durms = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1);

    return durms.count();
}

int updateVGADisplay() {
    static int lastTime = 0;

    if (millis() - lastTime >= 20) {
        SDL_Event e;
        e.type = SDL_WINDOWEVENT;
        e.window.event = SDL_WINDOWEVENT_EXPOSED;
        e.window.windowID = 0;

        SDL_PushEvent(&e);
        lastTime = millis();
    }

    return 1;
}