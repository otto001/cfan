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

    std::vector<std::string> args(argv + 1, argv + argc);

    if (std::find(args.begin(), args.end(), "--detect") != args.end()) {
        control.detect();
        std::cout << "Detection complete." << std::endl;
        return 0;
    } else if (std::find(args.begin(), args.end(), "--smartfaniv") != args.end()) {
        control.setFansToSmartFanIV();
        std::cout << "Reset all fans to SmartFanIV control." << std::endl;
        return 0;
    } else {
        if (std::find(args.begin(), args.end(), "--debug") != args.end()) {
            std::cout << "Debug on." << std::endl;
            control.debug = true;
        }
    }

    control.run();
    return 0;
}
