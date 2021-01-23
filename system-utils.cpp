//
// Created by ludwig on 23.01.2021.
//
#include "system-utils.h"

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