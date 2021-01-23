//
// Created by ludwig on 23.01.2021.
//
#include "system-utils.h"


#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>

#if WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void System::sleep(unsigned int millisec) {
#if WIN32
    Sleep(millisec);
#else
    usleep(millisec*1000);
#endif
}


std::string System::exec(const char* cmd) {
#if WIN32
    return "";
#else

    std::array<char, 128> buffer{};
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
#endif
}
