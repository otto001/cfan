#include <iostream>
#include "Control.h"

int main(int argc, char* argv[]) {
    Control control;
    bool success = control.load();
    if (success) {
        std::cout << "Successfully loaded " << Control::configPath << std::endl;
    } else {
        std::cout << "Failed to load " << Control::configPath << std::endl;
    }

    if (argc >= 2) {
        if (argv[1] == std::string("--curses")) {
            control.curses();
        } else if (argv[1] == std::string("--detect")) {
            control.detect();
            return 0;
        }
    }
    control.run();
    return 0;
}
