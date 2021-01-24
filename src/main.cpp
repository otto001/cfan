#include <iostream>
#include "Control.h"

#if WIN32
#include <windows.h>
#include <winfan/winfan.h>
#endif

int main(int argc, char* argv[]) {
#if WIN32
    WinFan::init();
#endif


    Control control;
    bool success = control.load();
    if (success) {
        std::cout << "Successfully loaded " << Control::configPath << std::endl;
    } else {
        std::cout << "Failed to load " << Control::configPath << std::endl;
    }

#if WIN32
    WinFan::interval = control.getInterval();
#endif

    if (argc >= 2) {
        if (argv[1] == std::string("--curses")) {
            control.curses();
        } else if (argv[1] == std::string("--detect")) {
            control.detect();
            return 0;
        } else if (argv[1] == std::string("--debug")) {
            control.debug = true;
        }
    }
    control.run();
    return 0;
}
