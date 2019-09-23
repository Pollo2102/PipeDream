#include <cstring>
#include <iostream>
#include "CmdArgs.h"

bool getArgValue(int &i, char *argv[], int argc, std::string &value) {
    if (i < argc - 1) {
        value = argv[i+1];
        i++;
        return true;
    } else {
        return false;
    }
}

bool parseCmdArgs(const char *pname, char *argv[], int argc, CmdArgs &args) {
    args.fileFormat = FileFormat::Unspecified;
    for (int i = 0; i < argc; i++) {
        if (strncmp(argv[i], "--mif", 5) == 0) {
            std::string miff;
            args.fileFormat = FileFormat::Mif;
            if (!getArgValue(i, argv, argc, miff)) {
                usage(pname);
                std::cerr << "Missing argument for option '" << argv[i] << "'\n";
                return false;
            }
            int pos = miff.find(':');
            if (pos != std::string::npos) {
                args.fileName1 = miff.substr(0, pos);
                args.fileName2 = miff.substr(pos + 1);
            } else {
                args.fileName1 = miff;
            }
        } else if (strncmp(argv[i], "--elf", 5) == 0) {
            args.fileFormat = FileFormat::Elf;
            if (!getArgValue(i, argv, argc, args.fileName1)) {
                usage(pname);
                std::cerr << "Missing argument for option '" << argv[i] << "'\n";
                return false;
            }
        } else if (strncmp(argv[i], "--font", 6) == 0) {
            if (!getArgValue(i, argv, argc, args.fontFileName)) {
                usage(pname);
                std::cerr << "Missing argument for option '" << argv[i] << "'\n";
                return false;
            }
        } else {
            usage(pname);
            return false;
        }
    }

    if (args.fileFormat == FileFormat::Unspecified) {
        usage(pname);
        std::cerr << "You have to specify the input file format 'Mif' or 'Elf'\n";
        return false;
    }

    if (args.fontFileName.empty()) {
        usage(pname);
        std::cerr << "Missing VGA font file argument\n";
        return false;
    }

    if (args.fileFormat == FileFormat::Mif) {
        if (args.fileName1.empty()) {
            usage(pname);
            std::cerr << "Missing code file argument\n";
            return false;
        }
        if (args.fileName2.empty()) {
            usage(pname);
            std::cerr << "Missing data file argument\n";
            return false;
        }
    } else if (args.fileFormat == FileFormat::Elf) {}

    return true;
}

void usage(const char *progname) {
    std::cerr << "VMIPS32SOC version 1\n"
         << "Usage: " << progname << " ((--mif <code file>:<data file>) | (--elf <elf executable>)) --font <font file>\n"
         << "Where:\n"
         << "       --mif to specify that the input files are in MIF (memory initialization format)\n"
         << "       --elf to specify the executable file to run in ELF format\n"
         << "       --font specify the VGA font file to use\n"
         << "Ex:  " << progname << " --elf tetris.elf --font font_rom.mif\n"
         << "   -> This example command will run the program contained in the ELF executable file 'tetris.elf' using \n"
         << "      the VGA font file 'font_rom.mif'\n";
}