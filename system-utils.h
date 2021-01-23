//
// Created by ludwig on 23.01.2021.
//

#ifndef CFAN_SYSTEM_UTILS_H
#define CFAN_SYSTEM_UTILS_H

#include <string>

namespace System {

    void sleep(unsigned int millisec);
    std::string exec(const char* cmd);

}
#endif //CFAN_SYSTEM_UTILS_H
