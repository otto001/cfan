#include <iostream>
#include "Control.h"

int main(int argc, char* argv[]) {
    Control control;
    control.load();
    std::cout << "Sucessfully loaded " << Control::configPath << std::endl;

    if (argc >= 2) {
        if (argv[1] == std::string("--curses")) {
            control.curses();
        }
    }
    control.run();

    return 0;
}
