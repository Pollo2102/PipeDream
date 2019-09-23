/*
 * MIPS32Sim.h
 *
 *  Created on: Sept 21, 2018
 *      Author: ideras
 */

#ifndef MIPS32SIM_H_
#define MIPS32SIM_H_

#include <cstdint>
#include <thread>
#include <memory>
#include "VGATextWindow.h"

class VMIPS32SOC;
class VGATextWindow;

class Mips32Sim {
public:
    Mips32Sim(VGATextWindow *vgatw);
    ~Mips32Sim();

    void repaintDisplayWindow();
    void dumpRegFile();
    void dumpDataMemory();
    void dumpDataMemoryAscii();
    bool start();
    bool isRunning() { return running; }
    uint32_t *getInstMem();
    uint32_t *getDataMem();
    uint8_t *getVgaRom();
    uint32_t *getVgaFb();

private:
    void run();
    void reset();
    void oneClockPulse();
    bool getResetState();

    void clockPulse() {
        oneClockPulse();
        oneClockPulse();
    }

    uint32_t getDataAt(uint32_t addr);

private:
    bool running;
    VGATextWindow *vgatw;
    std::thread *timerThread;
    std::thread *simThread;
    std::unique_ptr<VMIPS32SOC> m32soc;
};

#endif /* MIPS32SIM_H_ */
