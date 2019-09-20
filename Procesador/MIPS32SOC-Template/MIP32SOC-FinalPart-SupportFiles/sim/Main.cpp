#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include <SDL.h>
#include <SDL_thread.h>

#include "MifLoader.h"
#include "CmdArgs.h"
#include "Mips32SocSim.h"
#include "VGATextWindow.h"

int main(int argc, char** argv)
{
    const char *pname = argv[0];
    CmdArgs args;

    argv++;
    argc--;
    if (!parseCmdArgs(pname, argv, argc, args)) {
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Unable to initialize SDL: " << SDL_GetError() << '\n';
        return 1;
    }

    std::unique_ptr<VGATextWindow> vgatw(new VGATextWindow(640, 480));
    Mips32Sim msim(vgatw.get());

    if (args.fileFormat == FileFormat::Elf) {
        std::cerr << "ELF file format is not supported.  Use MIF instead.\n";
        return 1;
    }

    std::cout << "Font file: \x1b[35m'" << args.fontFileName << "'\x1b[0m\n"
              << "Code file: \x1b[35m'" << args.fileName1 << "'\x1b[0m\n"
              << "Data file: \x1b[35m'" << args.fileName2 << "'\x1b[0m\n" << std::flush;

    if (!MifLoader::loadFile(args.fontFileName, msim.getVgaRom())) {
        return 1;
    }
    if (!MifLoader::loadFile(args.fileName1, msim.getInstMem())) {
        return 1;
    }
    if (!MifLoader::loadFile(args.fileName2, msim.getDataMem())) {
        return 1;
    }
    
    if (!msim.start()) {
        return 1;
    }

    vgatw->run();
    SDL_Quit();

    return 0;
}

