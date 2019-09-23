#ifndef _MIF_LOADER_H_
#define _MIF_LOADER_H_
#include <limits>
#include <string>
#include <fstream>
#include <iostream>

namespace  MifLoader {
    inline std::string& trim(std::string& s) {
        const char* t = " \t\n\r\f\v";

        s.erase(0, s.find_first_not_of(t));
        s.erase(s.find_last_not_of(t) + 1);
        return s;
    }

    template <typename T>
    inline bool addHexDigit(T &u, unsigned int d) {
        if (u > (std::numeric_limits<T>::max() - d) / 16) {
            return false;
        }
        u = u * 16 + d;
        return true;
    }

    template <typename T>
    inline bool strToHex(const std::string &str, T &n) {
        unsigned int d;

        n = 0;
        for (char ch : str) {
            if (ch >= '0' && ch <= '9') {
                d = ch - '0';
            } else if (ch >= 'a' && ch <= 'f') {
                d = ch - 'a' + 10;
            } else if (ch >= 'A' && ch <= 'F') {
                d = ch - 'A' + 10;
            } else {
                return false;
            }
            if (!addHexDigit(n, d)) {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    bool loadFile(const std::string &path, T *mem) {
        std::ifstream in (path.c_str(), std::ios::in);

        if (!in.is_open()) {
            std::cerr << "Cannot open file '" << path << "'.\n";
            return false;
        }

        std::string line;
        int index = 0;
        T v;

        while (!in.eof()) {
            std::getline(in, line);
            trim(line);
            if (!strToHex(line, v)) {
                std::cerr << "Error loading file '" << path << "'. "
                        << "Invalid data at line " << (index + 1) << "\n";
                return false;
            }
            mem[index++] = v;
        }

        in.close();
        return true;
    }
} //  MifLoader

#endif
