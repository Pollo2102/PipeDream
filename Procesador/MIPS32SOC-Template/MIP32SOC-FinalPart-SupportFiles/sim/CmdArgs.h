#ifndef _CMD_ARGS_H_
#define _CMD_ARGS_H_

#include <string>

enum class FileFormat {
    Mif,
    Elf,
    Unspecified
};

struct CmdArgs {
    FileFormat fileFormat;
    std::string fileName1;
    std::string fileName2;
    std::string fontFileName;
};

bool parseCmdArgs(const char *pname, char *argv[], int argc, CmdArgs &args);
void usage(const char *progname);

#endif
